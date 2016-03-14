import serial
from flask import Flask
from flask import request
from flask import render_template
app = Flask(__name__)
app.debug = True
_serial = None

@app.route("/", methods=['GET', 'POST'])
def index():
    action = None
    if request.method == 'POST':
        if request.form['action']:
            action = "{action}\r\n".format(action=request.form['action'])
            _serial.write(action.encode('ascii'))

    return render_template('index.html', action=action)

if __name__ == "__main__":
    _serial = serial.Serial('com3', 9600, timeout=0)
    app.run()
