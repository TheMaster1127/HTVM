from flask import Flask, request, send_file
import os
import subprocess

def Trim(inputString):
    return inputString.strip() if inputString else ""

def RunCMD(command):
    try:
        result = subprocess.run(command, shell=True, check=True, capture_output=True, text=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        print(f"Error: {e}")
        return e.stdout + "\n" + e.stderr
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
        return ""

def addEndpoint(func, method="POST"):
    """Register a function as an endpoint with a single HTTP method."""
    endpoint = f"/{func.__name__}"
    
    def handle_request():
        if request.method == "GET":
            # Extract raw query string
            raw_query = request.query_string.decode('utf-8')  # Get query string like "WAESRDG="
            if raw_query:
                # Split by "=" and get everything before the "="
                key = raw_query.split('=')[0]
                return func(key)  # Pass the extracted key to the function
            else:
                return "No query string provided", 400
        
        elif request.method in {"POST", "PUT", "PATCH"}:
            data = request.get_json()
            return func(data)
        
        elif request.method == "DELETE":
            data = request.args.to_dict() if not request.is_json else request.get_json()
            return func(data)
        
        else:
            return f"Method {request.method} not supported", 405
    app.add_url_rule(
        endpoint,
        endpoint,
        handle_request,
        methods=[method]
    )



def getFilesPathsAndStuff(command):
    return RunCMD(Trim(command))
addEndpoint(getFilesPathsAndStuff)