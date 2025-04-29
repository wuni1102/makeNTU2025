from flask import Flask
from flask import request
from flask import render_template
from flask import redirect, url_for
from flask import jsonify

global move_buffer
move_buffer = [""] * 10
submit_item = []

app = Flask(__name__)

@app.route("/")
def index():
    return render_template('index.html', move = move_buffer)

@app.route("/data", methods=['GET'])
def data():
    name = request.args.get('name')
    ret_list = jsonify(submit_item)
    submit_item.clear()
    return ret_list

@app.route('/submit', methods=['POST'])
def submit():
    move = request.form['move']
    for idx, j in enumerate(move_buffer):
        if j == "":
            result = ""
            for i in str(move):
                if i.upper() in ['W', 'A', 'S', 'D', 'L', 'R']:
                    result += i.upper()
            move_buffer[idx] = result
            break 
    print(move_buffer)
    return redirect('/')

@app.route('/addtolist', methods=['POST'])
def addtolist():
    item = request.form['item']
    submit_item.append(item)
    return redirect('/')

if __name__ == '__main__':
    app.run("192.168.59.65")