# TODO / PLAN FOR HTVM V3

## ⚠️ **WARNING: This is a Development Plan, Not a Promise** ⚠️

> This document outlines the **planned** development roadmap for HTVM V3. It is a living document, and the features, their order, and release versions are **subject to change** based on development realities and shifting priorities. This is a guide, not a guarantee.

---

### **1. Package the HT-IDE**
-   `[ ]` Build Electron to generate standalone executables for all platforms to **eliminate the NPM requirement for users.**

### **2. Implement the HTVM Hook API ("The Freedom API")**
-   `[ ]` Architect and implement the core API with stable hook points in the parser and transpiler.
-   `[ ]` Develop essential helper functions to make the API usable.
-   **YouTube Release (v2.1):** "HTVM's New Plugin API: Build Your Own Syntax! (v2.1 Update & Tutorial)"

### **3. Implement the HTVM Debugger**
-   `[ ]` Build the debugger within the HT-IDE by injecting `input()` calls at breakpoints to display variable states.
-   **YouTube Release (v2.2):** "Introducing the HTVM Debugger"

### **4. Implement Total Syntax Configuration**
-   `[ ]` Break down previously hard-coded syntaxes (`gui`, `when`, `subout` etc...) into configurable rules in `HTVM-instructions.txt`.

### **5. Implement Major GUI Enhancements**
-   `[ ]` Add new GUI commands and improve existing ones based on the new total syntax configuration capabilities.
-   **YouTube Release (v2.3):** "How to Use GUIs in HTVM (New v2.3 Features & Tutorial)"

### **6. Implement New Language Constructs (Liner & Flowcall)**
-   `[ ]` **Liner:** Implement the weighted conditional block.
-   `[ ]` **Flowcall:** Implement the named-input block.
-   **YouTube Release (v2.4):** "New HTVM Constructs: Liner & Flowcall Explained (v2.4 Update)"

### **7. Implement the "Writability vs. Readability" Engine (The Transformer)**
-   `[ ]` Develop the shorthand-to-code expansion logic and hotkey integration.
-   **YouTube Release (v2.5):** "Code at the Speed of Thought: HTVM's IDE New Feature (v2.5)"

### **8. Implement Static One-Time Inference (SOTI)**
-   `[ ]` Re-architect the parser's variable handling to infer and lock a variable's type upon its first assignment.
-   **YouTube Release (v2.6):** "Static Typing Without the Boilerplate: HTVM's New SOTI Engine (v2.6)"

### **9. Implement the Advanced Alias Engine**
-   `[ ]` Implement `.htvmprofile` parsing for infinite keyword aliasing. Integrate into the parser, IDE syntax highlighting, and autocompletion.
-   **YouTube Release (v2.7):** "Code Your Way: HTVM's Infinite Alias Engine"

### **10. Implement Personalized Styling & Bidirectional Formatting (The Code War Eliminator)**
-   `[ ]` Implement the `.htvmprofile` `style_config` parser and the non-destructive rendering system in the IDE, including the **Intelligent Name Collision Detection Algorithm.**
-   **YouTube Release (v2.8):** "Ending the Code Wars: HTVM's Personalized Styling Engine (v2.8)"

### **11. Implement the New `For` Construct (The Definitive Iteration Engine)**
-   `[ ]` Build the full polymorphic engine for all data types, including the `A_` variable suite.
-   **YouTube Release (v2.9):** "The Ultimate Loop: Introducing HTVM's New 'For' Construct (v2.9 Update)"

### **12. Add New Language Targets (GDScript, AngelScript, C)**
-   `[ ]` Extend the transpiler engine and built-ins for all three languages. Update documentation to reflect 18 languages and create `LANGS.md`.
-   **YouTube Release (v2.10) - Titles:**
    -   "HTVM for Godot: Full GDScript Support is Here!"
    -   "HTVM Now Supports AngelScript"
    -   "HTVM Now Supports C"

### **13. Implement The Metaconfigurator (Customizable Config Files)**
-   `[ ]` Extend the IDE/engine to parse and convert between different instruction file formats (JSON, YAML, INI).
-   **YouTube Release (v2.11):** "Your Config, Your Way: HTVM's Metaconfigurator (v2.11)"

### **14. Implement Pythonic Indentation Style (Experimental)**
-   `[ ]` Implement the new feature, framing it as a completely new addition to HTVM.
-   **YouTube Release (v2.12, if successful):** "Introducing Pythonic Indentation Style to HTVM"

### **15. Implement "AI Language Creator"**
-   `[ ]` Engineer the master prompt for the LLM and build the IDE interface to generate `HTVM-instructions.txt` files from plain English.
-   **YouTube Release (v2.13):** "HTVM: AI-Assisted Language Generation is Here"

### **16. Build the Community Hub ("HTVM Marketplace")**
-   `[ ]` Create the `htvm-marketplace` GitHub repository and contribution guidelines.
-   `[ ]` Build the "Import from Marketplace" feature into the IDE.
-   **YouTube Release (v2.14):** "Introducing The HTVM Marketplace: Share and Discover HTVM Plugins!"

### **17. Implement V2-to-V3 Instruction File Converter**
-   `[ ]` Create a utility to migrate old instruction files to the new V3 format.
-   **YouTube Release (v2.15):** "HTVM V2 to V3 Converter"

### **18. Update the Website & Documentation**
-   `[ ]` Update the HTVM Language Creator website and all documentation for every new V3 feature.

### **19. HTVM v3.0 Grand Launch**
-   `[ ]` Produce and release the definitive launch video: **"HTVM v3: The Future of Programming is Here."**

---

### **HTVM V3 To-Do List (In Order)**

#### 0/23 Done!

1.  `[ ]` IDE Packaging
2.  `[ ]` HTVM Hook API
3.  `[ ]` HTVM Debugger
4.  `[ ]` Total Syntax Configuration
5.  `[ ]` GUI Enhancements
6.  `[ ]` Liner (New Language Constructs)
7.  `[ ]` Flowcall (New Language Constructs)
8.  `[ ]` Writability Engine ("The Transformer")
9.  `[ ]` Static One-Time Inference (SOTI)
10. `[ ]` Advanced Alias Engine
11. `[ ]` Personalized Styling Engine (Code War Eliminator)
12. `[ ]` The `For` Construct (Definitive Iteration Engine)
13. `[ ]` New Language Target: GDScript
14. `[ ]` New Language Target: AngelScript
15. `[ ]` New Language Target: C
16. `[ ]` Metaconfigurator (Customizable Config Files)
17. `[ ]` Pythonic Indentation (Experimental)
18. `[ ]` AI Language Creator
19. `[ ]` HTVM Marketplace (Community Hub)
20. `[ ]` V2-to-V3 Converter
21. `[ ]` Update the Website
22. `[ ]` Update the Documentation
23. `[ ]` Finish HTVM v3

### **Videos To Make:**

#### 0/18 Done!

1. `[ ]` HTVM's New Plugin API: Build Your Own Syntax! (v2.1 Update & Tutorial)
2. `[ ]` Introducing the HTVM Debugger (v2.2)
3. `[ ]` How to Use GUIs in HTVM (v2.3 Features & Tutorial)
4. `[ ]` New HTVM Constructs: Liner & Flowcall Explained (v2.4 Update)
5. `[ ]` Code at the Speed of Thought: HTVM's IDE New Feature (v2.5)
6. `[ ]` Static Typing Without the Boilerplate: HTVM's New SOTI Engine (v2.6)
7. `[ ]` Code Your Way: HTVM's Infinite Alias Engine (v2.7)
8. `[ ]` Ending the Code Wars: HTVM's Personalized Styling Engine (v2.8)
9. `[ ]` The Ultimate Loop: Introducing HTVM's New 'For' Construct (v2.9 Update)
10. `[ ]` HTVM for Godot: Full GDScript Support is Here! (v2.10)
11. `[ ]` HTVM Now Supports AngelScript (v2.10)
12. `[ ]` HTVM Now Supports C (v2.10)
13. `[ ]` Your Config, Your Way: HTVM's Metaconfigurator (v2.11)
14. `[ ]` Introducing Pythonic Indentation Style to HTVM (v2.12)
15. `[ ]` HTVM: AI-Assisted Language Generation is Here (v2.13)
16. `[ ]` Introducing The HTVM Marketplace: Share and Discover HTVM Plugins! (v2.14)
17. `[ ]` HTVM V2 to V3 Converter (v2.15)
18. `[ ]` HTVM v3: The Future of Programming is Here.
