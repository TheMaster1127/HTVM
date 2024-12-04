from flask import Flask, request, send_file
import os

def StrTitleCase(input_string):
    words = input_string.split(' ')  # Split the input string into words
    result = []
    for word in words:
        if word:  # Ignore empty strings (in case of multiple spaces)
            result.append(word[0].upper() + word[1:].lower())  # Capitalize first letter, lowercase others
        else:
            result.append(word)  # Preserve spaces as is
    return ' '.join(result)  # Join the list of words back into a string

# Declare the global app variable
app = None
def createBackendInit(filename="index.html"):
    """Initialize the Flask app with an optional filename to be served."""
    global app  # Use the global app variable
    app = Flask(__name__)
    # Define a route to serve the file, defaulting to 'index.html'
    def appRoute():
        file_path = os.path.join(os.path.dirname(__file__), filename)
        return send_file(file_path), 200
    # Add URL rule with the route that calls appRoute
    app.add_url_rule('/', 'appRoute', appRoute, methods=["GET"])
    # Handle 404 errors
    def notFound(e):
        return "Page not found", 404
    app.register_error_handler(404, notFound)

# Register function as an endpoint with an optional method
def addEndpoint(func, method="POST"):
    """Register a function as an endpoint with an optional method (GET or POST)."""
    endpoint = f"/{func.__name__}"
    app.add_url_rule(
        endpoint,
        endpoint,
        lambda: func(request.data.decode()),  # Handle incoming request data
        methods=[method]  # Allow methods: "GET", "POST", etc.
    )

def startServer(port=8000, host="0.0.0.0"):
    """Run the Flask app."""
    app.run(host=host, port=port, debug=True)


# Initialize Flask app
createBackendInit("awdsf.html")
# Define your custom endpoint functions using camelCase
def helloWord(data):
    # Handle data and return plain text response
    return "Hello, you sent: " + data
def TitleCaseText(data):
    # Handle data and return plain text response
    return StrTitleCase(data)
# Register the endpoints
addEndpoint(helloWord, "GET")
addEndpoint(TitleCaseText, "PUT")
# Start the server
startServer()
