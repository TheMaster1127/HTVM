// --- Drag & Drop State ---
let draggedTab = null;

// --- UI Rendering Functions ---
async function renderAll() {
    await renderFileList();
    await renderTabs();
}

async function renderFileList() {
    const el = document.getElementById('file-list');
    el.innerHTML = '';
    const allPaths = await getAllPaths();
    const tree = {};
    allPaths.forEach(p => {
        let l = tree;
        p.split('/').filter(Boolean).forEach((part, i, a) => {
            if (!l[part]) l[part] = { _children: {} };
            if (i === a.length - 1) {
                l[part]._isFile = !p.endsWith('/');
                l[part]._path = p;
            }
            l = l[part]._children;
        });
    });

    let node = tree;
    currentDirectory.split('/').filter(Boolean).forEach(part => {
        if (node && node[part]?._children) node = node[part]._children;
    });

    if (currentDirectory !== '/') {
        const li = document.createElement('li');
        li.innerHTML = `<strong>..</strong>`;
        li.onclick = async () => {
            const parts = currentDirectory.split('/').filter(Boolean);
            parts.pop();
            await setCurrentDirectory(parts.length ? `/${parts.join('/')}/` : '/');
        };
        el.appendChild(li);
    }

    Object.keys(node || {}).sort((a, b) => (node[a]._isFile === node[b]._isFile) ? a.localeCompare(b) : node[a]._isFile ? 1 : -1).forEach(key => {
        const item = node[key];
        const li = document.createElement('li');
        const span = document.createElement('span');
        span.className = 'file-item-name';
        span.textContent = `${item._isFile ? '📄' : '📁'} ${key}`;
        li.onclick = () => (item._isFile ? openFileInEditor(item._path) : setCurrentDirectory(item._path));

        const delBtn = document.createElement('button');
        delBtn.textContent = '🗑️';
        delBtn.style.cssText = 'background:none;border:none;color:#aaa;cursor:pointer;margin-left:auto;visibility:hidden;';
        li.onmouseenter = () => delBtn.style.visibility = 'visible';
        li.onmouseleave = () => delBtn.style.visibility = 'hidden';
        delBtn.onclick = e => {
            e.stopPropagation();
            deleteItem(item._path, item._isFile);
        };

        li.appendChild(span);
        li.appendChild(delBtn);
        el.appendChild(li);
    });
    updateActiveFileVisuals(currentOpenFile);
}

async function renderTabs() {
    const container = document.getElementById('tabs-container');
    container.innerHTML = '';
    openTabs.forEach(filename => {
        const tab = document.createElement('div');
        tab.className = 'tab';
        tab.dataset.filename = filename;
        tab.title = filename;
        tab.draggable = true; // Make the tab draggable

        const name = document.createElement('span');
        name.className = 'file-name';
        name.textContent = filename.split('/').pop();
        tab.appendChild(name);

        const close = document.createElement('span');
        close.textContent = '×';
        close.className = 'close-tab';
        close.onclick = e => {
            e.stopPropagation();
            handleCloseTabRequest(filename);
        };
        tab.appendChild(close);
        
        // Add event listeners for drag-and-drop
        tab.addEventListener('dragstart', handleDragStart);
        tab.addEventListener('dragend', handleDragEnd);
        tab.addEventListener('dragover', handleDragOver);
        tab.addEventListener('dragleave', handleDragLeave);
        tab.addEventListener('drop', handleDrop);
        
        tab.onclick = () => openFileInEditor(filename);
        container.appendChild(tab);
        checkDirtyState(filename);
    });
    updateActiveFileVisuals(currentOpenFile);
}

function updateActiveFileVisuals(filename) {
    document.querySelectorAll('.tab').forEach(t => t.classList.toggle('active', t.dataset.filename === filename));
    document.querySelectorAll('#file-list li').forEach(li => li.classList.toggle('active-file-list-item', li.textContent.includes(filename?.split('/').pop() || '')));
}

function checkDirtyState(filename) {
    const tab = document.querySelector(`.tab[data-filename="${filename}"]`);
    if (!tab) return;
    const isDirty = fileSessions.has(filename) && !fileSessions.get(filename).getUndoManager().isClean();
    tab.classList.toggle('dirty', isDirty);
}

async function setCurrentDirectory(path) {
    currentDirectory = path;
    document.getElementById('current-path-display').textContent = path;
    await dbSet('lastCwd', path); // <-- CORRECTED THIS LINE
    await renderFileList();
}

const toggleDropdown = () => {
    const el = document.getElementById('lang-dropdown');
    el.style.display = el.style.display === 'block' ? 'none' : 'block';
};
window.toggleDropdown = toggleDropdown;

async function changeLanguage(name, img, lang) {
    document.getElementById('selected-lang-name').textContent = name;
    document.getElementById('selected-lang-img').src = img;
    await dbSet('selectedLangExtension', lang); // <-- CORRECTED THIS LINE
    toggleDropdown();
}
window.changeLanguage = changeLanguage;

function initResizer(resizerEl, containerEl, lsKey, direction) {
    resizerEl.onmousedown = e => {
        e.preventDefault();
        const start = direction === 'x' ? e.clientX : e.clientY;
        const startSize = direction === 'x' ? containerEl.offsetWidth : containerEl.offsetHeight;
        const doDrag = m => {
            const delta = (direction === 'x' ? m.clientX - start : m.clientY - start);
            let newSize;
            if (direction === 'y') newSize = startSize - delta;
            else if (resizerEl.id === 'output-panel-resizer') newSize = startSize - delta;
            else newSize = startSize + delta;
            if (newSize > 100 && newSize < window[direction === 'x' ? 'innerWidth' : 'innerHeight'] - 50) {
                containerEl.style[direction === 'x' ? 'width' : 'height'] = `${newSize}px`;
                editor.resize();
                fitAddon.fit();
            }
        };
        const stopDrag = async () => {
            window.removeEventListener('mousemove', doDrag);
            window.removeEventListener('mouseup', stopDrag);
            await dbSet(lsKey, containerEl.style[direction === 'x' ? 'width' : 'height']);
        };
        window.addEventListener('mousemove', doDrag);
        window.addEventListener('mouseup', stopDrag);
    };
}

async function printExecutionEndMessage() {
    const clearOnRun = await dbGet('clearTerminalOnRun');
    if (clearOnRun === true) {
        term.writeln(`\n\x1b[1;31m=== Execution is over ===\x1b[0m`);
        term.write('$ ');
    }
}

function runHtmlCode(code) {
    const panel = document.getElementById('output-panel');
    const iframe = document.getElementById('html-output');
    iframe.srcdoc = code;
    panel.classList.add('visible');
    printExecutionEndMessage();
}

function handleDownloadHtml() {
    const iframe = document.getElementById('html-output');
    const htmlContent = iframe.srcdoc;
    if (!htmlContent) return alert('No HTML content to download.');
    let fileName = prompt("Please enter a name for the HTML file:", "output.html")?.trim();
    if (!fileName) return;
    if (!fileName.toLowerCase().endsWith('.html')) fileName += '.html';
    const blob = new Blob([htmlContent], { type: 'text/html;charset=utf-8' });
    const link = document.createElement('a');
    link.href = URL.createObjectURL(blob);
    link.download = fileName;
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link);
    URL.revokeObjectURL(link.href);
}

// --- Drag & Drop Handlers ---
function handleDragStart(e) {
    draggedTab = e.target;
    e.target.classList.add('dragging');
}

function handleDragEnd(e) {
    e.target.classList.remove('dragging');
    document.querySelectorAll('.tab.drag-over').forEach(tab => tab.classList.remove('drag-over'));
}

function handleDragOver(e) {
    e.preventDefault();
    const target = e.target.closest('.tab');
    if (target && target !== draggedTab) {
        target.classList.add('drag-over');
    }
}

function handleDragLeave(e) {
    const target = e.target.closest('.tab');
    if (target) {
        target.classList.remove('drag-over');
    }
}

async function handleDrop(e) {
    e.preventDefault();
    const targetTab = e.target.closest('.tab');
    if (!targetTab || targetTab === draggedTab) {
        return;
    }

    const draggedFilename = draggedTab.dataset.filename;
    const targetFilename = targetTab.dataset.filename;

    const draggedIndex = openTabs.indexOf(draggedFilename);
    const targetIndex = openTabs.indexOf(targetFilename);
    
    // Remove the dragged tab from its original position
    openTabs.splice(draggedIndex, 1);
    // Insert it at the new position
    openTabs.splice(targetIndex, 0, draggedFilename);

    // Re-render the tabs in the new order
    await renderTabs();
}