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

-   `[ ]` **Focus on Core Language Targets**
    -   *Objective:* Focus on three languages and remove the rest. We will only focus on JavaScript, Python, and C++. This enhances quality and maintainability.



