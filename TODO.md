# TODO for HTVM v3

### ⚠️ **WARNING: This is a Development Plan, Not a Promise** ⚠️

> This document outlines the strategic vision for the development of HTVM. It is a living document, meaning priorities may shift and the order of implementation is flexible. The goal is to build upon the stable foundation of V2 and deliver the next generation of personalized programming.

---

-   `[✅]` **Refactor the Documentation System**
    -   *Objective:* Refactor the way documentation is written and managed internally. The goal is to move away from the current hardcoded approach to a more modular system, making it significantly easier to add new documentation as features are developed.

-   `[✅]` **Implement the HTVM Debugger**
    -   *Objective:* Build the integrated debugger that uses injected `input()` calls to provide state inspection directly within the IDE's workflow.
    
-   `[✅]` **Implement True Structs with Instancing**
    -   *Objective:* Evolve structs from static namespaces into instantiable objects. The `instance` keyword will create a complete, independent copy of the struct's definition, enabling more complex data patterns.

-   `[✅]` **Document the `Liner` Construct**
    -   *Objective:* Add clear documentation for the `Liner` construct.

-   `[ ]` **Enhance the GUI System**
    -   *Objective:* The primary goal is to make all GUI-related keywords (e.g., `gui`, `button`) fully configurable via the instruction file, removing all hardcoded elements. This also includes adding new features and capabilities to the GUI system.

-   `[ ]` **Implement Code Formatting Configuration**
    -   *Objective:* Allow users to define code formatting rules (tabs vs. spaces) in the instruction file. These rules will be used by the HTVM formatter and the HTVM-to-HTVM conversion process.

-   `[ ]` **Achieve Total Syntax Configuration**
    -   *Objective:* De-hardcode all remaining syntax elements (`gui`, `when`, `subout`, etc.) into configurable rules, enabling ultimate language personalization.

-   `[ ]` **Add a New HIDDEN Language Target**
    -   *Objective:* Extend the transpiler to support **C**.

-   `[ ]` **Introduce the `#define` Meta-Programming Directive**
    -   *Objective:* Implement a `#define` directive that allows developers to reconfigure HTVM's syntax (keywords, block styles, and many other syntactic elements) directly from within a source file. This directive will be executed once at the beginning of the parsing step, meaning keywords cannot be changed midway through the code. This also includes a specific, hardcoded directive (`#define_programming_block_delimiter`) to safely customize the block delimiter characters for programming blocks.

-   `[ ]` **Evolve the Configuration System**
    -   *Objective:* Implement support for `HTVM-instructions.json` and `HTVM-instructions.htvmconf` alongside the legacy `HTVM-instructions.txt` file. The engine will auto-detect the file type based on its extension, ensuring backward compatibility. This also includes building a utility to convert between all three formats.

-   `[ ]` **Implement "The Transformer" Engine (Writability vs. Readability)**
    -   *Objective:* Create the shorthand-to-code expansion logic, allowing for rapid, compressed coding that expands into fully readable code, solving a timeless programming trade-off.

-   `[ ]` **Implement the "AI Language Creator"**
    -   *Objective:* Engineer the LLM prompt and IDE interface to allow users to generate a base `HTVM-instructions.txt` file from a plain English description of their desired language.

-   `[ ]` **Focus on Core Language Targets**
    -   *Objective:* Focus on three languages and remove the rest. We will only focus on JavaScript, Python, and C++. This enhances quality and maintainability.








