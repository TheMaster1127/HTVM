// --- Storage Helpers ---
const getIdeId = () => new URLSearchParams(window.location.search).get('id') ?? '0';

// --- DEXIE MIGRATION: Replaced localStorage helpers with async Dexie functions ---

// Old localStorage functions (for reference, no longer used for workspace data)
// const lsGet = key => { try { const i = localStorage.getItem(STORAGE_PREFIX + key); return i ? JSON.parse(i) : null; } catch { return null; } };
// const lsSet = (key, value) => { try { localStorage.setItem(STORAGE_PREFIX + key, JSON.stringify(value)); } catch (e) { console.error(e); } };
// const lsRemove = key => localStorage.removeItem(STORAGE_PREFIX + key);

async function dbGet(key) {
    try {
        const item = await db.settings.get(key);
        return item ? item.value : null;
    } catch (error) {
        console.error(`Failed to get key "${key}" from IndexedDB`, error);
        return null;
    }
}

async function dbSet(key, value) {
    try {
        await db.settings.put({ key, value });
    } catch (error)
    {
        console.error(`Failed to set key "${key}" in IndexedDB`, error);
    }
}

async function dbRemove(key) {
    try {
        await db.settings.delete(key);
    } catch (error) {
        console.error(`Failed to remove key "${key}" from IndexedDB`, error);
    }
}


// --- Configuration ---
// Note: instructionSetKeys are now used as keys in the 'settings' and 'instructionSets' tables
const instructionSetKeys = {
    list: 'instruction_sets_list',
    activeId: 'active_instruction_set_id',
    legacyKey: `htvm_lang_${getIdeId()}` // Kept for one-time migration logic
};

const hotkeyConfig = {
    runFile:      { label: 'Run File', default: { key: 'Enter', ctrl: true, shift: false, alt: false }, secondary: { key: 'F5', ctrl: false, shift: false, alt: false } },
    saveFile:     { label: 'Save File', default: { key: 's', ctrl: true, shift: false, alt: false } },
    formatFile:   { label: 'Format HTVM File', default: { key: 'f', ctrl: true, shift: true, alt: false } },
    closeTab:     { label: 'Close Tab', default: { key: 'w', ctrl: true, shift: false, alt: false } },
    reopenTab:    { label: 'Re-open Last Closed Tab', default: { key: 't', ctrl: true, shift: true, alt: false } },
    toggleSidebar:{ label: 'Toggle Sidebar', default: { key: 'b', ctrl: true, shift: false, alt: false } },
};

const syntaxColorConfig = {
    'ace-color-command':         { label: 'HTVM Commands',              default: '#569cd6', isText: true, defaultBold: true },
    'ace-color-keyword':         { label: 'Keywords',                   default: '#8080e0', isText: true, defaultBold: true },
    'ace-color-functions':       { label: 'Functions',                  default: '#80dfff', isText: true, defaultBold: false },
    'ace-color-buildin-func':    { label: 'Built-in Variables (A_...)', default: '#ff80df', isText: true, defaultBold: false },
    'ace-color-comment':         { label: 'Comments',                   default: '#40d080', isText: true, defaultBold: false },
    'ace-color-blocks-import':   { label: 'Programming Blocks & Imports', default: '#f51000', isText: true, defaultBold: true },
    'ace-color-static-types':    { label: 'Static Types',               default: '#569cd6', isText: true, defaultBold: true },
    'ace-color-string':          { label: 'Strings',                    default: '#ffa0a0', isText: true, defaultBold: false },
    'ace-color-operators':       { label: 'Operators',                  default: '#40a0e0', isText: true, defaultBold: true },
    'ace-color-true-false-null-etc': { label: 'True, False, null etc...', default: '#00ffff', isText: true, defaultBold: false },
    'ace-color-array-methods':   { label: 'Array Methods',              default: '#fab820', isText: true, defaultBold: false },
    'ace-color-gui-options':     { label: 'GUI Options',                default: '#a6e22e', isText: true, defaultBold: false },
    'ace-gutter-text':           { label: 'Gutter Text Color',          default: '#cbcdc3', isText: true, defaultBold: false },
    'ace-gutter-background':     { label: 'Gutter Background',          default: '#204020', isText: false, defaultBold: false },
    'ace-active-line':           { label: 'Active Line Highlight',      default: '#103010', isText: false, defaultBold: false },
    'ace-background':            { label: 'Editor Background',          default: '#050505', isText: false, defaultBold: false },
};

const uiThemeConfig = {
    // --- General Category ---
    '--modal-bg': { label: 'Modal Background', default: '#1e1e1e', type: 'color', category: 'General', description: 'Background color for pop-up dialog boxes like Settings or Session Manager.' },
    '--modal-header-text': { label: 'Modal Header Text', default: '#ffffff', type: 'color', category: 'General', description: 'Color of the title text inside modals (e.g., "Settings + Help").', hasBoldToggle: true, defaultBold: true },
    '--modal-confirm-btn-bg': { label: 'Modal "Save" Button BG', default: '#3d8b40', type: 'color', category: 'General', description: 'Background color for confirmation buttons in modals, like "Save & Apply".' },
    '--modal-confirm-btn-text': { label: 'Modal "Save" Button Text', default: '#ffffff', type: 'color', category: 'General', description: 'Text color for confirmation buttons in modals.', hasBoldToggle: true, defaultBold: true },
    '--modal-cancel-btn-bg': { label: 'Modal "Cancel" Button BG', default: '#555555', type: 'color', category: 'General', description: 'Background color for cancellation buttons in modals.' },
    '--modal-cancel-btn-text': { label: 'Modal "Cancel" Button Text', default: '#ffffff', type: 'color', category: 'General', description: 'Text color for cancellation buttons in modals.', hasBoldToggle: true, defaultBold: false },
    '--modal-reset-btn-bg': { label: 'Modal "Reset" Button BG', default: '#c12a2a', type: 'color', category: 'General', description: 'Background color for "Reset to Defaults" buttons.' },
    '--modal-reset-btn-text': { label: 'Modal "Reset" Button Text', default: '#ffffff', type: 'color', category: 'General', description: 'Text color for "Reset to Defaults" buttons.', hasBoldToggle: true, defaultBold: false },

    // --- Sidebar Buttons Category ---
    '--btn-new-file-bg': { label: '"New File" BG', default: '#0e639c', type: 'color', category: 'Sidebar Buttons', description: 'Background color for the "New File" button in the sidebar.' },
    '--btn-new-file-text': { label: '"New File" Text', default: '#ffffff', type: 'color', category: 'Sidebar Buttons', description: 'Text color for the "New File" button.', hasBoldToggle: true, defaultBold: false },
    '--btn-new-folder-bg': { label: '"New Folder" BG', default: '#fe6619', type: 'color', category: 'Sidebar Buttons', description: 'Background color for the "New Folder" button in the sidebar.' },
    '--btn-new-folder-text': { label: '"New Folder" Text', default: '#ffffff', type: 'color', category: 'Sidebar Buttons', description: 'Text color for the "New Folder" button.', hasBoldToggle: true, defaultBold: false },
    '--btn-save-session-bg': { label: '"Save Session" BG', default: '#2c2c2c', type: 'color', category: 'Sidebar Buttons', description: 'Background color for the "Save Session" button.' },
    '--btn-save-session-text': { label: '"Save Session" Text', default: '#ffffff', type: 'color', category: 'Sidebar Buttons', description: 'Text color for the "Save Session" button.', hasBoldToggle: true, defaultBold: false },
    '--btn-load-session-bg': { label: '"Load Session" BG', default: '#2c2c2c', type: 'color', category: 'Sidebar Buttons', description: 'Background color for the "Load Session" button.' },
    '--btn-load-session-text': { label: '"Load Session" Text', default: '#ffffff', type: 'color', category: 'Sidebar Buttons', description: 'Text color for the "Load Session" button.', hasBoldToggle: true, defaultBold: false },
    '--btn-settings-bg': { label: '"Settings" BG', default: '#2c2c2c', type: 'color', category: 'Sidebar Buttons', description: 'Background color for the "Settings" button.' },
    '--btn-settings-text': { label: '"Settings" Text', default: '#ffffff', type: 'color', category: 'Sidebar Buttons', description: 'Text color for the "Settings" button.', hasBoldToggle: true, defaultBold: false },
    '--btn-manage-instr-bg': { label: '"Manage Instructions" BG', default: '#2a8f2a', type: 'color', category: 'Sidebar Buttons', description: 'Background color for the "Manage Instructions" button in the sidebar footer.' },
    '--btn-manage-instr-text': { label: '"Manage Instructions" Text', default: '#ffffff', type: 'color', category: 'Sidebar Buttons', description: 'Text color for the "Manage Instructions" button.', hasBoldToggle: true, defaultBold: false },
    '--btn-htvm-to-htvm-bg': { label: '"HTVM to HTVM" BG', default: '#6a0dad', type: 'color', category: 'Sidebar Buttons', description: 'Background color for the "HTVM to HTVM" converter button.' },
    '--btn-htvm-to-htvm-text': { label: '"HTVM to HTVM" Text', default: '#ffffff', type: 'color', category: 'Sidebar Buttons', description: 'Text color for the "HTVM to HTVM" button.', hasBoldToggle: true, defaultBold: false },
    '--btn-export-import-bg': { label: '"Export/Import" BG', default: '#c12a2a', type: 'color', category: 'Sidebar Buttons', description: 'Background for the "Export/Import" button.' },
    '--btn-export-import-text': { label: '"Export/Import" Text', default: '#ffffff', type: 'color', category: 'Sidebar Buttons', description: 'Text for the "Export/Import" button.', hasBoldToggle: true, defaultBold: false },
    '--btn-open-folder-bg': { label: '"Open New Folder" BG', default: '#0e639c', type: 'color', category: 'Sidebar Buttons', description: 'Background color for the "Open New Folder" button.' },
    '--btn-open-folder-text': { label: '"Open New Folder" Text', default: '#ffffff', type: 'color', category: 'Sidebar Buttons', description: 'Text color for the "Open New Folder" button.', hasBoldToggle: true, defaultBold: false },

    // --- Sidebar Category ---
    '--sidebar-bg': { label: 'Sidebar Background', default: '#121212', type: 'color', category: 'Sidebar', description: 'The main background color of the file explorer sidebar.' },
    '--sidebar-header-text': { label: '"Files" Title Text', default: '#e0e0e0', type: 'color', category: 'Sidebar', description: 'The color of the "Files" title text at the top of the sidebar.', hasBoldToggle: true, defaultBold: true },
    '--sidebar-path-bg': { label: 'Current Path Background', default: '#1a1a1a', type: 'color', category: 'Sidebar', description: 'Background for the current directory path display (e.g., "/src/files/").' },
    '--sidebar-path-text': { label: 'Current Path Text', default: '#ffffff', type: 'color', category: 'Sidebar', description: 'Text color for the current directory path display.', hasBoldToggle: true, defaultBold: false },
    '--sidebar-file-text': { label: 'File List Text', default: '#e0e0e0', type: 'color', category: 'Sidebar', description: 'The text color for file and folder names in the list.', hasBoldToggle: true, defaultBold: false },
    '--sidebar-file-hover-bg': { label: 'File Item Hover BG', default: '#1f1f1f', type: 'color', category: 'Sidebar', description: 'The background color that appears when you hover your mouse over a file or folder.' },
    '--sidebar-file-active-bg': { label: 'Active File Background', default: '#005f87', type: 'color', category: 'Sidebar', description: 'The background color for the currently selected file in the sidebar list.' },
    '--sidebar-file-active-text': { label: 'Active File Text', default: '#ffffff', type: 'color', category: 'Sidebar', description: 'The text color for the currently selected file in the sidebar list.', hasBoldToggle: true, defaultBold: false },
    '--main-toggle-btn-color': { label: 'Toggle Sidebar Icon (☰)', default: '#e0e0e0', type: 'color', category: 'Sidebar', description: 'The color of the "hamburger" menu icon (☰) used to toggle the sidebar.' },
    '--sidebar-close-btn-color': { label: 'Mobile Close Icon (X)', default: '#e0e0e0', type: 'color', category: 'Sidebar', description: 'The color of the "X" button used to close the sidebar on mobile devices.' },

    // --- Top Bar ---
    '--top-bar-bg': { label: 'Top Bar Background', default: '#1a1a1a', type: 'color', category: 'Top Bar', description: 'The background color of the top bar that contains the tabs and run button.' },
    '--run-btn-bg': { label: '▶ Run Button BG', default: '#3d8b40', type: 'color', category: 'Top Bar', description: 'Background color for the main "▶ Run" button in the top bar.' },
    '--run-btn-text': { label: '▶ Run Button Text', default: '#ffffff', type: 'color', category: 'Top Bar', description: 'Text color for the "▶ Run" button.', hasBoldToggle: true, defaultBold: true },
    '--btn-format-bg': { label: 'Format Button BG (Mobile)', default: '#3d8b40', type: 'color', category: 'Top Bar', description: 'Background color for the "Format" button in the top bar (visible on mobile only).' },
    '--btn-format-text': { label: 'Format Button Text (Mobile)', default: '#ffffff', type: 'color', category: 'Top Bar', description: 'Text color for the "Format" button.', hasBoldToggle: true, defaultBold: true },
    '--htvm-lang-selector-text': { label: 'Language Selector Text', default: '#e0e0e0', type: 'color', category: 'Top Bar', description: 'The text color for the language selector dropdown.', hasBoldToggle: true, defaultBold: false },
    '--htvm-checkbox-text': { label: 'HTVM Checkbox Text', default: '#e0e0e0', type: 'color', category: 'Top Bar', description: 'The text color for the labels next to the checkboxes (e.g., "Run JS", "Full HTML").', hasBoldToggle: true, defaultBold: false },
    '--htvm-checkbox-color': { label: 'HTVM Checkbox Color', default: '#3d8b40', type: 'color', category: 'Top Bar', description: 'The color of the checkmark inside the "Run JS" and "Full HTML" checkboxes.' },
    
    // --- File Tabs Category ---
    '--tab-inactive-bg': { label: 'Inactive Tab Background', default: '#252525', type: 'color', category: 'File Tabs', description: 'Background color for tabs that are not currently active.' },
    '--tab-inactive-text': { label: 'Inactive Tab Text', default: '#ffffff', type: 'color', category: 'File Tabs', description: 'Text color for tabs that are not currently active.', hasBoldToggle: true, defaultBold: false },
    '--tab-active-bg': { label: 'Active Tab Background', default: '#000000', type: 'color', category: 'File Tabs', description: 'Background color for the currently active/selected tab.' },
    '--tab-active-text': { label: 'Active Tab Text', default: '#ffffff', type: 'color', category: 'File Tabs', description: 'Text color for the currently active/selected tab.', hasBoldToggle: true, defaultBold: false },
    '--tab-hover-bg': { label: 'Tab Hover Background', default: '#3e3e3e', type: 'color', category: 'File Tabs', description: 'The background color when hovering over any tab. Set this to the same color as "Inactive Tab Background" to disable the effect.' },
    '--tab-close-icon': { label: 'Tab Close Icon (X)', default: '#ffffff', type: 'color', category: 'File Tabs', description: 'The color of the "X" icon used for closing an open file tab.' },
    
    // --- HTML Output Panel Category ---
    '--output-header-bg': { label: 'HTML Output Header BG', default: '#1a1a1a', type: 'color', category: 'HTML Output Panel', description: 'Background color for the header of the HTML Output panel.' },
    '--output-header-text': { label: 'HTML Output Header Text', default: '#ffffff', type: 'color', category: 'HTML Output Panel', description: 'Text color for the title ("HTML Output") and buttons in the panel header.', hasBoldToggle: true, defaultBold: false },
    '--download-html-btn-bg': { label: '"Download HTML" BG', default: '#3d8b40', type: 'color', category: 'HTML Output Panel', description: 'Background color for the "Download" button in the HTML Output panel.' },
    '--download-html-btn-text': { label: '"Download HTML" Text', default: '#ffffff', type: 'color', category: 'HTML Output Panel', description: 'Text color for the "Download" button.', hasBoldToggle: true, defaultBold: false },

    // --- Resizers & Scrollbars Category ---
    '--resizer-bg': { label: 'Resizer Bar Color', default: '#2c2c2c', type: 'color', category: 'Resizers & Scrollbars', description: 'The color of the draggable bars used to resize panels.' },
    '--resizer-hover-bg': { label: 'Resizer Bar Hover Color', default: '#2c2c2c', type: 'color', category: 'Resizers & Scrollbars', description: 'The color of the resizer bar when you hover over it. Set to the same color as the main Resizer Bar to disable the effect.' },
    '--scrollbar-track-bg': { label: 'Scrollbar Track Color', default: '#2c2c2c', type: 'color', category: 'Resizers & Scrollbars', description: 'The background color of the scrollbar channel.' },
    '--scrollbar-thumb-bg': { label: 'Scrollbar Thumb Color', default: '#0078d4', type: 'color', category: 'Resizers & Scrollbars', description: 'The color of the draggable part of the scrollbar (the "thumb").' },
    '--scrollbar-thumb-hover-bg': { label: 'Scrollbar Thumb Hover Color', default: '#0098f4', type: 'color', category: 'Resizers & Scrollbars', description: 'The color of the scrollbar thumb when you hover over it.' },
    '--scrollbar-size': { label: 'Scrollbar Thickness', default: '16', type: 'range', min: '4', max: '24', unit: 'px', category: 'Resizers & Scrollbars', description: 'Controls the width/height of the scrollbars.' },
    '--scrollbar-border-radius': { label: 'Scrollbar Roundness', default: '3', type: 'range', min: '0', max: '12', unit: 'px', category: 'Resizers & Scrollbars', description: 'Controls how rounded the corners of the scrollbar thumb are.' },
    
    // --- Debugger Category ---
    '--debugger-bg': { label: 'Debugger Background', default: '#1e1e1e', type: 'color', category: 'Debugger', description: 'Main background color of the debugger window.' },
    '--debugger-header-bg': { label: 'Debugger Header BG', default: '#2c2c2c', type: 'color', category: 'Debugger', description: 'Background of the draggable header bar.' },
    '--debugger-header-text': { label: 'Debugger Header Text', default: '#ffffff', type: 'color', category: 'Debugger', description: 'Text color for the debugger header.', hasBoldToggle: true, defaultBold: true },
    '--debugger-resume-btn-bg': { label: '"Resume" Button BG', default: '#3d8b40', type: 'color', category: 'Debugger', description: 'Background for the "Resume" button.' },
    '--debugger-stop-btn-bg': { label: '"Stop" Button BG', default: '#c12a2a', type: 'color', category: 'Debugger', description: 'Background for the "Stop" button.' },
    '--debugger-btn-text': { label: 'Button Text', default: '#ffffff', type: 'color', category: 'Debugger', description: 'Text color for buttons inside the debugger.', hasBoldToggle: true, defaultBold: false },
    '--debugger-scope-bg': { label: 'Scope Panel BG', default: '#1a1a1a', type: 'color', category: 'Debugger', description: 'Background for the "Scope Variables" panel.' },
    '--debugger-var-name-color': { label: 'Variable Name Color', default: '#9cdcfe', type: 'color', category: 'Debugger', description: 'Color for variable names in the scope panel.', hasBoldToggle: true, defaultBold: false },
    '--debugger-var-value-color': { label: 'Variable Value Color', default: '#ce9178', type: 'color', category: 'Debugger', description: 'Color for variable values in the scope panel.', hasBoldToggle: true, defaultBold: false },
};


// --- Utility Functions ---
const debounce = (func, delay) => {
    let timeout;
    return (...args) => {
        clearTimeout(timeout);
        timeout = setTimeout(() => func.apply(this, args), delay);
    };
};

function LoopParseFunc(varString, delimiter1="", delimiter2="") {
    let items;
    if (!delimiter1 && !delimiter2) {
        // If no delimiters are provided, return an array of characters
        items = [...varString];
    } else {
        // Construct the regular expression pattern for splitting the string
        let pattern = new RegExp('[' + delimiter1.replace(/[.*+?^${}()|[\]\\]/g, '\\$&') + delimiter2.replace(/[.*+?^${}()|[\]\\]/g, '\\$&') + ']+');
        // Split the string using the constructed pattern
        items = varString.split(pattern);
    }
    return items;
}