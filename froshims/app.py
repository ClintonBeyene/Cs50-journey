from flask import Flask, render_template, request

app = Flask(__name__)

SPORTS = ['Basketball', 'Soccer', 'Ultimate Frisbee']

#implementing some code / is default
@app.route('/')
#define function
def index():

    #get that file from the folder called template open it up and send from that all character to the user's actual browser
    return render_template('index.html', sports=SPORTS)

@app.route('/register', methods=['POST'])
def register():
    if not request.form.get('name'):
        return render_template('failure.html')
    for sport in request.form.getlist('sport'):
        if sport not in SPORTS:
            return render_template('failure.html')
    return render_template('success.html')

