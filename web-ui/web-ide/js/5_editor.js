// --- Editor and Tab Management ---

function setupGutterEvents() {
    editor.on("guttermousedown", function(e) {
        const target = e.domEvent.target;
        if (target.className.indexOf("ace_gutter-cell") == -1) return;
        if (!editor.isFocused()) return;
        if (e.clientX > 25 + target.getBoundingClientRect().left) return;

        const row = e.getDocumentPosition().row;
        const currentBreakpoints = fileBreakpoints.get(currentOpenFile) || new Set();

        if (currentBreakpoints.has(row)) {
            editor.session.clearBreakpoint(row);
            currentBreakpoints.delete(row);
        } else {
            editor.session.setBreakpoint(row, "ace_breakpoint");
            currentBreakpoints.add(row);
        }
        fileBreakpoints.set(currentOpenFile, currentBreakpoints);
        e.stop();
    });
}

// --- DEXIE MIGRATION: Made function async to load from DB ---
async function openFileInEditor(filename) {
    if (!filename || currentOpenFile === filename) return;
    if (currentOpenFile) {
        await saveFileContent(currentOpenFile, editor.getValue(), true);
        await dbSet('state_' + currentOpenFile, {
            scrollTop: editor.session.getScrollTop(),
            cursor: editor.getCursorPosition()
        });
    }

    if (!fileSessions.has(filename)) {
        const fileRecord = await db.files.get(filename);
        const content = fileRecord ? fileRecord.content : "";
        const mode = ace.require("ace/ext/modelist").getModeForPath(filename).mode;
        const session = ace.createEditSession(content, filename.endsWith('.htvm') ? 'ace/mode/htvm' : mode);
        session.on('change', () => checkDirtyState(filename));
        fileSessions.set(filename, session);
    }

    editor.setSession(fileSessions.get(filename));

    // RENDER BREAKPOINTS FOR THE OPENED FILE
    const breakpoints = fileBreakpoints.get(filename) || new Set();
    editor.session.clearBreakpoints();
    breakpoints.forEach(row => {
        editor.session.setBreakpoint(row, "ace_breakpoint");
    });

    const state = await dbGet('state_' + filename);
    if (state) {
        setTimeout(() => {
            editor.gotoLine(state.cursor.row + 1, state.cursor.column, false);
            editor.session.setScrollTop(state.scrollTop);
        }, 1);
    }

    editor.setReadOnly(false);
    editor.focus();
    currentOpenFile = filename;
    if (!openTabs.includes(filename)) openTabs.push(filename);

    await renderAll();
    await updateEditorModeForHtvm();
}


async function closeTab(filenameToClose, force = false) {
    if (!force && fileSessions.has(filenameToClose) && !fileSessions.get(filenameToClose).getUndoManager().isClean()) {
        if (!confirm("You have unsaved changes. Close anyway?")) return;
    }

    const index = openTabs.indexOf(filenameToClose);
    if (index === -1) return;

    if (!force) recentlyClosedTabs.push(filenameToClose);
    openTabs.splice(index, 1);

    if (currentOpenFile === filenameToClose) {
        currentOpenFile = null;
        if (openTabs.length > 0) {
            await openFileInEditor(openTabs[Math.max(0, index - 1)]);
        } else {
            editor.setSession(ace.createEditSession("// No file open."));
            editor.setReadOnly(true);
            document.getElementById('htvm-controls').style.display = 'none';
        }
    }
    await renderAll();
}

async function handleCloseTabRequest(filename) {
    if (!filename) return;
    if (fileSessions.has(filename)) {
        if (!fileSessions.get(filename).getUndoManager().isClean()) {
            await saveFileContent(filename, editor.getValue(), true);
        }
    }
    await closeTab(filename);
}

const handleReopenTab = async () => {
    const f = recentlyClosedTabs.pop();
    const allPaths = await getAllPaths();
    if (f && allPaths.includes(f)) {
        await openFileInEditor(f);
    }
};

async function getActiveInstructionSetContent() {
    const activeId = await dbGet(instructionSetKeys.activeId);
    if (activeId) {
        const instructionSet = await db.instructionSets.get(activeId);
        return instructionSet ? instructionSet.content : "";
    }
    return "";
}


async function updateEditorModeForHtvm() {
    const htvmControls = document.getElementById('htvm-controls');
    if (!currentOpenFile || !currentOpenFile.endsWith('.htvm')) {
        htvmControls.style.display = 'none';
        return;
    }
    htvmControls.style.display = 'flex';
    
    // --- DEXIE MIGRATION: Load instructions from DB ---
    const activeContent = await getActiveInstructionSetContent();
    if (!activeContent) return;
    const keywords = activeContent.split('\n');
    
    if (!keywords || keywords.length < 42) return;

    const currentLine = editor.getSelectionRange().start.row;
    const lines = editor.getValue().split('\n');
    
    const languageMarkers = {
        [keywords[12]]: { end: keywords[13], lang: "cpp" }, [keywords[14]]: { end: keywords[15], lang: "py" },
        [keywords[16]]: { end: keywords[17], lang: "js" }, [keywords[18]]: { end: keywords[19], lang: "go" },
        [keywords[20]]: { end: keywords[21], lang: "lua" }, [keywords[22]]: { end: keywords[23], lang: "cs" },
        [keywords[24]]: { end: keywords[25], lang: "java" }, [keywords[26]]: { end: keywords[27], lang: "kt" },
        [keywords[28]]: { end: keywords[29], lang: "rb" }, [keywords[30]]: { end: keywords[31], lang: "nim" },
        [keywords[32]]: { end: keywords[33], lang: "ahk" }, [keywords[34]]: { end: keywords[35], lang: "swift" },
        [keywords[36]]: { end: keywords[37], lang: "dart" }, [keywords[38]]: { end: keywords[39], lang: "ts" },
        [keywords[40]]: { end: keywords[41], lang: "groovy" }
    };

    const detectedBlocks = [];
    let currentBlock = null;

    for (let i = 0; i < lines.length; i++) {
        const line = lines[i];

        if (!currentBlock) {
            for (const marker in languageMarkers) {
                if (marker && marker !== 'undefined' && line.includes(marker)) {
                    currentBlock = {
                        start: i,
                        lang: languageMarkers[marker].lang,
                        endMarker: languageMarkers[marker].end
                    };
                    break;
                }
            }
        }
        
        if (currentBlock) {
            if (currentBlock.endMarker && currentBlock.endMarker !== 'undefined' && line.includes(currentBlock.endMarker)) {
                detectedBlocks.push({
                    start: currentBlock.start,
                    end: i,
                    lang: currentBlock.lang
                });
                currentBlock = null; 
            }
        }
    }
    
    if (currentBlock) {
         detectedBlocks.push({
            start: currentBlock.start,
            end: lines.length -1,
            lang: currentBlock.lang
        });
    }

    let lang = "htvm";
    for (const block of detectedBlocks) {
        if (currentLine >= block.start && currentLine <= block.end) {
            lang = block.lang;
            break;
        }
    }

    const modeMap = {'js':'javascript','py':'python','cpp':'c_cpp','go':'golang','lua':'lua','cs':'csharp','java':'java','kt':'kotlin','rb':'ruby','nim':'nim','ahk':'autohotkey','swift':'swift','dart':'dart','ts':'typescript','groovy':'groovy','htvm':'htvm'};
    const finalMode = `ace/mode/${modeMap[lang] || 'text'}`;

    // --- THE DEFINITIVE SLEDGEHAMMER FIX ---
    // The bug is a deep state corruption in the Ace session, caused by previous buggy code.
    // Smart checks are not enough. We must assume the session is poisoned and
    // forcefully tear down and rebuild the mode from scratch on every single cursor
    // move or tab switch inside an HTVM file. This is aggressive, but it guarantees
    // the corrupted state is destroyed and the highlighting works consistently.

    // 1. Force the mode to a neutral, temporary state. This destroys the old tokenizer.
    editor.session.setMode("ace/mode/text");

    // 2. Immediately apply the correct mode. This creates a brand new, clean tokenizer.
    editor.session.setMode(finalMode);
}