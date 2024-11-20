# HTVM  

### 🚀 HTVM: The Revolution in Programming  
HTVM is a revolutionary programming language and engine inspired by my earlier languages but a hundred times more powerful. Built in **HT++**, HTVM can convert code to **JavaScript**, **Python**, and **C++**, introducing groundbreaking features:  
- **Customizable Syntax**: Define your own syntax without restrictions.  
- **No More Libraries**: Forget importing libraries—everything you need is built-in for simplicity and efficiency.  

HTVM makes programming simpler, more flexible, and revolutionary.  

---

### 🌐 OSP: Objectively Simplified Programming Paradigm  
HTVM introduces the **Objectively Simplified Programming (OSP)** paradigm, which eliminates the complexities of traditional object-oriented programming while still supporting objects.  
- OSP focuses on intuitive and powerful object usage.  
- For more details, check out the **[OSP Documentation](https://github.com/TheMaster1127/HTVM/blob/main/DOCUMENTATION.md#osp-objectively-simplified-programming-paradigm)**.

---

### 🛠️ HTVM IDE: Integrated development environment
To enhance your development experience, HTVM comes with a dedicated **HTVM IDE**, featuring:  
- Syntax highlighting.  
- Code completion for efficient programming.  

---

## Table of Contents

1. [⚡ Getting Started](#-getting-started)
2. [📘 Usage](#-usage)
3. [📂 Adding Built-In Functions](#-adding-built-in-functions)
4. [🔄 Syntax Highlighting and Code Completion Regeneration](#-syntax-highlighting-and-code-completion-regeneration)
5. [📜 Documentation Regeneration](#-documentation-regeneration)
6. [💻 Linux Instructions](#-linux-instructions)
7. [🛠️ HTVM IDE](#-htvm-ide)


---

### ⚡ Getting Started  

#### Configuring Your Language  

1. **Adjust Syntax**:  
   - Use the website: [HTVM Syntax Configurator](https://themaster1127.github.io/HTVM/), or  
   - Edit `HT-instructions.txt` directly.  
     - Each line corresponds to the same line in `instruction documentation.txt`.  

2. **Write Your Code**:  
   - Save your language code as `yourCodeFileName.yourExtension`.  

3. **Compile and Execute**:  
   - Use `HTVM.exe` or compile the C++ code to generate output.  
   - Specify the target language (`cpp`, `py`, or `js`) in the first line of `HT-instructions.txt`.

4. **Add Built-In Functions**:  
   - Add functions at the bottom of `HT-instructions.txt`.  
   - Follow the syntax rules detailed in the **Adding Built-In Functions** section below.  

5. **Regenerate IDE Features**:  
   - Use the **Autocomplete-Syntax-Highlighting-Regenerator** tool to update syntax highlighting and code completion.  

---

### 📘 Usage  

#### Basic Command  
```bash
HTVM <yourCodeFileName.yourExtension> <HT-instructions.txt> [optional LangToTranspileTo]
```  

#### Options  
- **Required Parameters**:  
  - `yourCodeFileName.yourExtension`: The source code file.  
  - `HT-instructions.txt`: Instructions file for transpilation.  
- **Optional**:  
  - Specify the target language (`cpp`, `py`, `js`) directly in the command.  

**Example**:  
```bash
HTVM main.ht HT-instructions.txt cpp
```  

---

### 📂 Adding Built-In Functions  

1. Open `HT-instructions.txt`.  
2. Copy the last function block and paste it at the bottom.  
3. Follow these rules:  
   - **Language Specification**: Use `lang: cpp`, `lang: py`, or `lang: js` to define the language-specific implementation.  
   - **Function Name**: Use `name: functionName`.  
   - **Libraries**: List required libraries with a `|` delimiter. For example:  
     - Python: `libs: import math|import time`.  
     - C++: `libs: #include <iostream>|#include <cstdlib>`.  
     - JavaScript: `libs: <script src="https://cdn.jsdelivr.net/npm/sweetalert2@11"></script>`.  
   - **Description**:  
     - Format:  
       ```  
       description: string~~~[One-line description of the function]~~~Here is how the function looks:~~~```~~~[Function signature]~~~```  
       ```  
     - Example:  
       ```  
       description: string~~~Sort is a function to sort elements based on various criteria like numeric, random, alphabetical order, etc.~~~Here is how the function looks:~~~```~~~Sort(string input, [string options = ""])~~~```  
       ```  

**Here is how a build-in function in AWSD.AS looks like:**

```
func======================func==============
lang: cpp
name: Sleep
libs: #include <thread>|#include <chrono>
description: system~~~Sleep is a function that pauses execution for a specified number of milliseconds.~~~here is how the func looks like:~~~```~~~Sleep(int milliseconds)~~~```~~~
// Function to sleep for a specified number of milliseconds
void Sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
funcEND======================funcEND==============
```

4. **ChatGPT Prompt for Function Descriptions:**  
   To generate descriptions for functions, use the following ChatGPT prompt to ensure the response follows a specific format:  

   **ChatGPT Prompt:**  
   ```
   here is what you will do structly so i wil give you a func like something like this it can be in c++ py or js dosnet matter from what it is it what you must do is give me output in this format:
   
   description: string~~~StrTitleCase is a func balalbla bla bal~~~here is how the func looks like:~~~```~~~StrTitleCase(string, [optanalName], string, [optanal], string, [optanal], [optanal])~~~```~~~
   
   the param dosnet have to be the same name juts a simlpe name no _ pls
   
   Use square brackets: When you mention the function or describe the parameters, put optional parameters in square brackets [ ]. This is the most common notation for optional parameters. For example:
   
   functionName(param1, [param2], [param3])
   This means that param2 and param3 are optional.
   Provide a description or note: You can also mention which parameters are optional in a description or a comment, such as:
   
   "The param2 and param3 parameters are optional."
   "The optional parameters are param2 and param3."
   Default values in code: If the function includes default values for parameters, you can also point this out. For example:
   
   functionName(param1, param2 = "default", param3 = 10)
   This means that param2 and param3 have default values and are optional.
   
   YOU MUST SPECIFY THE TYPE AS WELL like this
   
   funcName(int asd, str, waeds, bool, waedsf, arr str, waesdf, bool [awsesrs = false], bool [awsesrs = true])
   
   YOU MUST SPECIFY THE TYPE EVEN IF YOU DONT KNOW TRY TO GUESS HERE IS THE TYPE SYNTAX
   str
   int
   bool
   arr str
   func
   ... otherwize made them up
   
   so the ~~~ = to a new line ok ~~~ is a new line and the first one where we typed string is the category and it must alwas be one word the bets word for thet category like string math gui io files bla...
   THE description BUST BE ONLY IN ONE LINE
   here is func and replay in one line:
   ================================================

   // Function to sleep for a specified number of milliseconds
   void Sleep(int milliseconds) {
       std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
   }

   ```  

If chatGPT replayis in more then one line tell it:

`I SAID REPLY IN ONE LINE`

**Important**: Do not modify the first 86 lines of `HT-instructions.txt`.  

---

### 🔄 Syntax Highlighting and Code Completion Regeneration  

To regenerate IDE features:  
1. Compile the `Autocomplete-Syntax-Highlighting-Regenerator.cpp`:  
   ```bash
   g++ Autocomplete-Syntax-Highlighting-Regenerator.cpp -o Autocomplete-Syntax-Highlighting-Regenerator
   ```  

2. Run the compiled program:  
   ```bash
   Autocomplete-Syntax-Highlighting-Regenerator.exe HT-instructions.txt
   ```  

   or in linux

   ```bash
   ./Autocomplete-Syntax-Highlighting-Regenerator HT-instructions.txt
   ``` 

3. This will update the file `IDE\htvm_syntax_highlighting_and_autocomplete.js` with the latest syntax and code completion.

4. Press `Ctrl+Shift+R` to reload the IDE, or if the IDE is closed, the updates will apply when reopened.  

---

### 📜 Documentation Regeneration  

Regenerate `DOCUMENTATION.md` using:  
1. Compile the `Documentation-Generation.cpp` file:  
   ```bash
   g++ Documentation-Generation.cpp -o Documentation-Generation
   ```  

2. Run the executable:  
   ```bash
   Documentation-Generation.exe HT-instructions.txt
   ```  

   or in linux

   ```bash
   ./Documentation-Generation HT-instructions.txt
   ``` 

---

### 💻 Linux Instructions  

1. Compile `HTVM.cpp`:  
   ```bash
   g++ HTVM.cpp -o HTVM
   ```  

2. Run the transpiler:  
   ```bash
   ./HTVM main.ht HT-instructions.txt
   ```  

3. Add an optional target language:  
   ```bash
   ./HTVM main.ht HT-instructions.txt cpp
   ```  

   or 

   ```bash
   ./HTVM main.ht HT-instructions.txt py
   ```  

   or 

   ```bash
   ./HTVM main.ht HT-instructions.txt js
   ```  


### 🛠️ HTVM IDE


To run the IDE:
```bash
cd IDE
npm install
npm start
```

then next time you wanan open the ide `cd IDE` go to the IDE folder and open a terminal tehre or `cmd` in windows since the **HTVM IDE** will work in both windows and linux.
and next time just use:

```
npm start
```
