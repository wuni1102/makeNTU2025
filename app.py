from flask import Flask
from flask import request
from flask import render_template
from flask import redirect, url_for
from flask import jsonify
from utils import get_beat

from google import genai
from google.genai import types

from dotenv import load_dotenv

load_dotenv()

client = genai.Client()

global move_buffer
move_buffer = []
submit_item = []

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html", move=move_buffer)


@app.route("/data", methods=["GET"])
def data():
    # name = request.args.get('name')
    ret_list = jsonify(submit_item)
    submit_item.clear()
    return ret_list


@app.route("/submit", methods=["POST"])
def submit():
    move = request.form["move"]

    result = ""
    for i in str(move):
        if i.upper() in ["W", "A", "S", "D", "L", "R"]:
            result += i.upper()
    move_buffer.append(result)

    print(move_buffer)
    return redirect("/")


@app.route("/addtolist", methods=["POST"])
def addtolist():
    item = request.form["item"]
    delete_item = request.form["delete"]
    action = request.form["action"]
    if action == "submit":
        submit_item.append(item)
    if action == "delete":
        move_buffer.remove(delete_item)
    return redirect("/")


@app.route("/handle_audio", methods=["POST"])
def handle_audio():
    audio = request.form["file"]
    beats = get_beat(audio)
    # print(beats)
    submit_item.append(beats)
    return redirect("/")


@app.route("/record")
def record():
    return render_template("record.html")


@app.route("/transcribe", methods=["POST"])
def transcribe_audio():
    if "audio" not in request.files:
        return jsonify({"error": "No audio file provided"}), 400
    audio_file = request.files["audio"]
    audio_content = audio_file.read()
    response = client.models.generate_content(
        model="gemini-1.5-flash",
        contents=[
            "請將以下語音轉文字並直接輸出，如果有雜音可以忽略，如果全都是雜音或是無法分辨，請回覆「&$%$hu#did」",
            types.Part.from_bytes(
                data=audio_content,
                mime_type="audio/wav",
            ),
        ],
    )
    app.logger.info(f"{response.text=}")
    return jsonify({"text": response.text.strip()})


if __name__ == "__main__":
    app.run("0.0.0.0")
