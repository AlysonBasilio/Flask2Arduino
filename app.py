import serial
from flask import Flask, request, render_template
app = Flask(__name__)
app.debug = False
_serial = None
channels = {
    "ventilador\r\n": "danger",
    "carregador\r\n": "danger",
    "luzes\r\n": "danger",
    "pc\r\n": "danger",
}


def switch(name):
    if channels.has_key(name):
        if channels[name] == "danger":
            channels[name] = "success"
        else:
            channels[name] = "danger"

@app.route("/", methods=['GET', 'POST'])
def index():
    action = None
    if request.method == 'POST':
        if request.form['action']:
            action = "{action}".format(action=request.form['action'])
            _serial.write(action.encode('ascii'))
            switch(action.lower());

    print channels
    return render_template('index.html', action=action, channels=channels)

if __name__ == "__main__":
    _serial = serial.Serial('com5', 9600)
    app.run()
