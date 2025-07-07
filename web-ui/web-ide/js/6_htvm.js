// --- HTVM and Code Execution ---

// --- DEXIE MIGRATION: Reworked instruction set management to use IndexedDB. ---
async function initializeInstructionSetManagement() {
    // This function handles the one-time migration from localStorage to IndexedDB.
    const legacyDataRaw = localStorage.getItem(instructionSetKeys.legacyKey);
    const instructionList = await dbGet(instructionSetKeys.list);

    if (legacyDataRaw && !instructionList) {
        const newId = 'default_migrated_' + Date.now();
        const newList = [{ name: 'Default', id: newId }];
        let legacyContentAsString = '';
        try {
            const legacyDataParsed = JSON.parse(legacyDataRaw);
            legacyContentAsString = Array.isArray(legacyDataParsed) ? legacyDataParsed.join('\n') : '';
        } catch {
            legacyContentAsString = legacyDataRaw;
        }

        await db.instructionSets.put({ id: newId, name: 'Default', content: legacyContentAsString });
        await dbSet(instructionSetKeys.list, newList);
        await dbSet(instructionSetKeys.activeId, newId);
        
        localStorage.removeItem(instructionSetKeys.legacyKey);
        console.log("Migrated legacy instruction set to new IndexedDB system.");
    }
}

// --- FIX: This function now reads from DB and passes content to its children ---
async function loadDefinitions() {
    // This is now the single source of truth for the active instruction set content.
    const instructionContent = await getActiveInstructionSetContent();
    
    // Pass the content directly to the mode and completer initializers.
    await window.initializeHtvmMode(IDE_ID, instructionContent);
    await window.initializeCompleters(IDE_ID, editor, instructionContent);
    
    // Refresh the editor if an htvm file is open
    if (editor && currentOpenFile && currentOpenFile.endsWith('.htvm')) {
        editor.session.setMode("ace/mode/text");
        editor.session.setMode("ace/mode/htvm");
    }
}

// --- SELF-CONTAINED DEBUGGER ---

let activeLineMarker = null;
function highlightLine(row) {
    clearHighlight();
    activeLineMarker = editor.session.addMarker(
        new ace.Range(row, 0, row, 1), "ace_debugger_active_line", "fullLine", true
    );
}

function clearHighlight() {
    if (activeLineMarker) {
        editor.session.removeMarker(activeLineMarker);
        activeLineMarker = null;
    }
}

async function __debug_pause__(line, scopeFn) {
    debuggerState.isPaused = true;
    debuggerState.scope = scopeFn();
    highlightLine(line);
    openDebuggerModal();

    return new Promise((resolve, reject) => {
        debuggerState.resolve = resolve;
        debuggerState.reject = reject;
    });
}

function stopDebugger() {
    if (debuggerState.reject) {
        debuggerState.reject(new Error("Execution stopped by user."));
    }
    debuggerState.isActive = false;
    debuggerState.isPaused = false;
    clearHighlight();
    printExecutionEndMessage();
}

function getDeclaredVariables(code) {
    const declared = new Set();
    let match;

    const varRegex = /(?:let|const|var)\s+([a-zA-Z0-9_$]+(?:\s*,\s*[a-zA-Z0-9_$]+)*)/g;
    while ((match = varRegex.exec(code)) !== null) {
        match[1].split(',').forEach(v => declared.add(v.trim()));
    }

    const forLoopRegex = /for\s*\(\s*(?:let|const|var)\s+([a-zA-Z0-9_$]+)\s+(in|of)/g;
    while ((match = forLoopRegex.exec(code)) !== null) {
        declared.add(match[1].trim());
    }

    const funcRegex = /(?:async\s+)?function\s+([a-zA-Z0-9_$]+)/g;
    while ((match = funcRegex.exec(code)) !== null) {
        declared.add(match[1].trim());
    }

    return Array.from(declared);
}

function getAllFunctionNames(code) {
    const names = new Set();
    const funcRegex = /function\s+([a-zA-Z0-9_$]+)\s*\(/g;
    let match;
    while ((match = funcRegex.exec(code)) !== null) {
        names.add(match[1]);
    }
    return Array.from(names);
}

function protectAndTransform(code, transformFn) {
    const placeholders = new Map();
    let placeholderId = 0;
    // Add a random component to the placeholder to make it "super unique"
    const runId = Math.random().toString(36).substring(2);
    
    const regex = /(["'`])(?:\\.|(?!\1).)*\1|\/\*[\s\S]*?\*\/|\/\/.*/g;

    let protectedCode = code.replace(regex, (match) => {
        const placeholder = `__DBG_PROTECT_${runId}_${placeholderId++}__`;
        placeholders.set(placeholder, match);
        return placeholder;
    });

    let transformedCode = transformFn(protectedCode);

    placeholders.forEach((original, placeholder) => {
        transformedCode = transformedCode.replace(new RegExp(placeholder, 'g'), original);
    });

    return transformedCode;
}

async function runJsCode(code) {
    term.writeln(`\x1b[1;33m--- JS Execution ---\x1b[0m`);
    const originalLog = window.console.log;

    debuggerState.isActive = true;
    debuggerState.isPaused = false;

    const script = document.createElement('script');
    const scriptId = `dynamic-script-${Date.now()}`;
    script.id = scriptId;

    const cleanup = async () => {
        const scriptToRemove = document.getElementById(scriptId);
        if (scriptToRemove) document.body.removeChild(scriptToRemove);
        delete window.__debug_pause__;
        delete window.__execution_resolver__;
        window.console.log = originalLog;
        if (debuggerState.isActive) {
            await printExecutionEndMessage();
        }
        debuggerState.isActive = false;
        debuggerState.isPaused = false;
        clearHighlight();
    };

    try {
        await new Promise((resolve, reject) => {
            window.__debug_pause__ = __debug_pause__;
            window.__execution_resolver__ = { resolve, reject };

            let codeToRun = code;
            const breakpoints = fileBreakpoints.get(currentOpenFile);

            if (breakpoints && breakpoints.size > 0) {
                term.writeln(`\x1b[36mDebugger attached. Transforming code for breakpoints.\x1b[0m`);

                const funcNames = getAllFunctionNames(codeToRun);
                
                codeToRun = protectAndTransform(codeToRun, (sanitizedCode) => {
                    let transformed = sanitizedCode.replace(/(?<!async\s)function(\s+[a-zA-Z0-9_$]*\s*\()/g, "async function$1");
                    transformed = transformed.replace(/(=|\:)\s*function(\s*\()/g, "$1 async function$2");

                    if (funcNames.length > 0) {
                        const callRegex = new RegExp(`(?<!function |async function |await )\\b(${funcNames.join('|')})\\b(?=\\s*\\()`, 'g');
                        transformed = transformed.replace(callRegex, 'await $&');
                    }
                    return transformed;
                });
                
                const lines = codeToRun.split('\n');
                const sortedBreakpoints = Array.from(breakpoints).sort((a, b) => b - a);
                const declaredVars = getDeclaredVariables(codeToRun);
                const scopeCapture = `(() => { const scope = {}; ${declaredVars.map(v => `try { if(typeof ${v} !== 'undefined') scope['${v}'] = ${v}; } catch(e){}`).join(' ')} return scope; })`;
                
                sortedBreakpoints.forEach(row => {
                    if(lines[row] !== undefined) {
                       lines.splice(row, 0, `await window.__debug_pause__(${row}, ${scopeCapture});`);
                    }
                });
                codeToRun = lines.join('\n');
            } else {
                 term.writeln(`\x1b[32mRunning code without debugger.\x1b[0m`);
            }

            window.console.log = (...args) => term.writeln(args.map(arg => typeof arg === 'object' ? JSON.stringify(arg, null, 2) : String(arg)).join(' '));
            
            script.type = 'module';
            script.textContent = 'try {\n' +
                                 codeToRun + '\n' +
                                 'window.__execution_resolver__.resolve();\n' +
                                 '} catch (e) {\n' +
                                 'window.__execution_resolver__.reject(e);\n' +
                                 '}';
            
            script.onerror = (err) => reject(new Error('Script execution failed. Check DevTools console (Ctrl+Shift+I) for syntax errors.'));
            document.body.appendChild(script);
        });
    } catch (e) {
        if (e.message !== "Execution stopped by user.") {
             term.writeln(`\x1b[31mError: ${e.message}\x1b[0m`);
        } else {
             term.writeln(`\x1b[33mExecution stopped by user.\x1b[0m`);
        }
    } finally {
        await cleanup();
    }
}

/**
 * Pre-processes HTVM code to find all `include` statements and load their content
 * into a cache recursively. This is necessary to bridge the gap between the
 * synchronous compiler and the asynchronous file system.
 * @param {string} source - The source code to scan.
 * @param {string} basePath - The directory of the source file, for resolving relative paths.
 * @param {Map<string, string|null>} cache - The cache to populate.
 * @param {Set<string>} processedFiles - A set of processed paths to prevent infinite loops.
 * @param {Function} asyncReader - The real async file reading function.
 */
async function preloadHtvmImports(source, basePath, cache, processedFiles, asyncReader) {
    const canonicalPath = window.resolveHtvmPath(basePath, '/');
    if (processedFiles.has(canonicalPath)) {
        return; // Already processed, stop to prevent circular recursion
    }
    processedFiles.add(canonicalPath);

    const includeRegex = /^include\s+(.+)/gmi;
    const matches = [...source.matchAll(includeRegex)];

    for (const match of matches) {
        const importPath = match[1].trim();
        const absoluteImportPath = window.resolveHtvmPath(importPath, basePath);
        
        if (!cache.has(absoluteImportPath)) {
            const fileContent = await asyncReader(absoluteImportPath);
            cache.set(absoluteImportPath, fileContent); // Cache success or failure (null)
            if (fileContent !== null) {
                // If file was found, scan it for more includes
                const newBasePath = absoluteImportPath.substring(0, absoluteImportPath.lastIndexOf('/') + 1);
                await preloadHtvmImports(fileContent, newBasePath, cache, processedFiles, asyncReader);
            }
        }
    }
}

async function formatHtvmCode(code) {
    let instructionSetContent = await getActiveInstructionSetContent();
    let instructionSet = instructionSetContent.split('\n');
    
    term.writeln(`\x1b[32mFormatting HTVM file...\x1b[0m`);
    resetGlobalVarsOfHTVMjs();

    // The formatter might also use includes, so we apply the same pre-loading logic.
    const originalAsyncFileRead = window.FileRead;
    const importCache = new Map();
    const currentPath = currentOpenFile ? currentOpenFile.substring(0, currentOpenFile.lastIndexOf('/') + 1) : '/';
    await preloadHtvmImports(code, currentPath, importCache, new Set(), originalAsyncFileRead);
    
    window.FileRead = (path) => {
        const resolvedPath = window.resolveHtvmPath(path, currentPath);
        return importCache.has(resolvedPath) ? importCache.get(resolvedPath) : null;
    };

    resetGlobalVarsOfHTVMjs();    
    argHTVMinstrMORE.push(instructionSet.join('\n'));
    const formattedCode = await compiler(code, instructionSet.join('\n'), "full", "htvm");
    resetGlobalVarsOfHTVMjs();
    
    // Restore the original async reader
    window.FileRead = originalAsyncFileRead;
    
    term.writeln(`\x1b[32mFormatting complete.\x1b[0m`);
    return formattedCode;
}

async function runHtvmCode(code) {
    resetGlobalVarsOfHTVMjs();
    const lang = await dbGet('selectedLangExtension') || 'js';

    // Set the base directory for the main file being executed.
    if (currentOpenFile) {
        const lastSlash = currentOpenFile.lastIndexOf('/');
        window.currentHtvmFileDirectory = lastSlash === -1 ? '/' : currentOpenFile.substring(0, lastSlash + 1);
    } else {
        window.currentHtvmFileDirectory = '/';
    }
    
    let instructionSetContent = await getActiveInstructionSetContent();
    let instructionSet = instructionSetContent.split('\n');
    const isFullHtml = lang === 'js' && document.getElementById('full-html-checkbox').checked;

    if (isFullHtml && Array.isArray(instructionSet) && instructionSet.length > 158) {
        instructionSet[158] = "on";
    }
    
    term.writeln(`\x1b[32mTranspiling HTVM to ${isFullHtml ? 'HTML' : lang.toUpperCase()}...\x1b[0m`);
    
    // --- Pre-load all includes before compiling ---
    const originalAsyncFileRead = window.FileRead;
    const importCache = new Map();
    // Start pre-loading from the main source code and its directory
    await preloadHtvmImports(code, window.currentHtvmFileDirectory, importCache, new Set(), originalAsyncFileRead);

    // --- Temporarily replace FileRead with a synchronous cache lookup ---
    window.FileRead = (path) => {
        const resolvedPath = window.resolveHtvmPath(path, window.currentHtvmFileDirectory);
        return importCache.get(resolvedPath);
    };

    // --- Call the synchronous compiler ---
    const compiled = await compiler(code, instructionSet.join('\n'), "full", lang);
    
    // --- Restore the original async FileRead function ---
    window.FileRead = originalAsyncFileRead;
    resetGlobalVarsOfHTVMjs();
    
    const newFileExt = isFullHtml ? 'html' : lang;
    const newFile = currentOpenFile.replace(/\.htvm$/, `.${newFileExt}`);

    const wasAlreadyOpen = openTabs.includes(newFile);

    if (fileSessions.has(newFile)) {
        fileSessions.delete(newFile);
    }

    await saveFileContent(newFile, compiled, false);

    if (!wasAlreadyOpen) {
        await openFileInEditor(newFile);
    }
    
    const shouldRunAfter = (await dbGet('runJsAfterHtvm')) !== false;
    if (shouldRunAfter) {
        if (isFullHtml) {
            runHtmlCode(compiled);
        } else if (lang === 'js') {
            await runJsCode(compiled);
        } else {
            await printExecutionEndMessage();
        }
    } else {
        await printExecutionEndMessage();
    }
}

async function handleRun(e) {
    e?.preventDefault();
    if (!currentOpenFile) return;

    if (debuggerState.isActive) {
        term.writeln(`\x1b[31mError: Cannot start a new execution while the debugger is active.\x1b[0m`);
        term.writeln(`\x1b[33mPlease 'Resume' or 'Stop' the current debugging session first.\x1b[0m`);
        term.write('$ ');
        return;
    }
    
    const clearOnRun = await dbGet('clearTerminalOnRun');
    if (clearOnRun === true) {
        term.clear();
    }

    await saveFileContent(currentOpenFile, editor.getValue());
    term.writeln(`\x1b[36m> Running ${currentOpenFile}...\x1b[0m`);
    const ext = currentOpenFile.split('.').pop();
    
    if (ext === 'js') await runJsCode(editor.getValue());
    else if (ext === 'htvm') await runHtvmCode(editor.getValue());
    else if (ext === 'html') runHtmlCode(editor.getValue());
    else {
        term.writeln(`\x1b[31mError: Cannot execute ".${ext}" files.\x1b[0m`);
        await printExecutionEndMessage();
    }
}