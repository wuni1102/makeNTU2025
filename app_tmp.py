from flask import Flask, render_template, request, jsonify
from google import genai
from google.genai import types
from dotenv import load_dotenv

load_dotenv()
app = Flask(__name__)
client = genai.Client()

SYSTEM_PROMPT="""
You are working with a robot, this robot contains few commands that can be used to control it.
The commands are:
- W [number] - Move forward by the number of steps specified in the number.
- S [number] - Move backward by the number of steps specified in the number.
- A [number] - Turn left by the number of steps specified in the number.
- D [number] - Turn right by the number of steps specified in the number.
- L [number] - raise the left arm by the number of steps specified in the number.
- R [number] - raise the right arm by the number of steps specified in the number.
- PRINT [string] - Print the string specified in the string.
- STOP - Stop the robot.
- TALK - Talk to the robot and show the response on screen.
Your mission is to convert the natural language command into the robot command.
The robot command should be in the format of "COMMAND_1 [parameter1 (if needed)], COMMAND_2 [parameter2 (if needed)]...".
You should not add any extra text or explanation.
"""
SYSTEM_PROMPT_CONFIG = types.GenerateContentConfig(system_instruction=SYSTEM_PROMPT)

@app.route('/')
def index():
    return render_template('record_new.html')

@app.route("/generate_commands", methods=["POST"])
def transcribe_audio():
    if "audio" not in request.files:
        return jsonify({"error": "No audio file provided"}), 400
    audio_file = request.files["audio"]
    audio_content = audio_file.read()
    response = client.models.generate_content(
        model="gemini-1.5-flash",
        config=SYSTEM_PROMPT_CONFIG,
        contents=[
            "The input audio file is a command to control the robot. Please convert it into the robot command.",
            types.Part.from_bytes(
                data=audio_content,
                mime_type="audio/wav",
            ),
        ],
    )
    app.logger.info(f"{response.text=}")
    return jsonify({"commands": response.text.strip()})
