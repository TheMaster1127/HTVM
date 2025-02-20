// htvm-err-handling.js

// Global error handler
function handleError(error) {
    const errorMessage = error.message;
    const errorStack = error.stack;
    
    // Display error message in the UI
    const errorDiv = document.createElement('div');
    errorDiv.style.color = 'red';
    errorDiv.style.fontSize = '16px';
    errorDiv.style.margin = '20px';
    errorDiv.style.padding = '15px';
    errorDiv.style.border = '1px solid red';
    errorDiv.style.borderRadius = '5px';
    errorDiv.innerText = `Error: ${errorMessage}\nStack Trace: ${errorStack}`;
    document.body.appendChild(errorDiv);

    console.error('Error:', errorMessage);
    console.error('Stack Trace:', errorStack);
}
