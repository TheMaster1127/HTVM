# TODO

### ⚠️ **WARNING: This is a Development Plan, Not a Promise** ⚠️

> This document outlines the strategic vision for the development of HTVM. It is a living document, meaning priorities may shift and the order of implementation is flexible. The goal is to build upon the stable foundation of V2 and deliver the next generation of personalized programming.

---

### **Completed Milestones**
*The foundational features that are already implemented and stable.*

-   `[✅]` **Finalize the Plugin API & Marketplace ("The Freedom API")**
    -   *Objective:* Solidify the hook system and establish the community marketplace, empowering users to extend HTVM's syntax.
-   `[✅]` **Package the Standalone HT-IDE**
    -   *Objective:* Finalize and distribute the Electron-based IDE to remove the NPM dependency for users.
-   `[✅]` **Implement New Language Constructs (Liner)**
    -   *Objective:* Build the planned weighted conditional block (`Liner`) which offers new ways to express complex logic.

---

### **Part 1: The V2.1 Polish & Finalization**
*The essential, high-priority tasks to complete a polished and powerful version of the current HTVM engine.*

-   `[ ]` **Build The Definitive `For` Construct**
    -   *Objective:* Create a powerful polymorphic iteration engine that can intelligently loop over any data type (strings, arrays, maps, ranges) with a consistent syntax.

-   `[ ]` **Add a New Language Target**
    -   *Objective:* Extend the transpiler to support **C**, bringing the total number of target languages to 16.

-   `[ ]` **Implement Personalized Styling & Bidirectional Formatting**
    -   *Objective:* Build the system that reads styling preferences for code styling in a user's preferred format (tabs, spaces, brace style) without altering the source file.

-   `[ ]` **Implement the HTVM Debugger**
    -   *Objective:* Build the integrated debugger that uses injected `input()` calls to provide state inspection directly within the IDE's workflow.

-   `[ ]` **Produce the HTVM v2.1 Showcase Video**
    -   *Objective:* Create and release a video demonstrating the completed feature set and power of the polished V2 engine.

---

### **Part 2: Future Vision & Experimental Concepts**
*This is a document to look at for ambitious, next-generation ideas that MAY OR MAY NOT BE PURSUED IN THE FUTURE.*

-   `[ ]` **Achieve Total Syntax Configuration**
    -   *Objective:* De-hardcode all remaining syntax elements (`gui`, `when`, `maps`, `subout`, etc.) into configurable rules, enabling ultimate language personalization.

-   `[ ]` **Implement Static One-Time Inference (SOTI)**
    -   *Objective:* Introduce optional static typing without the boilerplate, allowing for greater type safety and performance when targeting static languages.

-   `[ ]` **Architect & Implement Native Map/Dictionary Support**
    -   *Objective:* Design a core, customizable syntax for key-value pairs (maps, dictionaries, hashmaps) and ensure it can be transpiled effectively to all target languages.

-   `[ ]` **Implement "The Transformer" Engine (Writability vs. Readability)**
    -   *Objective:* Create the shorthand-to-code expansion logic, allowing for rapid, compressed coding that expands into fully readable code, solving a timeless programming trade-off.

-   `[ ]` **Create the V2-to-V3 Instruction File Converter**
    -   *Objective:* Build a utility to ensure backward compatibility and a smooth transition for existing instruction files to the new V3 format.

-   `[ ]` **Implement Major GUI Enhancements**
    -   *Objective:* Expand the GUI command set with new controls and capabilities, building upon the new Total Syntax Configuration system.

-   `[ ]` **Implement The Metaconfigurator**
    -   *Objective:* Allow instruction files to be defined in multiple formats (JSON, YAML, INI), giving users more control over their configuration workflow.

-   `[ ]` **Implement Pythonic Indentation Style (Experimental)**
    -   *Objective:* Research and build the logic to support indentation-based blocks as a powerful alternative to braces or `end` keywords.

-   `[ ]` **Implement the "AI Language Creator"**
    -   *Objective:* Engineer the LLM prompt and IDE interface to allow users to generate a base `HTVM-instructions.txt` file from a plain English description of their desired language.
    
