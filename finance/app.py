import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime, date
import string
import re


from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get users stocks
    stocks = db.execute("SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE userid=:userid GROUP BY symbol HAVING total_shares > 0",
                        userid=session["user_id"])

    # Get user's cash balancce
    cash = db.execute("SELECT cash FROM users WHERE id = :userid", userid=session["user_id"])[0]["cash"]

    # intialize variables for total value
    total_value = cash
    grand_total = cash

    # itterate over stocks and add price and total value
    for stock in stocks:
        quote = lookup(stock["symbol"])
        stock["price"] = quote["price"]
        stock["value"] = stock["price"] * stock["total_shares"]
        total_value += stock["value"]
        grand_total += stock["value"]

    return render_template("index.html", stocks=stocks, cash=cash, total_value=total_value, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        # Check user inserted symbol
        if not symbol:
            return apology("Symbol is required", 400)

        # check user imputed share
        elif not shares:
            return apology("Shares must be provided", 400)

        # check user input is postive integer of shares
        elif not shares.isdigit():
            return apology("Shares Must be positive integer", 400)

        elif int(shares) <= 0:
            return apology("Shares must be postive integer", 400)

        # check user symbol is valid
        quote = lookup(symbol)
        if quote is None:
            return apology("Invalid Symbol", 400)

        price = quote["price"]
        total_cost = int(shares) * price

        cash = db.execute("SELECT cash FROM users WHERE id = :userid", userid=session["user_id"])[0]["cash"]

        balance = cash - total_cost

        if cash < total_cost:
            return apology("Insufficient funds")

        # update users
        db.execute("UPDATE users SET cash = :balance WHERE id = :userid",
                   balance=balance, userid=session["user_id"])

        # Insert the purchase into transactions
        db.execute("INSERT INTO transactions (userid, symbol, shares, price) values(:userid, :symbol, :shares, :price)",
                   userid=session["user_id"], symbol=quote["symbol"], shares=shares, price=round(quote["price"], 2))

        flash(f"Bought {shares} shares of {symbol} for {usd(total_cost)}!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT * FROM transactions WHERE userid=:userid ORDER BY timestamp DESC", userid=session["user_id"])

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # Require that a user input a stock’s symbol, implemented as a text field whose name is symbol
    if request.method == "GET":
        return render_template("quote.html")

    else:
        symbol = request.form.get("symbol").upper()
        response = lookup(symbol)

        if not response:
            return apology("Invalid symbol")

        else:
            text = "A share of " + " (" + response["symbol"] + ") " + "costs " + usd((response["price"]))+"."

            return render_template("quoted.html", text=text)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Require that a user input a username, implemented as a text field whose name is username.
    # Render an apology if the user’s input is blank or the username already exists.
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        symbols = string.punctuation

        # Check username was submitted
        if not username:
            return apology("Username is required", 400)

        # check password was submitted
        elif not password:
            return apology("password is required", 400)

        # check confirmation password was submitted
        elif not confirmation:
            return apology("Confirmation password is required", 400)

        # check confirmation password is similar to password
        elif password != confirmation:
            return apology("Password is not match")

        elif not re.search("[a-zA-Z]", password) or not re.search("[0-9]", password) or not re.search(fr"[{symbols}]", password):
            flash("Password must contain at leat one letter, one number and one symbol")
            return apology("Password must contain at leat one letter, number and symbol")

        # Query database for username
        assure = db.execute("SELECT * FROM users WHERE username=:username", username=username)

        # check username is not already exist
        if len(assure) != 0:
            return apology("Username is already exist!", 400)

        # add new users into database
        db.execute("INSERT INTO users (username, hash) VALUES(:username, :password)", username=username,
                   password=generate_password_hash(confirmation, method="pbkdf2:sha256", salt_length=8))

        # Query database for newly added users
        assure2 = db.execute("SELECT * FROM users WHERE username=:username", username=username)

        # Remember who are logged in
        session["user_id"] = assure2[0]["id"]

        # Flash succesful registration meassage
        flash("Registered!")

        # Return to home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Get users stocks
    stocks = db.execute("SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE userid=:userid GROUP BY symbol HAVING total_shares > 0",
                        userid=session["user_id"])

    if request.method == "POST":

        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        if symbol is None:
            return apology("Symbol is must")

        elif int(shares) <= 0 or not shares or not shares.isdigit():
            return ("Provide postive integer of shares")
        else:
            shares = int(shares)

        for stock in stocks:
            if stock["symbol"] == symbol:
                if stock["total_shares"] < shares:
                    return apology("not enough shares")
                else:
                    quote = lookup(symbol)
                    if quote is None:
                        return apology("Invalid Symbol")
                    price = quote["price"]
                    total_sale = shares * price

                    # update users table
                    db.execute("UPDATE users SET cash = cash + :total_sale WHERE id=:userid",
                               total_sale=total_sale, userid=session["user_id"])

                    # Add the sale to the history table
                    db.execute("INSERT INTO transactions (userid, symbol, shares, price) VALUES(:userid, :symbol, :shares, :price)",
                               userid=session["user_id"], symbol=symbol, shares=shares, price=price)

                    flash(f"sold {shares} shares of {symbol} for {usd(total_sale)}!")
                    return redirect("/")

        return apology("Invalid Symbol")

    # if the users visit the sell page
    else:
        return render_template("sell.html", stocks=stocks)
