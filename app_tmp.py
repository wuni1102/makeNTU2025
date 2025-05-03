from flask import Flask, render_template, request, jsonify
from google import genai
from google.genai import types
from dotenv import load_dotenv
import os

import time
import esp32_control

from pytubefix import YouTube
from pytubefix.cli import on_progress
from moviepy import AudioFileClip

from flask import redirect
from utils import get_beat


load_dotenv()
app = Flask(__name__)
client = genai.Client()

TEXT_TO_COMMAND_SYSTEM_PROMPT="""
You are working with a robot, this robot contains few commands that can be used to control it.
The commands are:
- W [number] - Move forward by the number of steps specified in the number.
- S [number] - Move backward by the number of steps specified in the number.
- A [number] - Turn left by the number of steps specified in the number.
- D [number] - Turn right by the number of steps specified in the number.
- L [number] - raise the left arm by the number of steps specified in the number.
- R [number] - raise the right arm by the number of steps specified in the number.
- T [number] - Turn the head by the number of steps specified in the number.
- PRINT [string] - Print the string specified in the string.
- STOP - Stop the robot.
- TALK [string]- Show the response on screen.
Your mission is to convert the natural language command into the robot command.
The robot command should be in the format of "COMMAND_1 [parameter1 (if needed)], COMMAND_2 [parameter2 (if needed)]...".
You should not add any extra text or explanation.
"""

ROBOT_RESPONSE_SYSTEM_PROMPT="""
You are a kind robot, your job is to respond to the user in a friendly and helpful manner.
You should not add any extra text or explanation.
"""

TEXT_TO_COMMAND_SYSTEM_PROMPT_CONFIG = types.GenerateContentConfig(system_instruction=TEXT_TO_COMMAND_SYSTEM_PROMPT)
ROBOT_RESPONSE_SYSTEM_PROMPT_CONFIG = types.GenerateContentConfig(system_instruction=ROBOT_RESPONSE_SYSTEM_PROMPT)

@app.route('/')
def index():
    return render_template('record_new.html')

@app.route("/generate_commands", methods=["POST"])
def generate_commands():
    if "audio" not in request.files:
        return jsonify({"error": "No audio file provided"}), 400
    audio_file = request.files["audio"]
    audio_content = audio_file.read()
    transcribe = transcribe_audio(audio_content)
    app.logger.info(f"{transcribe=}")
    response = client.models.generate_content(
        model="gemini-2.0-flash",
        config=TEXT_TO_COMMAND_SYSTEM_PROMPT_CONFIG,
        contents=
            "The following text is a command to control the robot. Please convert it into the robot command."
            + transcribe
    )
    app.logger.info(f"{response.text=}")
    return jsonify({"commands": response.text.strip()})

def transcribe_audio(audio_content):
    response = client.models.generate_content(
        model="gemini-2.0-flash",
        contents=[
            "請將以下語音轉文字並直接輸出，如果有雜音可以忽略，如果全都是雜音或是無法分辨，請回覆「&$%$hu#did」",
            types.Part.from_bytes(
                data=audio_content,
                mime_type="audio/wav",
            ),
        ],
    )
    return response.text.strip()


@app.route("/execute", methods=["POST"])
def execute_commands():
    commands = request.json.get("commands", [])
    app.logger.info(f"{commands=}")
    for command in commands:
        if command.startswith("PRINT"):
            message = command.split(" ", 1)[1]
            esp32_control.print_message(message)
        elif command.startswith("STOP"):
            esp32_control.stop()
        elif command.startswith("TALK"):
            message = command.split(" ", 1)[1]
            response = client.models.generate_content(
                model="gemini-2.0-flash",
                config=ROBOT_RESPONSE_SYSTEM_PROMPT_CONFIG,
                contents=message
            )
            esp32_control.print(response.text.strip())
        else:
            action, steps = command.split(" ")
            steps = int(steps)
            if action == "W":
                esp32_control.move_forward(steps)
            elif action == "S":
                esp32_control.move_backward(steps)
            elif action == "A":
                esp32_control.turn_left(steps)
            elif action == "D":
                esp32_control.turn_right(steps)
            elif action == "L":
                esp32_control.raise_left_arm(steps)
            elif action == "R":
                esp32_control.raise_right_arm(steps)

    return jsonify({"status": "success"})

@app.route("/handle_uploaded_audio", methods=["POST"])
def handle_uploaded_audio():
    audio = request.form["fileInput"]

    
    beats = get_beat(audio)
    hand = -1 # -1: left hand, 1: right hand

    for i in range(1, len(beats)):
        if hand:

            time.sleep((float(beats[i]) - float(beats[i-1])/2))
            esp32_control.raise_right_arm(180)
            time.sleep((float(beats[i]) - float(beats[i-1])/2))
            esp32_control.raise_right_arm(-180)
            hand *= -1
        else:
            time.sleep((float(beats[i]) - float(beats[i-1])/2))
            esp32_control.raise_left_arm(180)
            time.sleep((float(beats[i]) - float(beats[i-1])/2))
            esp32_control.raise_left_arm(-180)
            hand *= -1
    return redirect("/")

@app.route("/handle_youtube_link", methods=["POST"])
def handle_youtube_link():
    
    url = request.form["textInput"]
    #return redirect("/")
    try:
        yt = YouTube(url, on_progress_callback=on_progress)
    except Exception as e:
        print(e)
        return redirect("/")
    
    stream = yt.streams.filter(only_audio=True).first()
    
    stream.download(filename="audio.webm")

    clip = AudioFileClip("audio.webm")
    clip.write_audiofile("output.wav")
    
    beats = get_beat("output.wav")
    hand = -1 # -1: left hand, 1: right hand
    os.remove("output.wav")
    os.remove("audio.webm")

    for i in range(1, len(beats)):
        if hand:

            time.sleep((float(beats[i]) - float(beats[i-1])/2))
            esp32_control.raise_right_arm(180)
            time.sleep((float(beats[i]) - float(beats[i-1])/2))
            esp32_control.raise_right_arm(-180)
            hand *= -1
        else:
            time.sleep((float(beats[i]) - float(beats[i-1])/2))
            esp32_control.raise_left_arm(180)
            time.sleep((float(beats[i]) - float(beats[i-1])/2))
            esp32_control.raise_left_arm(-180)
            hand *= -1
    return redirect("/")

if __name__ == "__main__":
    app.run("0.0.0.0")
