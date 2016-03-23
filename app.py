import serial
from flask import Flask, request, render_template
app = Flask(__name__)
app.debug = False
_serial = None
channels = {
    "ventilador\r\n": "desligado",
    "carregador\r\n": "desligado",
    "luz\r\n": "desligado",
    "pc\r\n": "desligado",
}


def switch(name):
    if channels.has_key(name):
        if channels[name] == "desligado":
            channels[name] = "ligado"
        else:
            channels[name] = "desligado"

@app.route("/", methods=['GET', 'POST'])
def index():
    action = None
    if request.method == 'POST':
        if request.form['action']:
            action = "{action}\r\n".format(action=request.form['action'])
            _serial.write(action.encode('ascii'))
            switch(action.lower());

    return render_template('index.html', action=action, channels=channels)

if __name__ == "__main__":
    _serial = serial.Serial('com5', 9600)
    app.run()
