// --- DEXIE MIGRATION: Reworked instruction set modals to be async and use IndexedDB ---

async function promptForInitialInstructionSet() {
    const overlay = document.getElementById('modal-overlay');
    overlay.style.pointerEvents = 'auto';
    overlay.style.backgroundColor = 'rgba(0,0,0,0.7)';
    overlay.style.alignItems = 'center';
    overlay.style.justifyContent = 'center';

    overlay.innerHTML = `<div class="modal-box" style="text-align: center;">
        <h3 style="margin-top: 0;">Welcome to HT-IDE!</h3>
        <p>To enable <b>HTVM</b> features like transpiling and syntax highlighting, an instruction set file is required.</p>
        <p style="color: #ccc; font-size: 0.9em;">You can manage or change instruction sets later via the button in the sidebar.</p>
        <div class="modal-buttons" style="margin-top: 20px; justify-content: center; display: flex; gap: 15px;">
            <button id="initial-instr-cancel-btn" style="background-color: #555;">Continue without HTVM</button>
            <button id="initial-instr-upload-btn" style="background-color: #3d8b40; font-weight: bold;">Upload Instruction Set</button>
        </div>
    </div>`;

    document.getElementById('initial-instr-cancel-btn').onclick = () => {
        if (confirm("Are you sure? HTVM features will be disabled until an instruction set is provided and the IDE is reloaded. You can still use the IDE for standard file editing using other programming languages, e.g., JavaScript, Python, C++, etc.")) {
            overlay.style.display = 'none';
        }
    };

    document.getElementById('initial-instr-upload-btn').onclick = () => {
        const fileInput = document.getElementById('instruction-file-input');
        
        fileInput.onchange = e => {
            const file = e.target.files[0];
            if (!file) return;

            let newName = file.name.replace(/\.[^/.]+$/, "");
            
            const reader = new FileReader();
            reader.onload = async r => {
                const content = r.target.result;
                const newId = 'initial_setup_' + Date.now();
                const newSet = { name: newName, id: newId };

                await db.instructionSets.put({ id: newId, name: newName, content: content });
                await dbSet(instructionSetKeys.list, [newSet]);
                await dbSet(instructionSetKeys.activeId, newId);

                alert(`Instruction set "${newName}" has been added and activated. The IDE will now reload to apply the changes.`);
                await window.onbeforeunload();
                window.location.reload();
            };
            reader.readAsText(file);
            fileInput.value = ''; 
        };
        
        fileInput.click();
    };

    overlay.style.display = 'flex';
}


async function openInstructionManagerModal() {
    const overlay = document.getElementById('modal-overlay');
    overlay.style.pointerEvents = 'auto';
    overlay.style.backgroundColor = 'rgba(0,0,0,0.7)';
    overlay.style.alignItems = 'center';
    overlay.style.justifyContent = 'center';
    overlay.innerHTML = `<div class="modal-box" style="width:90%; max-width:600px;">
        <h3>HTVM Instruction Sets</h3>
        <ul class="modal-list" id="instruction-sets-list"></ul>
        <div class="modal-buttons">
             <button id="instr-add-new-btn" style="float:left; background-color:#2a8f2a;">Add New from File</button>
             <button id="instr-cancel-btn">Close</button>
        </div>
    </div>`;

    const listEl = document.getElementById('instruction-sets-list');
    const populateList = async () => {
        listEl.innerHTML = '';
        let sets = await dbGet(instructionSetKeys.list) || [];
        const activeId = await dbGet(instructionSetKeys.activeId);

        if (!sets.length) {
            listEl.innerHTML = "<li class='no-sessions' style='text-align:center; padding: 20px;'>No instruction sets found. Click 'Add New' to begin.</li>";
            return;
        }

        sets.forEach(set => {
            const li = document.createElement('li');
            const isActive = set.id === activeId;
            li.style.cssText = `display:flex; align-items:center; gap:10px; ${isActive ? 'background-color:#004a6e; font-weight:bold;' : ''}`;
            const nameSpan = document.createElement('span');
            nameSpan.textContent = `${set.name} ${isActive ? '(Active)' : ''}`;
            nameSpan.style.flexGrow = '1';
            const btnGroup = document.createElement('div');

            if (!isActive) {
                const applyBtn = document.createElement('button');
                applyBtn.textContent = 'Apply';
                applyBtn.style.backgroundColor = '#0e639c';
                applyBtn.onclick = async () => {
                    if (confirm(`This will apply the "${set.name}" instruction set and reload the IDE.\n\nYour current work will be saved, but undo/redo history will be lost.\n\nContinue?`)) {
                        await dbSet(instructionSetKeys.activeId, set.id);
                        await window.onbeforeunload();
                        window.location.reload();
                    }
                };
                btnGroup.appendChild(applyBtn);
            }

            const renameBtn = document.createElement('button');
            renameBtn.textContent = '✏️';
            renameBtn.title = 'Rename';
            renameBtn.style.marginLeft = '8px';
            renameBtn.onclick = async (e) => {
                e.stopPropagation();
                let newName = prompt(`Rename instruction set "${set.name}":`, set.name);
                if (newName && newName.trim() && newName !== set.name) {
                    newName = newName.trim();
                    if (sets.some(s => s.name === newName && s.id !== set.id)) {
                        alert("An instruction set with that name already exists.");
                        return;
                    }
                    set.name = newName;
                    await dbSet(instructionSetKeys.list, sets);
                    const instructionSet = await db.instructionSets.get(set.id);
                    if (instructionSet) {
                        instructionSet.name = newName;
                        await db.instructionSets.put(instructionSet);
                    }
                    await populateList();
                }
            };
            btnGroup.appendChild(renameBtn);

            const editBtn = document.createElement('button');
            editBtn.textContent = '📜';
            editBtn.title = 'Edit Instruction Set Content';
            editBtn.style.marginLeft = '8px';
            editBtn.onclick = (e) => {
                e.stopPropagation();
                openInstructionEditorModal(set.id, set.name);
            };
            btnGroup.appendChild(editBtn);

            const deleteBtn = document.createElement('button');
            deleteBtn.textContent = '🗑️';
            deleteBtn.title = 'Delete';
            deleteBtn.style.marginLeft = '8px';
            if (isActive) {
                deleteBtn.disabled = true;
                deleteBtn.title = "Cannot delete the active set.";
            }
            deleteBtn.onclick = async (e) => {
                e.stopPropagation();
                if (confirm(`Are you sure you want to delete the instruction set "${set.name}"? This cannot be undone.`)) {
                    const newSets = sets.filter(s => s.id !== set.id);
                    await dbSet(instructionSetKeys.list, newSets);
                    await db.instructionSets.delete(set.id);
                    await populateList();
                }
            };
            btnGroup.appendChild(deleteBtn);

            li.appendChild(nameSpan);
            li.appendChild(btnGroup);
            listEl.appendChild(li);
        });
    };

    document.getElementById('instr-add-new-btn').onclick = () => {
        const fileInput = document.getElementById('instruction-file-input');
        fileInput.onchange = async e => {
            const file = e.target.files[0];
            if (!file) return;
            let sets = await dbGet(instructionSetKeys.list) || [];
            let newName = prompt("Enter a name for this new instruction set:", file.name.replace(/\.[^/.]+$/, ""));
            if (!newName || !newName.trim()) return;
            newName = newName.trim();
            if (sets.some(s => s.name === newName)) return alert("An instruction set with that name already exists.");

            const reader = new FileReader();
            reader.onload = async r => {
                const content = r.target.result;
                const newId = 'custom_' + Date.now();
                const newSetData = { name: newName, id: newId };
                sets.push(newSetData);

                await db.instructionSets.put({ ...newSetData, content: content });
                await dbSet(instructionSetKeys.list, sets);

                if (sets.length === 1) {
                    await dbSet(instructionSetKeys.activeId, newId);
                    if (confirm("First instruction set has been added and activated. The IDE needs to reload to apply the changes. Reload now?")) {
                        await window.onbeforeunload();
                        window.location.reload();
                    } else {
                        await populateList();
                    }
                } else {
                    await populateList();
                }
            };
            reader.readAsText(file);
            fileInput.value = '';
        };
        fileInput.click();
    };

    document.getElementById('instr-cancel-btn').onclick = () => {
        overlay.style.display = 'none';
    };

    await populateList();
    overlay.style.display = 'flex';
}

async function openInstructionEditorModal(setId, setName) {
    const langOptions = "cpp,py,js,go,lua,cs,java,kt,rb,nim,ahk,swift,dart,ts,groovy".split(',');
    const langToAceModeMap = {'js':'javascript','py':'python','cpp':'c_cpp','go':'golang','lua':'lua','cs':'csharp','java':'java','kt':'kotlin','rb':'ruby','nim':'nim','ahk':'autohotkey','swift':'swift','dart':'dart','ts':'typescript','groovy':'groovy'};
    const overlay = document.getElementById('modal-overlay');
    overlay.style.pointerEvents = 'auto';
    overlay.innerHTML = `<div class="modal-box instr-editor-modal">
        <h3>Editing: ${setName}</h3>
        <div class="instr-editor-content">
            <div class="instr-editor-sidebar">
                <input type="search" id="instr-editor-search" placeholder="Search functions..." style="margin-bottom: 5px;">
                <div style="display: flex; justify-content: space-between; align-items: center; margin-bottom: 5px;">
                    <label class="toggle-switch-label" title="Show internal functions"><input type="checkbox" id="instr-show-internal-check"><span>Show Internal</span></label>
                    <button id="instr-add-func-btn" style="background-color: #2a8f2a; font-size: 0.9em; padding: 4px 8px;">+ New</button>
                </div>
                <ul id="instr-editor-func-list"></ul>
            </div>
            <div class="instr-editor-main">
                <div style="display: flex; gap: 10px;">
                    <div style="flex:2"><label>Name: <input type="text" id="instr-editor-name"></label></div>
                    <div style="flex:1"><label>Language: 
                        <select id="instr-editor-lang">${langOptions.map(l => `<option value="${l}">${l}</option>`).join('')}</select>
                    </label></div>
                </div>
                <div><label>Libraries (pipe-separated): <input type="text" id="instr-editor-libs"></label></div>
                 <div style="display: flex; gap: 10px; align-items: flex-end;">
                    <div style="flex:1;"><label>Category: <input type="text" id="instr-editor-category"></label></div>
                    <button id="instr-delete-func-btn" style="background-color: #c12a2a;">Delete Func</button>
                </div>
                <label>Description (use ~~~ for new lines):</label>
                <div style="display: flex; gap: 10px; flex-grow: 1; min-height: 120px;">
                    <textarea id="instr-editor-desc" style="flex: 1; resize: vertical;"></textarea>
                    <div id="instr-editor-desc-preview" style="flex: 1; border: 1px solid #444; padding: 8px; background: #1a1a1a; overflow-y: auto; white-space: pre-wrap; font-family: monospace;"></div>
                </div>
                <div><label>Function Body:</label></div>
                <div id="instr-editor-body-ace"></div>
            </div>
        </div>
        <div class="modal-buttons" style="margin-top: 15px;">
            <button id="instr-editor-cancel-btn">Cancel</button>
            <button id="instr-editor-save-btn" style="margin-left:8px; background-color: #3d8b40;">Save & Close</button>
        </div>
    </div>`;
    
    const instructionSet = await db.instructionSets.get(setId);
    const fullContent = instructionSet ? instructionSet.content : "";

    const funcMarker = 'func======================func==============';
    const endMarker = 'funcEND======================funcEND==============';
    let bodyEditor;

    let fileHeader = '';
    let functionsText = fullContent;
    const firstFuncIndex = fullContent.indexOf(funcMarker);
    if (firstFuncIndex > -1) {
        fileHeader = fullContent.substring(0, firstFuncIndex).trim();
        functionsText = fullContent.substring(firstFuncIndex);
    }
    
    const parseInstructions = (text) => {
        const functions = [];
        const blocks = text.split(new RegExp(`\n*${funcMarker}\n*`)).filter(b => b.trim());
        
        blocks.forEach((block, index) => {
            const endBlockIndex = block.indexOf(endMarker);
            if (endBlockIndex === -1) return;
            
            const contentPart = block.substring(0, endBlockIndex).trim();
            const lines = contentPart.split('\n');
            const funcData = { id: Date.now() + index, lang: '', name: '', libs: '', category: 'uncategorized', description: '', body: '', isInternal: false };
            
            let bodyStartIndex = -1;
            for (let i = 0; i < lines.length; i++) {
                const line = lines[i].trim();
                if (line.startsWith('lang:')) funcData.lang = line.substring(5).trim();
                else if (line.startsWith('name:')) funcData.name = line.substring(5).trim();
                else if (line.startsWith('libs:')) funcData.libs = line.substring(5).trim();
                else if (line.startsWith('description:')) {
                    let descContent = line.substring(12).trim();
                    if (descContent === 'null') {
                        funcData.isInternal = true;
                        funcData.category = 'internal';
                        funcData.description = '';
                    } else {
                        const descParts = descContent.split('~~~');
                        funcData.category = descParts.shift() || 'uncategorized';
                        funcData.description = descParts.join('~~~').replace(/~~~$/, '');
                    }
                } else if (line === '' && bodyStartIndex === -1 && funcData.name) {
                    bodyStartIndex = i + 1;
                    break; 
                }
            }
            
            if (bodyStartIndex !== -1) funcData.body = lines.slice(bodyStartIndex).join('\n');
            else funcData.body = lines.slice(4).join('\n');
            
            functions.push(funcData);
        });
        return functions;
    };

    let instructions = parseInstructions(functionsText);
    let activeFuncId = null;

    bodyEditor = ace.edit("instr-editor-body-ace");
    bodyEditor.setTheme("ace/theme/monokai");
    bodyEditor.setOptions({ enableBasicAutocompletion: true, enableLiveAutocompletion: true, behavioursEnabled: true, wrap: true });

    const listEl = document.getElementById('instr-editor-func-list');
    const searchInput = document.getElementById('instr-editor-search');
    const showInternalCheck = document.getElementById('instr-show-internal-check');
    const nameInput = document.getElementById('instr-editor-name');
    const langSelect = document.getElementById('instr-editor-lang');
    const libsInput = document.getElementById('instr-editor-libs');
    const categoryInput = document.getElementById('instr-editor-category');
    const descTextarea = document.getElementById('instr-editor-desc');
    const descPreview = document.getElementById('instr-editor-desc-preview');

    langSelect.addEventListener('change', () => {
        const newLang = langSelect.value;
        const aceMode = langToAceModeMap[newLang] || 'text';
        bodyEditor.session.setMode(`ace/mode/${aceMode}`);
    });

    descTextarea.addEventListener('input', () => {
        descPreview.textContent = descTextarea.value.replace(/~~~/g, '\n');
    });

    const saveCurrentFunc = () => {
        if (activeFuncId === null) return;
        const func = instructions.find(f => f.id === activeFuncId);
        if (!func) return;
        
        func.name = nameInput.value.trim();
        func.lang = langSelect.value;
        func.libs = libsInput.value.trim();
        func.category = categoryInput.value.trim().toLowerCase() || 'uncategorized';
        func.isInternal = (func.category === 'internal');
        func.description = descTextarea.value;
        func.body = bodyEditor.getValue();
    };
    
    const displayFunc = (funcId) => {
        if (activeFuncId !== null) saveCurrentFunc();
        activeFuncId = funcId;
        const func = instructions.find(f => f.id === funcId);
        if (!func) {
            nameInput.value = ''; langSelect.value = 'js'; libsInput.value = ''; categoryInput.value = ''; descTextarea.value = ''; bodyEditor.setValue('', -1);
            descPreview.textContent = '';
            return;
        }

        nameInput.value = func.name;
        langSelect.value = func.lang;
        libsInput.value = func.libs;
        categoryInput.value = func.category;
        descTextarea.value = func.description;
        descPreview.textContent = func.description.replace(/~~~/g, '\n');
        
        bodyEditor.setValue(func.body, -1);
        const aceMode = langToAceModeMap[func.lang] || 'text';
        bodyEditor.session.setMode(`ace/mode/${aceMode}`);
        
        document.querySelectorAll('#instr-editor-func-list li').forEach(li => {
            li.classList.toggle('active', parseInt(li.dataset.id) === funcId);
        });
    };

    const populateList = () => {
        saveCurrentFunc();
        const searchTerm = searchInput.value.toLowerCase();
        const showInternal = showInternalCheck.checked;
        
        const filtered = instructions.filter(f => 
            (showInternal || !f.isInternal) && 
            (f.name.toLowerCase().includes(searchTerm) || f.category.toLowerCase().includes(searchTerm) || f.lang.toLowerCase().includes(searchTerm))
        );

        const grouped = filtered.reduce((acc, func) => {
            const category = func.category || 'uncategorized';
            (acc[category] = acc[category] || []).push(func);
            return acc;
        }, {});

        listEl.innerHTML = '';
        Object.keys(grouped).sort().forEach(category => {
            const header = document.createElement('h4');
            header.textContent = category;
            header.onclick = () => header.scrollIntoView({ behavior: 'smooth' });
            listEl.appendChild(header);
            
            grouped[category].sort((a,b) => a.name.localeCompare(b.name)).forEach(func => {
                const li = document.createElement('li');
                li.textContent = `${func.name} (${func.lang})`;
                li.dataset.id = func.id;
                li.onclick = () => displayFunc(func.id);
                if (func.id === activeFuncId) li.classList.add('active');
                listEl.appendChild(li);
            });
        });
    };
    
    searchInput.oninput = populateList;
    showInternalCheck.onchange = populateList;
    
    document.getElementById('instr-add-func-btn').onclick = () => {
        saveCurrentFunc();
        const newFunc = { id: Date.now(), name: 'NewFunction', lang: 'js', libs: 'null', category: 'new', description: '', body: '// Your code here', isInternal: false };
        instructions.push(newFunc);
        populateList();
        displayFunc(newFunc.id);
        nameInput.focus();
        nameInput.select();
    };

    document.getElementById('instr-delete-func-btn').onclick = () => {
        if (activeFuncId === null || !confirm(`Are you sure you want to delete the function "${nameInput.value} (${langSelect.value})"?`)) return;
        instructions = instructions.filter(f => f.id !== activeFuncId);
        const oldActiveId = activeFuncId;
        activeFuncId = null;
        displayFunc(null); 
        populateList();
        const nextLi = document.querySelector(`#instr-editor-func-list li:not([data-id='${oldActiveId}'])`);
        if(nextLi) nextLi.click();
    };

    document.getElementById('instr-editor-save-btn').onclick = async () => {
        saveCurrentFunc();
        
        const reconstruct = () => {
            return instructions.map(func => {
                let descString = func.isInternal ? 'null' : `${func.category}~~~${func.description}`;
                const parts = [
                    `lang: ${func.lang}`, `name: ${func.name}`, `libs: ${func.libs || 'null'}`,
                    `description: ${descString}`, '', func.body
                ];
                return `${funcMarker}\n${parts.join('\n')}\n${endMarker}`;
            }).join('\n\n');
        };

        const newFunctionsText = reconstruct();
        const newContent = (fileHeader ? fileHeader + '\n\n' : '') + newFunctionsText;
        
        await db.instructionSets.update(setId, { content: newContent });

        overlay.style.display = 'none';
        if(confirm("Instruction set saved. Reload the IDE now for changes to take effect? Your work is saved.")) {
            await window.onbeforeunload();
            window.location.reload();
        }
    };

    document.getElementById('instr-editor-cancel-btn').onclick = () => {
        if(confirm("Are you sure? All unsaved changes in this editor will be lost.")) {
            overlay.style.display = 'none';
            openInstructionManagerModal();
        }
    };

    populateList();
    if (instructions.length > 0) displayFunc(instructions[0].id);
    overlay.style.display = 'flex';
}

async function openHtvmToHtvmModal() {
    const overlay = document.getElementById('modal-overlay');
    overlay.style.pointerEvents = 'auto';
    overlay.style.backgroundColor = 'rgba(0,0,0,0.7)';
    overlay.style.alignItems = 'center';
    overlay.style.justifyContent = 'center';
    overlay.innerHTML = `<div class="modal-box" style="width:90%; max-width:600px;">
        <h3>HTVM to HTVM Converter</h3>
        <p style="margin-top:0; color:#ccc;">The currently active instruction set is the <b>TARGET</b>. Select the <b>SOURCE</b> set to convert from.</p>
        <ul class="modal-list" id="htvm-converter-list"></ul>
        <div class="modal-buttons">
             <button id="htvm-converter-cancel-btn">Close</button>
        </div>
    </div>`;

    const listEl = document.getElementById('htvm-converter-list');
    const sets = await dbGet(instructionSetKeys.list) || [];
    const activeId = await dbGet(instructionSetKeys.activeId);
    const activeSet = sets.find(s => s.id === activeId);

    if (!activeSet) {
        listEl.innerHTML = `<li class='no-sessions'>No active (TARGET) instruction set found.</li>`;
        document.getElementById('htvm-converter-cancel-btn').onclick = () => overlay.style.display = 'none';
        overlay.style.display = 'flex';
        return;
    }

    const handleSourceSelection = async (sourceId) => {
        const sourceInstructionSet = await db.instructionSets.get(sourceId);
        const targetInstructionSet = await db.instructionSets.get(activeId);
        
        if (!sourceInstructionSet || !targetInstructionSet) {
            alert("Error: Could not load instruction sets.");
            return;
        }

        const sourceInstructionSetContent = sourceInstructionSet.content;
        const targetInstructionSetContent = targetInstructionSet.content;

        const fileInput = document.createElement('input');
        fileInput.type = 'file';
        fileInput.multiple = true;
        fileInput.accept = '.htvm';
        fileInput.onchange = async e => {
            const files = e.target.files;
            if (!files || files.length === 0) return;

            overlay.style.display = 'none';
            term.writeln(`\x1b[36mStarting HTVM to HTVM conversion for ${files.length} file(s)...\x1b[0m`);

            for (const file of Array.from(files)) {
                await new Promise(resolve => {
                    const reader = new FileReader();
                    reader.onload = async r => {
                        const codeSnippet = r.target.result;
                        
                        resetGlobalVarsOfHTVMjs();
                        
                        // For uploaded files, the base path for includes is the root
                        const basePath = '/';
                        window.currentHtvmFileDirectory = basePath;

                        // --- Pre-load includes ---
                        const originalAsyncFileRead = window.FileRead;
                        const importCache = new Map();
                        await preloadHtvmImports(codeSnippet, basePath, importCache, new Set(), originalAsyncFileRead);
                        
                        // --- Override with sync reader ---
                        window.FileRead = (path) => {
                            const resolvedPath = window.resolveHtvmPath(path, basePath);
                            return importCache.get(resolvedPath);
                        };

                        let instrFile = targetInstructionSetContent;
                        const instr0 = sourceInstructionSetContent;

                        let fixInstrFile = "";
                        const items2 = LoopParseFunc(instrFile, "\n", "\r");
                        for (let index = 0; index < items2.length; index++) {
                            const LoopField2 = items2[index];
                            if (index === 1) { // Second line
                                fixInstrFile += "htvm" + '\n';
                            } else {
                                fixInstrFile += LoopField2.trim() + '\n';
                            }
                        }
                        instrFile = fixInstrFile.trimEnd();

                        const instr1 = codeSnippet.trim();
                        const instr2 = instr0.trim();
                        const instr3 = "htvm";
                        const instr4 = instrFile.trim();

                        argHTVMinstrMORE.length = 0; // Clear before using
                        argHTVMinstrMORE.push(instr4);

                        const convertedCode = await compiler(instr1, instr2, "full", instr3);
                        resetGlobalVarsOfHTVMjs();
                        // --- Restore async reader ---
                        window.FileRead = originalAsyncFileRead;

                        const originalFilename = file.name;
                        let baseNewFilename = originalFilename.replace(/(\.htvm)$/i, '.converted.htvm');
                        if (baseNewFilename === originalFilename) {
                            baseNewFilename = `${originalFilename}.converted`;
                        }

                        let finalFilename = baseNewFilename;
                        let counter = 1;
                        const allKnownPaths = await getAllPaths();
                        const nameMatch = baseNewFilename.match(/(.*)(\.htvm)$/);
                        const namePart = nameMatch ? nameMatch[1] : baseNewFilename;
                        const extPart = nameMatch ? nameMatch[2] : '';

                        let pathPrefix = currentDirectory === '/' ? '' : currentDirectory;
                        while (allKnownPaths.includes(pathPrefix + finalFilename)) {
                            finalFilename = `${namePart}(${counter})${extPart}`;
                            counter++;
                        }

                        const finalPath = pathPrefix + finalFilename;
                        
                        await saveFileContent(finalPath, convertedCode, false);
                        term.writeln(`\x1b[32mConverted ${originalFilename} -> ${finalFilename}\x1b[0m`);
                        
                        resolve();
                    };
                    reader.readAsText(file);
                });
            }
            
            await renderFileList();
            term.writeln(`\x1b[32m\nConversion process finished. Check the file list for new '.converted.htvm' files.\x1b[0m`);
            term.write('$ ');
        };
        fileInput.click();
    };

    listEl.innerHTML = '';
    sets.forEach(set => {
        const li = document.createElement('li');
        if (set.id === activeId) {
            li.textContent = `${set.name} (TARGET)`;
            li.style.cssText = 'background-color:#004a6e; font-weight:bold;';
        } else {
            li.textContent = set.name;
            li.onclick = () => handleSourceSelection(set.id);
        }
        listEl.appendChild(li);
    });

    document.getElementById('htvm-converter-cancel-btn').onclick = () => {
        overlay.style.display = 'none';
    };

    overlay.style.display = 'flex';
}

// --- Instruction Set and Converter Modals ---

async function openInstructionManagerModal() {
    const overlay = document.getElementById('modal-overlay');
    overlay.style.pointerEvents = 'auto';

    overlay.innerHTML = `<div class="modal-box instr-editor-modal">
        <h3>HTVM Instruction Set Manager</h3>
        <div class="instr-editor-content">
            <div class="instr-editor-sidebar">
                <input type="text" id="instr-search-box" placeholder="Search functions..." style="margin-bottom: 10px;">
                <ul id="instr-editor-func-list"></ul>
            </div>
            <div class="instr-editor-main">
                <div><label>Set Name: <input type="text" id="instr-set-name"></label></div>
                <div><label>Function Name: <input type="text" id="instr-func-name"></label></div>
                <div><label>Function Type: <select id="instr-func-type"><option value="normal">Normal</option><option value="string">String</option><option value="array">Array</option><option value="flow">Flow Control</option></select></label></div>
                <div><label>Function Body (JavaScript):</label><div id="instr-editor-body-ace"></div></div>
            </div>
        </div>
        <div class="modal-buttons">
            <button id="instr-delete-set-btn" class="modal-btn-reset">Delete This Set</button>
            <button id="instr-cancel-btn" class="modal-btn-cancel">Cancel</button>
            <button id="instr-save-btn" class="modal-btn-confirm">Save and Apply</button>
        </div>
    </div>`;

    let instructionSets = await dbGet(instructionSetKeys.list) || [];
    let activeSetId = await dbGet(instructionSetKeys.activeId);
    let currentEditingSet = null;

    const funcList = document.getElementById('instr-editor-func-list');
    const setNameInput = document.getElementById('instr-set-name');
    const funcNameInput = document.getElementById('instr-func-name');
    const funcTypeSelect = document.getElementById('instr-func-type');
    const searchBox = document.getElementById('instr-search-box');
    const bodyEditor = ace.edit("instr-editor-body-ace");
    bodyEditor.setTheme("ace/theme/monokai");
    bodyEditor.session.setMode("ace/mode/javascript");
    bodyEditor.setOptions({ fontSize: '14px', useWorker: false });

    const loadSetIntoEditor = (set) => {
        currentEditingSet = set;
        setNameInput.value = set.name;
        const instructions = set.content.split('\n');
        const functionData = {};
        for (let i = 42; i < 158; i += 2) {
            if (instructions[i] && instructions[i+1]) {
                functionData[instructions[i].trim()] = { body: instructions[i+1], type: 'normal' };
            }
        }
        currentEditingSet.functions = functionData;
        renderFunctionList();
        if (Object.keys(functionData).length > 0) {
            loadFunctionIntoEditor(Object.keys(functionData)[0]);
        }
    };
    
    const loadFunctionIntoEditor = (funcName) => {
        if (!currentEditingSet || !currentEditingSet.functions[funcName]) return;
        document.querySelectorAll('#instr-editor-func-list li').forEach(li => li.classList.remove('active'));
        const activeLi = document.querySelector(`#instr-editor-func-list li[data-func-name="${funcName}"]`);
        if (activeLi) activeLi.classList.add('active');
        
        funcNameInput.value = funcName;
        funcTypeSelect.value = currentEditingSet.functions[funcName].type;
        bodyEditor.setValue(currentEditingSet.functions[funcName].body, -1);
    };

    const saveCurrentFunction = () => {
        const activeLi = document.querySelector('#instr-editor-func-list li.active');
        if (!activeLi) return;
        const oldFuncName = activeLi.dataset.funcName;
        const newFuncName = funcNameInput.value.trim();
        
        if (oldFuncName !== newFuncName) {
            delete currentEditingSet.functions[oldFuncName];
        }
        currentEditingSet.functions[newFuncName] = {
            body: bodyEditor.getValue(),
            type: funcTypeSelect.value
        };
        renderFunctionList();
        loadFunctionIntoEditor(newFuncName);
    };
    
    funcNameInput.onblur = saveCurrentFunction;
    funcTypeSelect.onchange = saveCurrentFunction;
    bodyEditor.on('blur', saveCurrentFunction);

    const renderFunctionList = () => {
        funcList.innerHTML = '';
        if (!currentEditingSet) return;
        
        const filter = searchBox.value.toLowerCase();

        const addListItem = (name, type) => {
            if (filter && !name.toLowerCase().includes(filter)) return;
            const li = document.createElement('li');
            li.textContent = name;
            li.dataset.funcName = name;
            li.dataset.funcType = type;
            li.onclick = () => loadFunctionIntoEditor(name);
            funcList.appendChild(li);
        };
        
        if(currentEditingSet.functions) {
            Object.keys(currentEditingSet.functions).sort().forEach(name => addListItem(name, 'normal'));
        }
    };

    searchBox.oninput = renderFunctionList;

    if (activeSetId) {
        const activeSet = await db.instructionSets.get(activeSetId);
        if (activeSet) loadSetIntoEditor(activeSet);
    }

    document.getElementById('instr-cancel-btn').onclick = () => { overlay.style.display = 'none'; };
    
    document.getElementById('instr-delete-set-btn').onclick = async () => {
        if (!currentEditingSet || !currentEditingSet.id) return alert("No set selected to delete.");
        if (!confirm(`Are you sure you want to permanently delete the instruction set "${currentEditingSet.name}"?`)) return;
        
        instructionSets = instructionSets.filter(s => s.id !== currentEditingSet.id);
        await dbSet(instructionSetKeys.list, instructionSets);
        await db.instructionSets.delete(currentEditingSet.id);
        
        if (activeSetId === currentEditingSet.id) {
            activeSetId = instructionSets.length > 0 ? instructionSets[0].id : null;
            await dbSet(instructionSetKeys.activeId, activeSetId);
        }
        
        await loadDefinitions();
        overlay.style.display = 'none';
        alert(`Set "${currentEditingSet.name}" deleted.`);
    };

    document.getElementById('instr-save-btn').onclick = async () => {
        saveCurrentFunction();
        
        let newName = setNameInput.value.trim();
        if (!newName) return alert("Set name cannot be empty.");
        
        if (currentEditingSet) {
            let instructions = (await getActiveInstructionSetContent() || '').split('\n');
            if (instructions.length < 158) {
                instructions = new Array(158).fill('');
            }
            
            let funcIndex = 42;
            for(const funcName in currentEditingSet.functions) {
                if (funcIndex < 158) {
                    instructions[funcIndex] = funcName;
                    instructions[funcIndex + 1] = currentEditingSet.functions[funcName].body;
                    funcIndex += 2;
                }
            }
            // Clear out any remaining old function slots
            for (let i = funcIndex; i < 158; i++) {
                instructions[i] = '';
            }

            currentEditingSet.name = newName;
            currentEditingSet.content = instructions.join('\n');
            
            await db.instructionSets.put(currentEditingSet);
            let setInList = instructionSets.find(s => s.id === currentEditingSet.id);
            if (setInList) setInList.name = newName;
            await dbSet(instructionSetKeys.list, instructionSets);
            
            await loadDefinitions();
            overlay.style.display = 'none';
            alert(`Set "${newName}" saved and applied.`);
        }
    };

    overlay.style.display = 'flex';
}

async function openHtvmToHtvmModal() {
    const overlay = document.getElementById('modal-overlay');
    overlay.style.pointerEvents = 'auto';

    let instructionSets = await dbGet(instructionSetKeys.list) || [];
    let optionsHtml = instructionSets.map(s => `<option value="${s.id}">${s.name}</option>`).join('');

    overlay.innerHTML = `<div class="modal-box" style="max-width: 90vw; width: 1200px;">
        <h3>HTVM to HTVM Converter</h3>
        <p>This tool converts an HTVM file from one instruction set to another.</p>
        <div style="display: flex; gap: 15px; margin: 15px 0;">
            <div style="flex: 1;">
                <label>Source Instruction Set:</label>
                <select id="source-instr-select" style="width:100%;">${optionsHtml}</select>
            </div>
            <div style="flex: 1;">
                <label>Target Instruction Set:</label>
                <select id="target-instr-select" style="width:100%;">${optionsHtml}</select>
            </div>
        </div>
        <div style="display: flex; gap: 15px; height: 50vh;">
            <div style="flex: 1;"><label>Input HTVM Code:</label><div id="htvm-input-ace"></div></div>
            <div style="flex: 1;"><label>Output HTVM Code:</label><div id="htvm-output-ace"></div></div>
        </div>
        <div class="modal-buttons" style="margin-top:15px;">
            <button id="htvm-convert-cancel">Cancel</button>
            <button id="htvm-convert-run" class="modal-btn-confirm">Convert</button>
        </div>
    </div>`;

    const inputEditor = ace.edit("htvm-input-ace");
    const outputEditor = ace.edit("htvm-output-ace");
    [inputEditor, outputEditor].forEach(ed => {
        ed.setTheme("ace/theme/monokai");
        ed.session.setMode("ace/mode/htvm");
        ed.setOptions({ fontSize: '14px' });
    });
    outputEditor.setReadOnly(true);
    
    // Pre-fill with current file if it's an HTVM file
    if (currentOpenFile && currentOpenFile.endsWith('.htvm')) {
        inputEditor.setValue(editor.getValue(), -1);
    }
    
    document.getElementById('htvm-convert-cancel').onclick = () => { overlay.style.display = 'none'; };
    document.getElementById('htvm-convert-run').onclick = async () => {
        const sourceId = document.getElementById('source-instr-select').value;
        const targetId = document.getElementById('target-instr-select').value;
        if (!sourceId || !targetId) return alert("Please select both source and target instruction sets.");
        
        const sourceSet = await db.instructionSets.get(sourceId);
        const targetSet = await db.instructionSets.get(targetId);
        
        if (!sourceSet || !targetSet) return alert("Could not load instruction sets.");

        const htvmCode = inputEditor.getValue();
        argHTVMinstrMORE.push(sourceSet.content);
        argHTVMinstrMORE.push(targetSet.content);
        
        const convertedCode = await compiler(htvmCode, '', 'htvmTOhtvm', '');
        outputEditor.setValue(convertedCode, -1);
        resetGlobalVarsOfHTVMjs();
    };
    
    overlay.style.display = 'flex';
}

async function openLineMapperModal() {
    const overlay = document.getElementById('modal-overlay');
    overlay.style.pointerEvents = 'auto';

    overlay.innerHTML = `
        <div class="modal-box" style="max-width: 90vw; width: 1200px; display: flex; flex-direction: column; height: 90vh;">
            <h3>HTVM Line Mapper</h3>
            <div style="display: flex; gap: 15px; flex-grow: 1; margin-top: 10px; min-height: 0;">
                <div style="flex: 1; display: flex; flex-direction: column;">
                    <label for="mapper-htvm-code" style="margin-bottom: 5px;">HTVM Code</label>
                    <textarea id="mapper-htvm-code" style="flex-grow: 1; width: 100%; resize: none; background: #1e1e1e; color: #f0f0f0; border: 1px solid #333; font-family: monospace;"></textarea>
                </div>
                <div style="flex: 1; display: flex; flex-direction: column;">
                    <label for="mapper-target-code" style="margin-bottom: 5px;">Target Language Code</label>
                    <textarea id="mapper-target-code" style="flex-grow: 1; width: 100%; resize: none; background: #1e1e1e; color: #f0f0f0; border: 1px solid #333; font-family: monospace;"></textarea>
                </div>
            </div>
            <div style="display: flex; align-items: center; gap: 15px; margin-top: 15px; flex-shrink: 0;">
                <label for="mapper-target-line">Target Line Number:</label>
                <input type="number" id="mapper-target-line" style="width: 80px; background: #252525; color: #e0e0e0; border: 1px solid #333;" min="1">
                <button id="mapper-find-btn" class="modal-btn-confirm">Find Corresponding Line</button>
            </div>
            <div style="margin-top: 15px; flex-shrink: 0;">
                <label>Result:</label>
                <div id="mapper-result" style="background: #252525; padding: 10px; border-radius: 3px; min-height: 40px; white-space: pre-wrap; word-break: break-all; border: 1px solid #333;"></div>
            </div>
            <div class="modal-buttons" style="margin-top: 15px; flex-shrink: 0;">
                <button id="mapper-close-btn" class="modal-btn-cancel">Close</button>
            </div>
        </div>
    `;
    
    const htvmTextarea = document.getElementById('mapper-htvm-code');
    const targetTextarea = document.getElementById('mapper-target-code');
    const targetLineInput = document.getElementById('mapper-target-line');
    const findBtn = document.getElementById('mapper-find-btn');
    const resultDiv = document.getElementById('mapper-result');
    const closeBtn = document.getElementById('mapper-close-btn');

    closeBtn.onclick = () => overlay.style.display = 'none';
    
    findBtn.onclick = () => {
        const htvmCode = htvmTextarea.value;
        const targetCode = targetTextarea.value;
        const targetLine = targetLineInput.value;
        if (!htvmCode || !targetCode || !targetLine) {
            resultDiv.textContent = "Error: All fields (HTVM Code, Target Code, and Target Line) must be filled.";
            return;
        }
        try {
            const result = tryToMapHTVMlineToTargetLine(htvmCode, targetCode, targetLine);
            resultDiv.textContent = result;
        } catch (e) {
            resultDiv.textContent = `An error occurred: ${e.message}`;
            console.error(e);
        }
    };

    overlay.style.display = 'flex';

    // Simple Promise-based confirm/alert to avoid blocking and allow interaction with the underlying modal
    const showInteractivePrompt = (text, confirmText = "Yes", cancelText = "No") => {
        return new Promise(resolve => {
            const promptOverlay = document.createElement('div');
            promptOverlay.style.cssText = `position: absolute; top: 0; left: 0; right: 0; bottom: 0; background: rgba(0,0,0,0.6); z-index: 1002; display: flex; justify-content: center; align-items: center;`;
            
            const modalBox = overlay.querySelector('.modal-box'); // Get the main modal box
            
            promptOverlay.innerHTML = `
                <div class="modal-box" style="max-width: 450px; text-align: center;">
                    <p style="line-height: 1.5;">${text}</p>
                    <div class="modal-buttons" style="justify-content: center; display: flex;">
                        <button id="prompt-yes" class="modal-btn-confirm">${confirmText}</button>
                        ${cancelText ? `<button id="prompt-no" class="modal-btn-cancel">${cancelText}</button>` : ''}
                    </div>
                </div>`;
            
            modalBox.appendChild(promptOverlay);

            document.getElementById('prompt-yes').onclick = () => {
                modalBox.removeChild(promptOverlay);
                resolve(true);
            };
            if (cancelText) {
                document.getElementById('prompt-no').onclick = () => {
                    modalBox.removeChild(promptOverlay);
                    resolve(false);
                };
            }
        });
    };
    
    const showAlert = (text) => showInteractivePrompt(text, "OK", null);

    const isHtvmFile = currentOpenFile && currentOpenFile.endsWith('.htvm');

    if (isHtvmFile) {
        htvmTextarea.value = editor.getValue();
        const hasCopied = await showInteractivePrompt("The HTVM code has been pre-filled.<br><br>Have you copied the target language code to your clipboard?");
        if (hasCopied) {
            try {
                const clipboardText = await navigator.clipboard.readText();
                if (clipboardText) {
                    targetTextarea.value = clipboardText;
                    resultDiv.textContent = "Pasted target code from clipboard.";
                } else {
                    await showAlert("Your clipboard is empty. Please copy the target code and paste it manually.");
                }
            } catch (err) {
                 await showAlert("Could not read from clipboard. Please paste the target code manually.");
            }
        } else {
            await showAlert("Please copy the target language code, then return here and paste it into the right-hand box.");
        }
    } else { // Not an HTVM file
        targetTextarea.value = editor.getValue();
        const hasCopied = await showInteractivePrompt("The target language code has been pre-filled.<br><br>Have you copied the corresponding .htvm file's code to your clipboard?");
        if (hasCopied) {
            try {
                const clipboardText = await navigator.clipboard.readText();
                if (clipboardText) {
                    htvmTextarea.value = clipboardText;
                    resultDiv.textContent = "Pasted HTVM code from clipboard.";
                } else {
                    await showAlert("Your clipboard is empty. Please copy the HTVM code and paste it manually.");
                }
            } catch (err) {
                 await showAlert("Could not read from clipboard. Please paste the HTVM code manually.");
            }
        } else {
            await showAlert("Please copy the .htvm file's code, then return here and paste it into the left-hand box.");
        }
    }
}