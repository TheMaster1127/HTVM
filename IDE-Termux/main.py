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


@app.route('/htvm_syntax_highlighting_and_autocomplete.js')
def serve_js():
    return send_from_directory(os.getcwd(), 'htvm_syntax_highlighting_and_autocomplete.js')






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

def RunCMD(command, working_dir=None):
    try:
        if working_dir:
            os.chdir(working_dir)  # Change the working directory if specified
        result = subprocess.run(command, shell=True, check=True, capture_output=True, text=True)
        return {"status": "success", "stdout": result.stdout, "stderr": ""}
    except subprocess.CalledProcessError as e:
        print(f"Command failed: {command}")
        return {"status": "error", "stdout": e.stdout, "stderr": e.stderr}
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
        return {"status": "error", "stdout": "", "stderr": str(e)}

@app.route('/run-cmd', methods=['POST'])
def run_cmd():
    data = request.json
    command = data['command']
    working_dir = data.get('working_dir')  # Optionally provide a working directory
    print(f"Current Working Directory: {os.getcwd()}")  # Debug log
    try:
        result = RunCMD(command, working_dir)
        if result["status"] == "success":
            return jsonify({"status": "success", "output": result["stdout"], "error": result["stderr"]})
        else:
            return jsonify({"status": "error", "output": result["stdout"], "error": result["stderr"]}), 400
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500




@app.route('/run-cmd-args', methods=['POST'])
def run_cmd_with_args():
    data = request.json
    command = data['command']
    args = data['args']
    
    # Join the command with arguments (assuming args is a list)
    full_command = f"{command} {' '.join(args)}"
    
    try:
        result = subprocess.run(full_command, shell=True, capture_output=True, text=True)
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

# Serve the index.html file from the root directory
@app.route('/')
def serve_index():
    return send_from_directory(os.getcwd(), 'index.html')

if __name__ == '__main__':
    app.run(debug=True)
