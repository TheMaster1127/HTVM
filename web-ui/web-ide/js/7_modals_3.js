// --- DEBUGGER MODAL ---
function openDebuggerModal() {
    const overlay = document.getElementById('modal-overlay');
    let modalBox = document.querySelector('.debugger-modal');
    
    if (!modalBox) {
        // Create elements once and append them to the body to avoid innerHTML wipes
        modalBox = document.createElement('div');
        modalBox.className = 'debugger-modal';
        modalBox.style.top = '20px';
        modalBox.style.left = '20px';
        modalBox.style.display = 'none'; // Start hidden

        modalBox.innerHTML = `
            <div class="debugger-header">Debugger Paused (Drag to Move)</div>
            <div class="debugger-controls">
                <button id="debugger-resume-btn">▶ Resume (F8)</button>
                <button id="debugger-stop-btn">⏹ Stop</button>
            </div>
            <div class="debugger-content">
                <div style="flex:1; display: flex; flex-direction: column;">
                    <h4>Scope Variables</h4>
                    <div class="debugger-scope"></div>
                </div>
            </div>`;
        
        let tooltip = document.getElementById('value-tooltip');
        if (!tooltip) {
            tooltip = document.createElement('div');
            tooltip.id = 'value-tooltip';
            document.body.appendChild(tooltip);
        }

        document.body.appendChild(modalBox);
        const header = modalBox.querySelector('.debugger-header');

        const resumeAndHide = () => {
            if (debuggerState.resolve) {
                debuggerState.isPaused = false;
                debuggerState.resolve();
            }
            overlay.style.display = 'none';
            modalBox.style.display = 'none';
            clearHighlight();
        };

        const stopAndHide = () => {
            stopDebugger();
            overlay.style.display = 'none';
            modalBox.style.display = 'none';
        }

        document.getElementById('debugger-resume-btn').onclick = resumeAndHide;
        document.getElementById('debugger-stop-btn').onclick = stopAndHide;

        window.addEventListener('keydown', (e) => {
            if (e.key === 'F8' && debuggerState.isPaused) {
                e.preventDefault();
                resumeAndHide();
            }
        });
        
        // --- DRAG AND DROP LOGIC (FOR MOUSE AND TOUCH) ---
        let offsetX, offsetY;
        
        const dragBackground = document.createElement('div');
        dragBackground.style.position = 'fixed';
        dragBackground.style.top = '0';
        dragBackground.style.left = '0';
        dragBackground.style.width = '100vw';
        dragBackground.style.height = '100vh';
        dragBackground.style.zIndex = '1001';
        dragBackground.style.display = 'none';
        document.body.appendChild(dragBackground);

        const move = (e) => {
            e.preventDefault();
            // Handle both mouse and touch events
            const clientX = e.clientX || e.touches[0].clientX;
            const clientY = e.clientY || e.touches[0].clientY;
            modalBox.style.left = `${clientX - offsetX}px`;
            modalBox.style.top = `${clientY - offsetY}px`;
        };
        
        const stopMove = () => {
            dragBackground.style.display = 'none';
            document.removeEventListener('mousemove', move);
            document.removeEventListener('mouseup', stopMove);
            document.removeEventListener('touchmove', move);
            document.removeEventListener('touchend', stopMove);
        };

        const startMove = (e) => {
            dragBackground.style.display = 'block';
             // Handle both mouse and touch events
            const clientX = e.clientX || e.touches[0].clientX;
            const clientY = e.clientY || e.touches[0].clientY;
            offsetX = clientX - modalBox.offsetLeft;
            offsetY = clientY - modalBox.offsetTop;
            document.addEventListener('mousemove', move);
            document.addEventListener('mouseup', stopMove);
            document.addEventListener('touchmove', move);
            document.addEventListener('touchend', stopMove);
        };
        
        header.addEventListener('mousedown', startMove);
        header.addEventListener('touchstart', startMove);
    }

    const scopeContainer = modalBox.querySelector('.debugger-scope');
    scopeContainer.innerHTML = '';
    if (debuggerState.scope && Object.keys(debuggerState.scope).length > 0) {
        for (const key in debuggerState.scope) {
            let valueStr;
            try {
                const fullStr = JSON.stringify(debuggerState.scope[key], null, 2);
                valueStr = fullStr.length > 250 ? fullStr.substring(0, 250) + '...' : fullStr;
            } catch (e) {
                valueStr = `[Circular]`;
            }
            
            const item = document.createElement('div');
            item.className = 'debugger-scope-item';
            item.innerHTML = `<span class="debugger-scope-name">${key}:</span> <span class="debugger-scope-value">${valueStr}</span>`;
            scopeContainer.appendChild(item);
        }
    } else {
        scopeContainer.innerHTML = '<i>No user-defined variables in the current scope.</i>';
    }
    
    // Display the debugger window without blocking the UI
    modalBox.style.display = 'flex';
}