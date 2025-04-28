from flask import Flask
from flask import request
from flask import render_template

app = Flask(__name__)

@app.route("/")
def index():
    return render_template('index.html')

@app.route("/data", methods=['GET'])
def data():
    name = request.args.get('name')
    return name

if __name__ == '__main__':
    app.run("192.168.59.65")