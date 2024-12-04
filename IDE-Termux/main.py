from flask import Flask, request, jsonify, send_from_directory
import os
import subprocess
import sys

app = Flask(__name__)

@app.route('/save-data', methods=['POST'])
def save_data():
    data = request.json
    place = data['place']
    content = data['data']
    try:
        with open(place, 'w') as file:
            file.write(content)
        return jsonify({"status": "success"})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route('/get-data', methods=['POST'])
def get_data():
    data = request.json
    place = data['place']
    try:
        with open(place, 'r') as file:
            content = file.read()
        return jsonify({"status": "success", "data": content})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route('/get-ide-dir-path', methods=['GET'])
def get_ide_dir_path():
    try:
        ide_dir = os.getcwd()
        return jsonify({"status": "success", "path": ide_dir})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route('/open-file', methods=['POST'])
def open_file():
    data = request.json
    file_name = data['file_name']
    try:
        with open(file_name, 'r') as file:
            content = file.read()
        return jsonify({"status": "success", "data": content})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route('/check-file-existence', methods=['POST'])
def check_file_existence():
    data = request.json
    file_path = data['file_path']
    exists = os.path.isfile(file_path)
    return jsonify({"status": "success", "exists": exists})

@app.route('/run-cmd', methods=['POST'])
def run_cmd():
    data = request.json
    command = data['command']
    try:
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        return jsonify({"status": "success", "output": result.stdout, "error": result.stderr})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route('/api/open-file-location', methods=['POST'])
def open_file_location():
    data = request.get_json()
    file_path = data.get('filePath')

    if not file_path or not os.path.exists(file_path):
        return jsonify({"error": "Invalid file path or file does not exist."}), 400

    try:
        # Open file location in file explorer
        if os.name == 'nt':  # Windows
            subprocess.Popen(f'explorer /select,"{file_path}"')
        elif os.name == 'posix':  # macOS/Linux
            subprocess.Popen(['open', os.path.dirname(file_path)]) if sys.platform == 'darwin' else subprocess.Popen(['xdg-open', os.path.dirname(file_path)])

        return jsonify({"message": f"Opened location for: {file_path}"}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)
