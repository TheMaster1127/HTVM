# HTVM  

### 🚀 HTVM: The Revolution in Programming  
HTVM is a revolutionary programming language and engine inspired by my earlier languages but a hundred times more powerful. Built in **[HT++](https://github.com/TheMaster1127/HT-plus-plus)**, HTVM can convert code to **JavaScript**, **Python**, and **C++**, introducing groundbreaking features:  
- **Customizable Syntax**: Define your own syntax without restrictions.  
- **No More Build-In Libraries**: Forget importing libraries—everything you need is built-in for simplicity and efficiency.  
- **HTVM IDE**: To enhance your development experience, HTVM comes with a dedicated IDE.

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

### 📚 Documentation
Here is the [Documentation](https://github.com/TheMaster1127/HTVM/blob/main/DOCUMENTATION.md)

---

### Table of Contents

1. [📘 Usage](#-usage)  
   **Description**: Learn how to compile and execute your language code using HTVM and the HTVM IDE.

2. [📂 Adding Built-In Functions](#-adding-built-in-functions)  
   **Description**: Add custom built-in functions to your language by following simple syntax rules.

3. [🔄 Syntax Highlighting and Code Completion Regeneration](#-syntax-highlighting-and-code-completion-regeneration)  
   **Description**: Use the **Autocomplete-Syntax-Highlighting-Regenerator** tool to refresh syntax highlighting and code completion.

4. [📜 Documentation Regeneration](#-documentation-regeneration)  
   **Description**: Update your language’s documentation whenever new features or changes are made.

5. [🛠️ HTVM IDE](#%EF%B8%8F-htvm-ide)  
   **Description**: Set up and use the HTVM IDE for coding, testing, and compiling your language.

---

### 📘 Usage  

[Go Back To The Table of Contents ](#table-of-contents)

### 1. **Clone the Repository**

First, clone the HTVM repository:

```bash
git clone https://github.com/TheMaster1127/HTVM
```

Navigate into the directory:

```bash
cd HTVM
```

2. **Adjust Syntax**:  
   - Use the website: [HTVM Syntax Configurator Website](https://themaster1127.github.io/HTVM/), or  
   - Edit `HT-instructions.txt` directly (NOT RECOMMENDED!).  
     - Each line corresponds to the same line in `instruction documentation.txt`.  

#### Usage of the HTVM compiler
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

### 3. Compile and Run `HTVM`

1. **Compile `HTVM.cpp`**:  
   **Recommended Command**:  
   ```bash
   g++ -std=c++17 HTVM.cpp -o HTVM
   ```  

   **Not Recommended** (may cause issues):  
   ```bash
   g++ HTVM.cpp -o HTVM
   ```  

2. **Run the Transpiler**:  
   After compiling, you will get a new executable file.  

   **General Usage**:  
   ```bash
   HTVM main.ht HT-instructions.txt
   ```  

   **Linux Users**:  
   Prepend `./` to the command:  
   ```bash
   ./HTVM main.ht HT-instructions.txt
   ```  

3. **Specify Target Language (Optional)**:  
   Add `cpp`, `py`, or `js` at the end of the command to specify the target language.  

   **Examples**:  
   - Generate C++ code:  
     ```bash
     HTVM main.ht HT-instructions.txt cpp
     ```  
     For Linux:  
     ```bash
     ./HTVM main.ht HT-instructions.txt cpp
     ```  

   - Generate Python code:  
     ```bash
     HTVM main.ht HT-instructions.txt py
     ```  
     For Linux:  
     ```bash
     ./HTVM main.ht HT-instructions.txt py
     ```  

   - Generate JavaScript code:  
     ```bash
     HTVM main.ht HT-instructions.txt js
     ```  
     For Linux:  
     ```bash
     ./HTVM main.ht HT-instructions.txt js
     ```  

--- 

### 📂 Adding Built-In Functions  

[Go Back To The Table of Contents ](#table-of-contents)

**Description**: Add custom built-in functions to your language by following simple syntax rules.

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

[Go Back To The Table of Contents ](#table-of-contents)

**Description**: Use the **Autocomplete-Syntax-Highlighting-Regenerator** tool to refresh syntax highlighting and code completion.

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

[Go Back To The Table of Contents ](#table-of-contents)

**Description**: Update your language’s documentation whenever new features or changes are made.

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

### 🛠️ HTVM IDE

[Go Back To The Table of Contents ](#table-of-contents)

**Description**: Set up and use the HTVM IDE for coding, testing, and compiling your language.

1. [How to set up the HTVM IDE](#set-up-the-htvm-ide)
2. [How to use the HTVM IDE and its Keyboard shortcuts](#How-to-use-the-htvm-ide-and-its-keyboard-shortcuts)
3. [How to use the HTVM IDE Property Files](#htvm-ide-property-files)

---

## **Set Up the HTVM IDE**

[Go Back](#%EF%B8%8F-htvm-ide)

After cloning the repository, go to the `IDE` directory where the files are located:

**Navigate to the HTVM folder**

```bash
cd HTVM
```

**Then navigate to the IDE folder**

```bash
cd IDE
```

---

### 1. **Ensure Node.js and npm are Installed**

The HTVM IDE requires **Node.js** and **npm** to run.

If either **Node.js** or **npm** is not installed, follow the installation steps below.

#### **Installing Node.js and npm**

- **Windows**: Download the prebuilt installer from the official Node.js website:  
  [https://nodejs.org/en/download/prebuilt-installer](https://nodejs.org/en/download/prebuilt-installer)

- **Linux**:  
  1. Update your package index:
     ```bash
     sudo apt update
     ```
  2. Install Node.js and npm using your package manager:
     ```bash
     sudo apt install nodejs npm
     ```

---

#### **Check if Node.js is Installed**

To check if **Node.js** is installed, use the following command:

```bash
node --version
```

If Node.js is installed, this will display the version number, for example:

```
v20.11.0
```

but it doesn't really matter what version.

#### **Check if npm is Installed**

npm is a package manager that comes with Node.js. To check if **npm** is installed, use the following command:

```bash
npm --version
```

If npm is installed, this will display the version number, for example:

```
10.2.4
```

but it doesn't really matter what version.

---

### 2. **Install Project Dependencies**

In the `IDE` directory, install the required dependencies using npm:

```bash
npm install
```

This will install all the necessary packages listed in the `package.json` file.

> **Note**: You only need to run `npm install` **once** during the initial setup. After the dependencies are installed, you don't need to run it again unless you pull changes from the repository that update the dependencies.

---

### 3. **Start the HTVM IDE**

Once the dependencies are installed, you can launch the HTVM IDE using:

```bash
npm start
```

This will open the Electron application, providing the HTVM IDE interface.

---

#### Troubleshooting:

- If you encounter issues with `npm install` or `npm start`, make sure that **Node.js** and **npm** are correctly installed.
- On **Linux**, if you run into permission errors during installation, you may need to prepend `sudo` to the `npm install` or `npm start` commands (e.g., `sudo npm install`).

---

### **How to use the HTVM IDE and its Keyboard shortcuts**

[Go Back](#%EF%B8%8F-htvm-ide)

### **Defined Global Hotkeys**
1. **Run and Compile:**
   - **`F5`**: Runs the current file and saves it.
   - **`Ctrl+F7`**: Compiles the current file and saves it.

2. **File Management:**
   - **`Ctrl+S`**: Saves the current file.
   - **`Ctrl+N`**: Creates a new file
   - **`Ctrl+O`**: Opens an existing file
   - **`Ctrl+W`**: Saves and closes the current tab, updates file tracking, and manages active tabs.
   - **`Ctrl+Shift+T`**: Reopens the last closed tab and restores it to the active session.

3. **Tab Navigation:**
   - **`Ctrl+Tab`**: Switches between open tabs, with logic for cycling through tabs and tracking the most recent tab.

4. **Advanced Features:**
   - **`Ctrl+Shift+Alt+F`**: **Warning!** This command **permanently** formats the current code with no undo option. Use with extreme caution, as there is no way to recover the original formatting once this action is performed.
   - **`Ctrl+Shift+Alt+V`**: Toggles Vim mode on and off.

5. **Drag-and-Drop Support:**
   - Allows users to drag files into the IDE to open them as new tabs.

---

### **HTVM IDE Keyboard Shortcuts**

The HTVM IDE is built around the [Ace Editor](https://ace.c9.io/), a powerful, web-based code editor that offers many keyboard shortcuts for efficient navigation and editing. Below is a categorized list of the most commonly used keyboard shortcuts within the HTVM IDE.

---

#### **File Management**  
- **Select All**: `Ctrl-A`  
- **Go to Line**: `Ctrl-L`  
- **Replace**: `Ctrl-H`  
- **Find**: `Ctrl-F`  
- **Find Next**: `Ctrl-K`  
- **Find Previous**: `Ctrl-Shift-K`  
- **Select or Find Next**: `Alt-K`  
- **Select or Find Previous**: `Alt-Shift-K`  
- **Find All**: `Ctrl-Alt-K`  

#### **Editing and Navigation**  
- **Duplicate Selection**: `Ctrl-Shift-D`  
- **Remove Line**: `Ctrl-D`  
- **Toggle Comment**: `Ctrl-/`  
- **Toggle Block Comment**: `Ctrl-Shift-/`  
- **Undo**: `Ctrl-Z`  
- **Redo**: `Ctrl-Shift-Z` or `Ctrl-Y`  
- **Indent**: `Tab`  
- **Outdent**: `Shift-Tab`  
- **Block Indent**: `Ctrl-]`  
- **Block Outdent**: `Ctrl-[`  

#### **Cursor and Selection**  
- **Expand to Matching**: `Ctrl-Shift-M`  
- **Jump to Matching**: `Ctrl-\` or `Ctrl-P`  
- **Select to Matching**: `Ctrl-Shift-\` or `Ctrl-Shift-P`  
- **Add Cursor Above**: `Ctrl-Alt-Up`  
- **Add Cursor Below**: `Ctrl-Alt-Down`  
- **Align Cursors**: `Ctrl-Alt-A`  

#### **Line Movement and Manipulation**  
- **Move Line Up**: `Alt-Up`  
- **Move Line Down**: `Alt-Down`  
- **Copy Line Up**: `Alt-Shift-Up`  
- **Copy Line Down**: `Alt-Shift-Down`  
- **Sort Lines**: `Ctrl-Alt-S`  

#### **Scrolling and View**  
- **Scroll Up**: `Ctrl-Up`  
- **Scroll Down**: `Ctrl-Down`  
- **Page Up**: `PageUp`  
- **Page Down**: `PageDown`  
- **Select Page Up**: `Shift-PageUp`  
- **Select Page Down**: `Shift-PageDown`  

#### **Macros**  
- **Toggle Recording**: `Ctrl-Alt-E`  
- **Replay Macro**: `Ctrl-Shift-E`  

#### **Case Modification**  
- **To Uppercase**: `Ctrl-U`  
- **To Lowercase**: `Ctrl-Shift-U`  

#### **Miscellaneous**  
- **Show Settings Menu**: `Ctrl-,`  
- **Show Keyboard Shortcuts**: `Ctrl-Alt-H`  
- **Open Command Palette**: `F1`  

---

### HTVM IDE Property Files

[Go Back](#%EF%B8%8F-htvm-ide)

HTVM IDE uses property files with the extensions `.htpc` and `.htpr` for compiling and running your code. These files provide the commands needed to execute or compile your code based on the file type (e.g., `.cpp`, `.py`, `.js`). The files are located in the `/property files/` folder in the IDE, and you can create your own property files for different languages.

---

### File Extensions and Corresponding Property Files

For each programming language you use in HTVM, the property files should have matching names with the extension `.htpc` for compile commands and `.htpr` for run commands. For example:

- `cpp.htpr` or `cpp.htpc`
- `zig.htpr` or `zig.htpc`
- `lua.htpr` or `lua.htpc`
- `c.htpr` or `c.htpc`
- `asm.htpr` or `asm.htpc`

In other words, the file extension of the code corresponds to the name of the property file.

---

- **.htpc**: Property file for compiling when pressing `Ctrl+F7`
- **.htpr**: Property file for running your code when pressing `F5`

Here's how the syntax works in these property files:

- **Placeholders**:
  - `%FILENAME%`: Full file path of the file being processed
  - `%ONLYFILENAME%`: The filename without its extension
  - `%DIRFULLPATH%`: The full directory path of the file

- **Commands**:
  - `~~~`: A placeholder for space, used to replace any `~~~` occurrences in the commands

#### Example Property File (`ht.htpr`)

The following example shows how to set up a property file to run code in C++, Python, and JavaScript. In this example, the lines for Python and JavaScript are commented out, but they can be enabled by removing the semicolon (`;`).

```plaintext
; for cpp

HTVM "%FILENAME%" "C:\Users\The_M\OneDrive\Desktop\GitHub~~~Projects\HTVM\HTVM\HT-instructions.txt" "cpp"
g++ "%ONLYFILENAME%.cpp" "-o" "%ONLYFILENAME%"
cd "%DIRFULLPATH%" && "%ONLYFILENAME%.exe"

; for python

;HTVM "%FILENAME%" "C:\Users\The_M\OneDrive\Desktop\GitHub~~~Projects\HTVM\HTVM\HT-instructions.txt" "py"
;cd "%DIRFULLPATH%" && python "%ONLYFILENAME%.py"

; for js
;HTVM "%FILENAME%" "C:\Users\The_M\OneDrive\Desktop\GitHub~~~Projects\HTVM\HTVM\HT-instructions.txt" "js"
```

#### Breakdown of the Code:

1. **For C++**:
   - The `g++` command compiles the file into an executable.
   - The output executable is then run from the directory using `%DIRFULLPATH%`.

2. **For Python**:
   - This section is commented out, but it would run the Python script using the `python` command.

3. **For JavaScript**:
   - This section is also commented out, but it would run a JavaScript file.

#### How to Use the Property File:

1. **To Compile** (Ctrl+F7):
   - Press `Ctrl+F7` to compile your code based on the `.htpc` property file.
   - Ensure the correct commands are in place for your desired language.

2. **To Run** (F5):
   - Press `F5` to run your code based on the `.htpr` property file.
   - Make sure the relevant sections for your language are uncommented to run the commands properly.

#### Example Workflow:

1. **Compile C++**:
   - In the property file, uncomment the C++ section by removing the `;`.
   - Press `Ctrl+F7` to compile the C++ code.

2. **Run Python**:
   - Uncomment the Python section in the `.htpr` property file.
   - Press `F5` to run the Python script.
