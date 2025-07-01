# HT-IDE

The IDE of the future — seamlessly built for HTVM, customizable, efficient, and ready to power the next generation of programming.

#### A screenshot from the web version:

![image](https://github.com/user-attachments/assets/baef0e77-fcc8-4ed9-9607-f9bbe1ab4114)

---

## **HT-IDE: The Complete Feature Breakdown**

Welcome to your custom-built Integrated Development Environment. This is far more than a simple text editor; it's a complete, persistent, and "insanely good" coding powerhouse designed for maximum productivity and ultimate personalization.

### **The Core Experience: Code, Edit, Run**

These are the foundational features you'll use every day.

*   **Advanced Code Editor:**
    *   Powered by the robust **Ace Editor** core.
    *   **Dynamic Syntax Highlighting:** Intelligently switches highlighting based on the language, including real-time mode changes inside `.htvm` files for embedded code blocks (JS, Python, C++, etc.).
    *   **Intelligent Autocompletion:** Provides suggestions for language keywords, functions, and even words already present in your current file.
    *   **Pro-Level Keybindings:** Switch between Normal (Ace), Vim, Emacs, VSCode, and Sublime keymaps to feel right at home.
    *   **Multi-Cursor Editing:** Hold `Ctrl` (or `Cmd`) and click to place multiple cursors for simultaneous editing.
    *   **Find & Replace:** Standard `Ctrl+F` functionality for searching within a file.

*   **Integrated Terminal:**
    *   A full-featured **xterm.js** terminal is built into the bottom panel.
    *   Perfect for viewing program output, save confirmations, and transpilation logs.
    *   Can be configured to automatically clear before each run.

*   **Multi-Language Execution:**
    *   **Run Button (`▶ Run`):** Execute your code with a single click (or hotkey).
    *   **JavaScript Runner:** Directly executes `.js` files, displaying `console.log` output in the terminal.
    *   **HTML Preview:** Renders `.html` files instantly in a dedicated, resizable side panel with a "Download" option.
    *   **HTVM Transpiler & Runner:** The core engine that runs `.htvm` files (see HTVM Powerhouse section).

### **File & Project Management**

A complete virtual file system that lives in your browser, powered by **IndexedDB** for large-scale storage.

*   **Sidebar File Explorer:** A familiar, tree-like view of your project.
*   **File & Folder Operations:** Easily create new files and folders within your current directory.
*   **Full Navigation:** Navigate into folders and use the `..` entry to go back up.
*   **Intuitive Tab System:**
    *   Open multiple files in a clean, tabbed interface.
    *   **Drag & Drop Reordering:** Click and drag a tab to change its position.
    *   **Unsaved Changes Indicator:** A `*` symbol appears on tabs with unsaved work.
    *   **Quick Close/Re-open:** Close tabs with `Ctrl+W` and instantly re-open the last closed tab with `Ctrl+Shift+T` (or your custom hotkeys).

### **The HTVM Powerhouse**

This is the unique engine that sets HT-IDE apart.

*   **Multi-Target Transpilation:**
    *   Convert `.htvm` source code to a vast array of popular languages: **JavaScript, Python, C++, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript, and Groovy.**
    *   The target language is selected via a convenient dropdown in the top bar.
    *   **Special JS/HTML Options:**
        *   `Run JS`: Automatically execute the JavaScript code immediately after it's generated.
        *   `Full HTML`: Wrap the generated JavaScript in a complete, runnable HTML5 document.

*   **Instruction Set Management:**
    *   **Centralized Manager:** A dedicated modal to handle all your HTVM instruction sets.
    *   **Add, Rename, Delete:** Easily manage your collection of instruction files.
    *   **Apply & Reload:** Switch between different instruction sets with a single click, which reloads the IDE to apply the changes globally.
    *   **The Instruction Set Editor:** A powerful, built-in tool to create and modify instruction sets.
        *   **Full UI:** Edit function metadata like name, target language, libraries, category, and description.
        *   **Live Description Preview:** See how your description formatting (using `~~~` for newlines) will look.
        *   **Embedded Ace Editor:** The function body is editable in a full code editor with proper syntax highlighting for its specified language (JS, Python, etc.).
        *   **Easy Organization:** Search, filter, and view functions by category, and toggle the visibility of internal functions.

*   **HTVM-to-HTVM Converter:** A utility to translate `.htvm` files written with one instruction set into code compatible with another, making code migration seamless.

### **Advanced Debugging Tools**

A simple yet powerful debugger for your JavaScript and transpiled-to-JS code.

*   **Gutter Breakpoints:** Simply click in the gutter (the area with line numbers) to set or remove a breakpoint on any line.
*   **Execution Pause:** When you run code, execution will pause at the first breakpoint it hits.
*   **Draggable Debugger Modal:**
    *   A non-blocking window appears, showing that execution is paused.
    *   **Controls:** Resume execution (`F8`) or stop it entirely.
    *   **Scope Inspector:** Automatically displays all user-declared variables and their current values at the moment of the pause.
*   **Value Hover:** While paused, simply hover your mouse over a variable name in the editor to see its value in a tooltip.

### **Ultimate Customization & Personalization**

Tailor every single aspect of the IDE to your exact preference.

*   **Full UI Theme Editor:**
    *   **Live-Preview:** Changes are applied instantly as you edit them.
    *   **Categorized & Organized:** Modify colors and styles for the General UI, Sidebar, Buttons, File Tabs, and more.
    *   **Total Control:** Use color pickers, boldness toggles, and sliders (for scrollbar size, etc.) to customize dozens of UI elements.
*   **Syntax Color Editor:** Independently control the color and boldness of every HTVM syntax element (commands, keywords, strings, comments, etc.).
*   **Editor Settings:** Tweak font size, keybinding modes, bracket auto-pairing, and the vertical print margin line.
*   **Customizable Hotkeys:** Remap the keyboard shortcuts for all major actions (Run, Save, Format, Close Tab, etc.) in a dedicated, conflict-aware modal.

### **Session & Data Management**

Your work and setups are always safe and portable.

*   **Session Manager:** Save and load your entire set of open tabs as a named "session," allowing you to quickly switch between different project contexts.
*   **Comprehensive Export/Import System:**
    *   **Export/Import Everything:** Create a full backup of *all* workspaces and settings in a single JSON file.
    *   **Export/Import Theme:** Save just your visual theme settings to share or reuse.
    *   **Export/Import Workspace:** Back up or migrate a single workspace, including all its files and settings.
    *   **Full Control:** The system now prompts you for a filename ("Save As") for all exports and gives you the option to import a workspace to a **new ID** or **overwrite an existing one** (with a strong confirmation warning).
*   **Persistent State:** The IDE automatically remembers your open files, panel sizes, breakpoints, and all settings, so you can close the browser and pick up exactly where you left off.

### **User Interface & Quality of Life**

Small details that make a big difference.

*   **Responsive Design:** The UI intelligently adapts for use on smaller screens and mobile devices.
*   **Resizable Panels:** Drag the borders between the file explorer, editor, terminal, and HTML output panel to create your perfect layout.
*   **Informative Tooltips:** Hover over help icons (`ℹ️`) in settings modals to get detailed explanations of what each option does.
*   **Workspace Isolation:** Each workspace (identified by the `?id=` in the URL) is completely sandboxed in its own database, with its own files, settings, and instruction sets, preventing data leaks.