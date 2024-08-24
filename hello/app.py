from flask import Flask, render_template, request

app = Flask(__name__)

#implementing some code / is default
@app.route('/', methods=['GET', 'POST'])
#define function
def index():
    if request.method == 'POST':
        name = request.form.get('name')
        return render_template('greet.html', name = name)
    #get that file from the folder called template open it up and send from that all character to the user's actual browser
    return render_template('index.html')



