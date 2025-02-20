// main.js

// Function to initialize the page and add UI elements
function init() {
    const messageDiv = document.createElement('div');
    messageDiv.style.color = 'white';
    messageDiv.style.fontSize = '20px';
    messageDiv.style.margin = '20px';
    messageDiv.innerText = 'HTVM is up and running!';
    document.body.appendChild(messageDiv);
    
    // Add an action button
    const actionButton = document.createElement('button');
    actionButton.innerText = 'Click me for a Test';
    actionButton.style.padding = '10px';
    actionButton.style.margin = '20px';
    actionButton.style.backgroundColor = '#4CAF50';
    actionButton.style.color = 'white';
    actionButton.style.border = 'none';
    actionButton.style.cursor = 'pointer';
    
    actionButton.addEventListener('click', () => {
        testFunction();
    });

    document.body.appendChild(actionButton);
}

// Function to test and simulate an error
function testFunction() {
    try {
        const result = simulateError();
        console.log(result);
    } catch (error) {
        handleError(error);
    }
}

// Simulate an error
function simulateError() {
    throw new Error('Something went wrong in the test function!');
}

// Initialize on page load
window.onload = init;
