# TODO / PLAN FOR HTVM V3

## The Strategic Roadmap for HTVM V3

### ⚠️ **WARNING: This is a Development Plan, Not a Promise** ⚠️

> This document outlines the strategic vision for the development of HTVM Version 3. It is a living document, meaning priorities may shift and the order of implementation is flexible. The goal is to build upon the stable foundation of V2 and deliver the next Version of personalized programming.

---

### **Core Engine & Parser Enhancements**
*Fundamental upgrades that expand the power and flexibility of the HTVM engine.*

-   `[✅]` **Finalize the Plugin API & Marketplace ("The Freedom API")**
    -   *Objective:* Solidify the hook system and establish the community marketplace, empowering users to extend HTVM's syntax.

-   `[ ]` **Achieve Total Syntax Configuration**
    -   *Objective:* De-hardcode all remaining syntax elements (`gui`, `when`, `maps`, `subout`, etc.) into configurable rules, enabling ultimate language personalization.

-   `[ ]` **Implement Static One-Time Inference (SOTI)**
    -   *Objective:* Introduce optional static typing without the boilerplate, allowing for greater type safety and performance when targeting static languages.

-   `[ ]` **Build the Advanced Alias Engine**
    -   *Objective:* Allow for infinite keyword aliasing via `.htvmprofile`, making the IDE and parser fully aware of a developer's personal vocabulary.

-   `[ ]` **Architect & Implement Native Map/Dictionary Support**
    -   *Objective:* Design a core, customizable syntax for key-value pairs (maps, dictionaries, hashmaps) and ensure it can be transpiled effectively to all target languages.

-   `[ ]` **Build The Definitive `For` Construct**
    -   *Objective:* Create a powerful polymorphic iteration engine that can intelligently loop over any data type (strings, arrays, maps, ranges) with a consistent syntax.

---

### **Developer Experience & Tooling**
*Features focused on making the day-to-day process of writing, debugging, and managing HTVM code faster and more intuitive.*

-   `[✅]` **Package the Standalone HT-IDE**
    -   *Objective:* Finalize and distribute the Electron-based IDE to remove the NPM dependency for users.

-   `[ ]` **Implement the HTVM Debugger**
    -   *Objective:* Build the integrated debugger that uses injected `input()` calls to provide state inspection directly within the IDE's workflow.

-   `[ ]` **Implement "The Transformer" Engine (Writability vs. Readability)**
    -   *Objective:* Create the shorthand-to-code expansion logic, allowing for rapid, compressed coding that expands into fully readable code, solving a timeless programming trade-off.

-   `[ ]` **Create the V2-to-V3 Instruction File Converter**
    -   *Objective:* Build a utility to ensure backward compatibility and a smooth transition for existing instruction files to the new V3 format.

---

### **The Code War Eliminator: Personalized Styling Engine**
*The philosophical heart of HTVM V3, solving the human problems of programming style and collaboration.*

-   `[ ]` **Implement Personalized Styling & Bidirectional Formatting**
    -   *Objective:* Build the system that reads styling preferences from a `.htvmprofile` and renders code in a user's preferred format (tabs, spaces, brace style, naming conventions) without altering the source file. This includes the Intelligent Name Collision Detection Algorithm.

---

### **High-Level Language Constructs & Features**
*New, expressive tools that developers can use directly in their HTVM code.*

-   `[ ]` **Implement Major GUI Enhancements**
    -   *Objective:* Expand the GUI command set with new controls and capabilities, building upon the new Total Syntax Configuration system.

-   `[ ]` **Implement New Language Constructs (Liner & Flowcall)**
    -   *Objective:* Build the planned weighted conditional block (`Liner`) and the named-input block (`Flowcall`) to offer new ways to express complex logic.

---

### **Ecosystem & Platform Expansion**
*Goals that extend HTVM's reach, making it compatible with more platforms and lowering the barrier to entry.*

-   `[ ]` **Add New Language Targets**
    -   *Objective:* Extend the transpiler to support **C**, **GDScript**, and **AngelScript**, bringing the total number of target languages to 18.

-   `[ ]` **Implement The Metaconfigurator**
    -   *Objective:* Allow instruction files to be defined in multiple formats (JSON, YAML, INI), giving users more control over their configuration workflow.

-   `[ ]` **Implement Pythonic Indentation Style (Experimental)**
    -   *Objective:* Research and build the logic to support indentation-based blocks as a powerful alternative to braces or `end` keywords.

-   `[ ]` **Implement the "AI Language Creator"**
    -   *Objective:* Engineer the LLM prompt and IDE interface to allow users to generate a base `HTVM-instructions.txt` file from a plain English description of their desired language.

---

### **V3 Finalization & Launch**
*The final push to consolidate all features and present HTVM V3 to the world.*

-   `[ ]` **Update the Website & All Documentation**
    -   *Objective:* Overhaul the official website and regenerate all documentation to reflect the full feature set of V3.

-   `[ ]` **Produce the HTVM v3.0 Launch Video**
    -   *Objective:* Create and release the definitive video that introduces the vision and capabilities of the completed V3 release: **"HTVM v3: The Future of Programming is Here."**


