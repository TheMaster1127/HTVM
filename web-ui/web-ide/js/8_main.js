// --- DEXIE MIGRATION: Reworked the entire main file to be async first. ---

let hotkeyListener = null; // Keep a reference to the listener to remove it later

async function applyAndSetHotkeys() {
    // Remove the old listener to prevent duplicates
    if (hotkeyListener) {
        document.removeEventListener('keydown', hotkeyListener);
    }

    const customHotkeys = await dbGet('customHotkeys') || {};
    
    // Merge custom hotkeys with defaults
    const activeHotkeys = {};
    for (const id in hotkeyConfig) {
        activeHotkeys[id] = customHotkeys[id] || hotkeyConfig[id].default;
    }

    hotkeyListener = async (e) => {
        // F5 is a special, non-customizable secondary key for Run
        if (e.key === 'F5') {
            e.preventDefault();
            await handleRun(e);
            return;
        }

        const checkMatch = (config) => {
            if (!config) return false;
            const key = e.key.toLowerCase();
            const targetKey = config.key.toLowerCase();
            if (key !== targetKey && e.key !== config.key) return false;
            const ctrl = e.ctrlKey || e.metaKey;
            return ctrl === config.ctrl && e.shiftKey === config.shift && e.altKey === config.alt;
        };

        if (checkMatch(activeHotkeys.runFile)) {
            e.preventDefault(); await handleRun(e);
        } else if (checkMatch(activeHotkeys.saveFile)) {
            e.preventDefault(); await saveFileContent(currentOpenFile, editor.getValue());
        } else if (checkMatch(activeHotkeys.formatFile)) {
            e.preventDefault();
            if (!currentOpenFile || !currentOpenFile.endsWith('.htvm')) {
                alert("The formatter only works with .htvm files.");
                return;
            }
            try {
                const formatted = await formatHtvmCode(editor.getValue());
                editor.session.setValue(formatted);
            } catch (err) {
                term.writeln(`\x1b[31mAn error occurred during formatting: ${err.message}\x1b[0m`);
            }
        } else if (checkMatch(activeHotkeys.closeTab)) {
            e.preventDefault(); await handleCloseTabRequest(currentOpenFile);
        } else if (checkMatch(activeHotkeys.reopenTab)) {
            e.preventDefault(); await handleReopenTab();
        } else if (checkMatch(activeHotkeys.toggleSidebar)) {
            e.preventDefault(); document.getElementById('main-toggle-sidebar-btn').click();
        }
    };

    document.addEventListener('keydown', hotkeyListener);
    await updateHotkeyTitles();
}

document.addEventListener('DOMContentLoaded', async () => {
    // --- Initialization ---
    IDE_ID = getIdeId();
    langTools = ace.require("ace/ext/language_tools");
    
    // --- DEXIE MIGRATION: Database setup is the very first step ---
    setupDatabase(IDE_ID);

    // Apply custom themes and colors before editor initialization
    await applyEditorColorSettings();
    await applyUiThemeSettings();

    // Initialize core components
    editor = ace.edit("editor");
    term = new Terminal({ cursorBlink: true, fontFamily: 'monospace', fontSize: 13, theme: { background: '#000000', foreground: '#00DD00', cursor: '#00FF00' } });
    fitAddon = new FitAddon.FitAddon();
    term.loadAddon(fitAddon);
    term.open(document.getElementById('terminal'));
    fitAddon.fit();

    // Populate language completions into localStorage (this is fine, as it's not workspace-specific data)
    Object.keys(draftCompletions).forEach(lang => {
        localStorage.setItem(`lang_completions_${lang}`, JSON.stringify(draftCompletions[lang]));
    });

    // Load HTVM definitions and instruction sets
    await initializeInstructionSetManagement();
    
    // Check for instruction set and start onboarding if necessary.
    const instructionList = await dbGet(instructionSetKeys.list) || [];
    let shouldShowPrompt = false;
    
    if (instructionList.length === 0) {
        // Condition 1: No instruction sets exist at all.
        shouldShowPrompt = true;
    } else if (instructionList.length === 1 && instructionList[0].name === 'Default') {
        // Condition 2: The only set is the migrated "Default" one.
        shouldShowPrompt = true;
    }

    if (shouldShowPrompt) {
        await promptForInitialInstructionSet();
    } else {
        await loadDefinitions();
    }

    // Configure Ace Editor based on settings from DB
    editor.setTheme("ace/theme/monokai");
    editor.setOptions({
        enableBasicAutocompletion: true,
        enableLiveAutocompletion: true,
        behavioursEnabled: await dbGet('autoPair') !== false,
        wrap: true,
        printMargin: await dbGet('printMarginColumn') || 80
    });
    editor.setShowPrintMargin(await dbGet('showPrintMargin') ?? true);
    editor.setFontSize(parseInt(await dbGet('fontSize') || 14, 10));

    const keybindingMode = await dbGet('keybindingMode') || 'normal';
    if (keybindingMode !== 'normal') {
        editor.setKeyboardHandler(`ace/keyboard/${keybindingMode}`);
    }
    
    setupGutterEvents();

    // --- Event Listeners ---
    editor.on('changeSelection', debounce(updateEditorModeForHtvm, 200));

    // Sidebar and Top Bar listeners
    document.getElementById('new-file-btn').onclick = handleNewFile;
    document.getElementById('new-folder-btn').onclick = handleNewFolder;
    document.getElementById('save-session-btn').onclick = () => openSessionModal('save');
    document.getElementById('load-session-btn').onclick = () => openSessionModal('load');
    document.getElementById('settings-btn').onclick = openSettingsModal;
    document.getElementById('load-instructions-btn').onclick = openInstructionManagerModal;
    document.getElementById('htvm-to-htvm-btn').onclick = openHtvmToHtvmModal;
    document.getElementById('export-import-btn').onclick = openExportImportModal;
    document.getElementById('open-folder-btn').onclick = () => alert("This feature is for the desktop version.");
    
    const toggleBtn = document.getElementById('main-toggle-sidebar-btn');
    const sidebar = document.querySelector('.sidebar');
    const backdrop = document.getElementById('sidebar-backdrop');
    const closeBtn = document.getElementById('sidebar-close-btn');

    async function toggleSidebar() {
        const isCollapsed = sidebar.classList.contains('collapsed');
        sidebar.classList.toggle('collapsed');
        await dbSet('sidebarCollapsed', !isCollapsed);

        const isMobileView = getComputedStyle(sidebar).position === 'absolute';
        if (isMobileView) {
            backdrop.style.display = isCollapsed ? 'block' : 'none';
        }

        setTimeout(() => { editor.resize(); fitAddon.fit(); }, 310);
    }

    toggleBtn.onclick = toggleSidebar;
    backdrop.onclick = toggleSidebar;
    closeBtn.onclick = toggleSidebar;

    // HTVM controls listeners
    document.getElementById('lang-dropdown').addEventListener('click', e => {
        const item = e.target.closest('.dropdown-item');
        if (item) changeLanguage(item.dataset.name, item.dataset.img, item.dataset.lang);
    });
    document.getElementById('run-js-after-htvm').checked = await dbGet('runJsAfterHtvm') !== false;
    document.getElementById('run-js-after-htvm').onchange = e => dbSet('runJsAfterHtvm', e.target.checked);
    document.getElementById('full-html-checkbox').checked = await dbGet('fullHtml') === true;
    document.getElementById('full-html-checkbox').onchange = e => dbSet('fullHtml', e.target.checked);

    // Run and Output Panel listeners
    document.getElementById('run-btn').onclick = handleRun;
    document.getElementById('format-btn').onclick = async () => {
        if (!currentOpenFile || !currentOpenFile.endsWith('.htvm')) {
            alert("The formatter only works with .htvm files.");
            return;
        }
        try {
            const formatted = await formatHtvmCode(editor.getValue());
            editor.session.setValue(formatted);
        } catch (err) {
            term.writeln(`\x1b[31mAn error occurred during formatting: ${err.message}\x1b[0m`);
        }
    };
    document.getElementById('close-output-btn').onclick = () => document.getElementById('output-panel').classList.remove('visible');
    document.getElementById('download-html-btn').onclick = handleDownloadHtml;

    // Apply custom hotkeys on startup
    await applyAndSetHotkeys();
    
    // Resizers
    initResizer(document.getElementById('sidebar-resizer'), document.querySelector('.sidebar'), 'sidebarWidth', 'x');
    initResizer(document.getElementById('terminal-resizer'), document.getElementById('terminal-container'), 'terminalHeight', 'y');
    initResizer(document.getElementById('output-panel-resizer'), document.getElementById('output-panel'), 'outputPanelWidth', 'x');

    // --- Application Startup Logic ---
    term.writeln(`\x1b[1;32mWelcome to HT-IDE! (Workspace ID: ${IDE_ID})\x1b[0m`);
    term.write('$ ');

    const savedBreakpoints = await dbGet('fileBreakpoints');
    if (savedBreakpoints) {
        for (const file in savedBreakpoints) {
            fileBreakpoints.set(file, new Set(savedBreakpoints[file]));
        }
    }

    // Restore UI state from DB
    const sidebarWidth = await dbGet('sidebarWidth'); if (sidebarWidth) document.querySelector('.sidebar').style.width = sidebarWidth;
    const terminalHeight = await dbGet('terminalHeight'); if (terminalHeight) document.getElementById('terminal-container').style.height = terminalHeight;
    const outputWidth = await dbGet('outputPanelWidth'); if (outputWidth) document.getElementById('output-panel').style.width = outputWidth;
    
    if (await dbGet('sidebarCollapsed') === true) {
        document.querySelector('.sidebar').classList.add('collapsed');
    } else {
        document.querySelector('.sidebar').classList.remove('collapsed');
    }

    const savedLang = await dbGet('selectedLangExtension');
    if (savedLang) {
        const item = document.querySelector(`.dropdown-item[data-lang="${savedLang}"]`);
        if (item) {
            document.getElementById('selected-lang-name').textContent = item.dataset.name;
            document.getElementById('selected-lang-img').src = item.dataset.img;
        }
    }

    // Restore file state
    const allKnownPaths = await getAllPaths();
    const lastCwd = await dbGet('lastCwd') || '/';
    await setCurrentDirectory(lastCwd);
    const savedOpenTabs = await dbGet('openTabs') || [];
    openTabs = savedOpenTabs.filter(f => allKnownPaths.includes(f));
    const lastFile = await dbGet('lastOpenFile');

    if (lastFile && allKnownPaths.includes(lastFile)) {
        await openFileInEditor(lastFile);
    } else if (openTabs.length > 0) {
        await openFileInEditor(openTabs[0]);
    } else {
        editor.setSession(ace.createEditSession("// No file open."));
        editor.setReadOnly(true);
        renderTabs();
    }

    // Window Listeners
    window.addEventListener('resize', debounce(() => {
        editor.resize();
        fitAddon.fit();

        const sidebar = document.querySelector('.sidebar');
        const backdrop = document.getElementById('sidebar-backdrop');
        const isDesktopView = getComputedStyle(sidebar).position !== 'absolute';
        if (isDesktopView) {
            backdrop.style.display = 'none';
        }
    }, 200));

    window.onbeforeunload = async () => {
        if (currentOpenFile) {
            await saveFileContent(currentOpenFile, editor.getValue(), true);
            await dbSet('state_' + currentOpenFile, { scrollTop: editor.session.getScrollTop(), cursor: editor.getCursorPosition() });
        }
        await dbSet('openTabs', openTabs);
        await dbSet('lastOpenFile', currentOpenFile);
        await dbSet('lastCwd', currentDirectory);

        const serializableBreakpoints = {};
        for (const [file, bpSet] of fileBreakpoints.entries()) {
            serializableBreakpoints[file] = Array.from(bpSet);
        }
        await dbSet('fileBreakpoints', serializableBreakpoints);
    };

    editor.on('mousemove', function (e) {
        const tooltip = document.getElementById('value-tooltip');
        if (!tooltip || !debuggerState.isPaused) {
            if (tooltip) tooltip.style.display = 'none';
            return;
        }
        
        const pos = e.getDocumentPosition();
        const token = editor.session.getTokenAt(pos.row, pos.column);

        if (token && (token.type.includes('variable') || token.type.includes('identifier'))) {
            const varName = token.value;
            if (debuggerState.scope && debuggerState.scope.hasOwnProperty(varName)) {
                let value = debuggerState.scope[varName];
                try {
                    value = JSON.stringify(value, null, 2);
                    if (value && value.length > 200) {
                        value = value.substring(0, 200) + '...';
                    }
                } catch {
                    value = String(value);
                }

                tooltip.innerText = `${varName}: ${value}`;
                tooltip.style.display = 'block';
                tooltip.style.left = (e.clientX + 15) + 'px';
                tooltip.style.top = (e.clientY + 15) + 'px';
            } else {
                tooltip.style.display = 'none';
            }
        } else {
            tooltip.style.display = 'none';
        }
    });

    setTimeout(() => {
        document.body.classList.remove('preload');
        fitAddon.fit();
    }, 50);
});

async function applyEditorColorSettings() {
    if (await dbGet('syntaxHighlightingEnabled') === false) {
        document.body.classList.add('syntax-highlighting-disabled');
    } else {
        document.body.classList.remove('syntax-highlighting-disabled');
    }

    const root = document.documentElement;
    for (const key in syntaxColorConfig) {
        const item = syntaxColorConfig[key];
        const savedColor = await dbGet(`color_${key}`) || item.default;
        root.style.setProperty(`--${key}`, savedColor);
        if (item.isText) {
            const isBold = await dbGet(`boldness_${key}`) ?? item.defaultBold;
            root.style.setProperty(`--${key}-font-weight`, isBold ? 'bold' : 'normal');
        }
    }
}

async function applyUiThemeSettings() {
    const root = document.documentElement;
    for (const key in uiThemeConfig) {
        const item = uiThemeConfig[key];
        const savedValue = await dbGet(`theme_${key}`) ?? item.default;
        const unit = item.unit || '';
        root.style.setProperty(key, savedValue + unit);
        if (item.hasBoldToggle) {
            const isBold = await dbGet(`theme_bold_${key}`) ?? item.defaultBold;
            root.style.setProperty(key + '-bold', isBold ? 'bold' : 'normal');
        }
    }
}