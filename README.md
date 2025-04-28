# HTVM

# 🚧 **HTVM Is Still Under Development** 🚧

#### Please be aware that this README file provides information about HTVM, but not everything may be fully functional yet. Some links might not work, and some features are still in development. While this file outlines what HTVM aims to offer, it's not entirely accurate at the moment, so we recommend coming back later for a fully polished experience.

#### We expect most features to be operational by the end of April 2025, and everything should be completed by the end of May 2025.

# 🚧 **HTVM Is Still Under Development** 🚧

---

### HTVM: The Revolution in Programming

## **HTVM: The Adaptive, Multi-Language, Customizable Syntax and Code Generation Engine**

HTVM is a revolutionary system that empowers **you to design your own programming language** with **fully customizable syntax**, tailored precisely to your needs and approach.

Write code using your personalized keywords, operators, and structure, and HTVM's powerful engine will **generate equivalent code** for **15 distinct target languages**:

**C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript, and Groovy.**

HTVM fundamentally changes the programming experience with groundbreaking features:

- **Total Syntax Customization**: Define your own keywords, operators, block structures, comments, and more, without the limitations of traditional languages. Build a language that feels intuitive *to you*.
- **Multi-Target Code Generation**: Write your logic once in your custom HTVM language and generate native code for multiple platforms or environments simultaneously.
- **Simplified Dependency Management**: Leverage a rich set of built-in functions. HTVM automatically handles adding necessary library includes/imports in the *generated* code, reducing boilerplate in your HTVM source.
- **OSP (Ordinal Struct Programming)**: Utilize HTVM's built-in methodology for organizing code with hierarchical namespaces and explicit `struct` data containers. [See OSP Docs](#https://github.com/TheMaster1127/HTVM/blob/main/DOCUMENTATION.md#osp-ordinal-struct-programming)
- **Programming Blocks**: Seamlessly embed native code for any target language directly within your HTVM files for tasks requiring specific platform features or libraries. [See Programming Blocks Docs](#https://github.com/TheMaster1127/HTVM/blob/main/DOCUMENTATION.md#programming-blocks)
- **HTVM IDE**: Develop efficiently with a dedicated IDE featuring custom syntax highlighting (based on *your* rules), code completion, file management, and execution capabilities (JS execution directly, others via generated code).

HTVM aims to make programming faster, more accessible, more personalized, and ultimately, more powerful by putting you in control of the language itself.

---
**What is HTVM?**  
HTVM is an Adaptive, Multi-Language, Customizable Syntax and Code Generation Engine. It allows users to create their own programming languages. It’s not just about programming in a new language, but about designing your own syntax. This means that whether you're a professional programmer or even someone with basic computer skills, you can tailor the way you write code to fit your preferences. It’s like giving everyone the power to define the grammar rules for their code without having to be stuck with traditional programming language limitations.

BTW, HTVM is bootstrapped to `C++` so it can run locally and to `JavaScript` so it can work in the browser.

Alright, let's make this crystal clear.  

### **What HTVM Is NOT**  
HTVM is **not** a general-purpose transpiler that lets you convert between existing languages. You **cannot** use HTVM to convert Python to JavaScript, JavaScript to C++, or any other combination like that. If you have a Python script and want to turn it into JavaScript, **HTVM is not what you're looking for.**  

Similarly, you **cannot** take existing code from languages like Python, Java, or C# and convert it to HTVM. That’s simply not how HTVM works. **HTVM is its own thing**—it’s a language that has its own syntax, which can be customized to your liking, and that syntax is what gets converted into other languages.  

However, what **is** possible is converting **HTVM to HTVM**—meaning, you can have different custom syntaxes within HTVM and convert between them you can do that [here](https://www.example.com/). That’s something no other system really does. But again, **HTVM does not translate between standard programming languages—it only translates its own customizable syntax to these languages.**  

---

### **What HTVM Actually Is**  
HTVM is **a revolutionary, next-level programming system** that lets you define your own syntax and then convert that syntax into **fifteen different programming languages**:  

**C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript, and Groovy.**  

It’s not just a transpiler—it’s an entire **ecosystem** that allows you to **create your own language, structure it however you want, and then generate real-world code in multiple target languages.**  

But here’s where it gets insane: **HTVM is not locked into any one syntax.** You can **completely customize** how your code looks. 

### **Total Syntax Customization – The Ultimate Flexibility**  

HTVM **isn’t just about converting your custom language to multiple targets—it’s about letting you build your language exactly the way you want.** And when I say customizable, I mean **everything** is customizable.

---

### 🌐 OSP: Ordinal Struct Programming

HTVM features **OSP (Ordinal Struct Programming)**, its unique built-in methodology for structuring code. It uses hierarchical namespaces (`alliance`, `crew`) and data containers (`struct`) with mandatory full-path access.
-   OSP provides an alternative way to organize data and related procedures (`proc`), emphasizing explicitness and clear structure, which can be beneficial for managing project components without relying on traditional OOP features like inheritance.
-   For a detailed explanation, see the **[OSP (Ordinal Struct Programming) Documentation](https://github.com/TheMaster1127/HTVM/blob/main/DOCUMENTATION.md#osp-ordinal-struct-programming)**.
-   Or, build your own HTVM language using the [HTVM Syntax Configurator Website](https://themaster1127.github.io/HTVM/web-ui/), and the specific documentation for your language, including OSP details, will be generated. Then you can read about OSP.

---

### 🛠️ HTVM IDE: Integrated development environment
To enhance your development experience, HTVM comes with a dedicated **HTVM IDE**, featuring:  
- Syntax highlighting.  
- Code completion for efficient programming.  
- And more see [🛠️ HTVM IDE](#%EF%B8%8F-htvm-ide)

---

### 📚 Documentation
The documentation for your HTVM language will be generated once you create it here on the [HTVM Syntax Configurator Website](https://themaster1127.github.io/HTVM/).

---

### 🔄 HTVM to HTVM Converter
**Description**: Since HTVM allows you to convert between different HTVM syntaxes, you can easily convert code written in one HTVM language to another. By obtaining the `HTVM-instructions.txt` file from your own language or someone else's, you can take their code and convert it into your language, or vice versa. This flexibility makes it easy to work with multiple HTVM languages and customize your programming experience to your needs.

[Visit the HTVM Converter Site](https://www.example.com/)

---

## Using HTVM Online

When you visit the [HTVM Configuration Website](https://themaster1127.github.io/HTVM/web-ui/), part of the main [HTVM website](https://themaster1127.github.io/HTVM/), you'll be welcomed by a powerful and customizable interface for creating your own programming language.

### Step 1: Create Your Language

Start by clicking **Create** to generate your language. Without this step, the interface will remain empty.

### Step 2: Customize Your Language

You'll find **many input boxes** and **toggle switches** to fully control your language's syntax and behavior.  

- Use **Preview** to instantly visualize how your language looks with **syntax highlighting**.

### Step 3: IDE Environment

Once you've customized your language, click the **IDE** button to enter a fully-featured environment that provides:  
- **File system support** for managing files and projects.  
- **Automatic Syntax Highlighting** based on your custom language.  
- **Autocomplete** for a faster coding experience.  
- **Run Code** to execute your code directly in JavaScript, just like writing inside an HTML file and seeing the output in the console.  

You can also **convert your code to any of the 15 supported programming languages**, but only JavaScript can be executed directly on the website. For other languages, you need to copy the output and run it locally.

### Step 4: Build Your Language

When you're done, come back to the configuration site and click **Build** to generate a **zip folder** containing:  
- An **HTML file** with custom syntax highlighting and example code in your language.  
- A **Markdown file** without syntax highlighting for environments without browser access.  
- A **HTVM-instructions.txt** file that contains detailed instructions on how to use your language both locally and in the browser.  
- And potentially some additional files.

### Local Usage

To use your language offline, click [📘 Usage](#-usage).

---

### Table of Contents

1. [📘 Usage](#-usage)  
   **Description**: Learn how to compile and execute your language code using HTVM and the HTVM IDE.

2. [📂 Adding Built-In Functions](#-adding-built-in-functions)  
   **Description**: Add custom built-in functions to your language by following simple syntax rules.

3. [📜 Documentation Regeneration](#-documentation-regeneration)  
   **Description**: Update your language’s documentation whenever new features or changes are made.

4. [🛠️ HTVM IDE](#%EF%B8%8F-htvm-ide)  
   **Description**: Set up and use the HTVM IDE for coding, testing, and compiling your language.
     
5. [💡 Why HTVM Was Created: Understanding Its Purpose, Problems Solved, Use Cases, and Who It Benefits](#-why-htvm-was-created-understanding-its-purpose-problems-solved-use-cases-and-who-it-benefits)  
   **Description**: Delve into the core motivations behind HTVM, what it aims to achieve, the specific problems it tackles, practical applications, and identify who stands to gain the most (and who might not).
 
6.  [🤔 Concerns, Questions, and Misunderstandings of HTVM](#-concerns-questions-and-misunderstandings-of-htvm)  
    **Description**: Addresses common questions and potential concerns about HTVM's feasibility, features, and development, providing the creator's perspective.

7.  [🏛️ The Philosophy Of HTVM](#️-the-philosophy-of-htvm)  
    **Description**: Understand the core principles driving HTVM: minimizing keystrokes, maximizing customization, enhancing accessibility, and empowering the developer.

8. [⚙️ What Customizations HTVM Offers](#%EF%B8%8F-what-customizations-htvm-offers)    
   **Description**: Explore the capabilities and features of HTVM that allow you to configure and customize your programming environment, making your coding experience more efficient and tailored to your needs.


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
   - Edit `HTVM-instructions.txt` directly (NOT RECOMMENDED!).  
     - Each line corresponds to the same line in `HTVM-instructions-VERY-SIMPLE-DOCS.txt`.  

#### Usage of the HTVM compiler
```bash
HTVM <yourCodeFileName.yourExtension> <HTVM-instructions.txt> [optional LangToTranspileTo] [optional HTVM-instructions2.txt for HTVM to HTVM the targer HTVM lang]
```  

#### Options  
- **Required Parameters**:  
  - `yourCodeFileName.yourExtension`: The source code file.  
  - `HTVM-instructions.txt`: Instructions file for transpilation.  
- **Optional**:  
  - Specify the target language (`cpp`, `py`, `js`, `go`, `lua`, `cs`, `java`, `kt`, `rb`, `nim`, `ahk`, `swift`, `dart`, `ts`, `groovy`, `htvm` or <yourExtension>) directly in the command.
  - Another HTVM instruction file so when you are converting to another HTVM lang you must alos tell HTVM what is the syntax of the targer HTVM lang.

**Example**:  
```bash
HTVM main.htvm HTVM-instructions.txt cpp
```

or HTVM to HTVM:

```bash
HTVM main.htvm HTVM-instructions.txt htvm HTVM-instructions2.txt
```  

### 3. Compile and Run `HTVM`

1. **Compile `HTVM.cpp`**:  
   **Recommended Command**:  
   ```bash
   g++ HTVM.cpp -o HTVM
   ```  


2. **Run the Transpiler**:  
   After compiling, you will get a new executable file.  

   **General Usage**:  
   ```bash
   HTVM main.htvm HTVM-instructions.txt cpp
   ```  

   **Linux Users**:  
   Prepend `./` to the command:  
   ```bash
   ./HTVM main.htvm HTVM-instructions.txt cpp
   ```  

3. **Specify Target Language (Optional)**:  
   Add `cpp`, `py`, `js`, `go`, `lua`, `cs`, `java`, `kt`, `rb`, `nim`, `ahk`, `swift`, `dart`, `ts`, `groovy`, `htvm` or <yourExtension> at the end of the command to specify the target language.  

   **Examples**:  
   - Generate C++ code:  
     ```bash
     HTVM main.htvm HTVM-instructions.txt cpp
     ```  
     For Linux:  
     ```bash
     ./HTVM main.htvm HTVM-instructions.txt cpp
     ```  

   - Generate Python code:  
     ```bash
     HTVM main.htvm HTVM-instructions.txt py
     ```  
     For Linux:  
     ```bash
     ./HTVM main.htvm HTVM-instructions.txt py
     ```  

   - Generate JavaScript code:  
     ```bash
     HTVM main.htvm HTVM-instructions.txt js
     ```  
     For Linux:  
     ```bash
     ./HHTVM main.htvm HTVM-instructions.txt js
     ```  

### And so on HTVM can convert to 15 languages `cpp`, `py`, `js`, `go`, `lua`, `cs`, `java`, `kt`, `rb`, `nim`, `ahk`, `swift`, `dart`, `ts`, `groovy`, `htvm` or yourExtension

--- 

### 📂 Adding Built-In Functions  

[Go Back To The Table of Contents ](#table-of-contents)

**Description**: Add custom built-in functions to your language by following simple syntax rules.

1. Open `HTVM-instructions.txt`.  
2. Copy the last function block and paste it at the bottom.  
3. Follow these rules:  
   - **Language Specification**: Use `lang: cpp`, `lang: py`, `lang: js`, `lang: go`, `lang: lua`, `lang: cs`, `lang: java`, `lang: kt`, `lang: rb`, `lang: nim`, `lang: ahk`, `lang: swift`, `lang: dart`, `lang: ts`, or `lang: groovy` to define the language-specific implementation.
   - **Function Name**: Use `name: functionName`.  
   - **Libraries**: List required libraries with a `|` delimiter. For example:  
      - **C++**: `libs: #include <iostream>|#include <cstdlib>`
      - **JavaScript (not in a full .html file)**: `libs: import { readFileSync } from 'fs';|import { EventEmitter } from 'events';`
      - **JavaScript (in a full .html file)**: `libs: <script src="https://cdn.jsdelivr.net/npm/sweetalert2@11"></script>`
      - **JavaScript (in a full .html file for more than one)**: `libs: <script src="https://cdn.jsdelivr.net/npm/sweetalert2@11"></script>|<script src="myModule.js"></script>`
      - For other languages, just use the same format. For `Go`, use `libs: )|"theLibName"`. The reason for using `)` is that in HTVM, it doesn't know when the import `()` ends, so we add the `)` as a placeholder. It ensures that the import is correctly handled and will be sorted out at the end. Also, don't worry about including the same lib multiple times, since HTVM will remove duplicates.
   - **Description**:  
     - Format:  
       ```  
       description: string~~~[One-line description of the function]~~~Here is how the function looks:~~~```~~~[Function signature]~~~```  
       ```  
     - Example:  
       ```  
       description: string~~~Sort is a function to sort elements based on various criteria like numeric, random, alphabetical order, etc.~~~Here is how the function looks:~~~```~~~Sort(string input, [string options = ""])~~~```  
       ```

       Note: The ~~~ delimiters in the description section are placeholders that will be replaced with new lines in the final documentation.

**Here is how a build-in function in HTVM-instructions.txt looks like:**

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

MAKRE SURE IT SATRST WHIT description: and all in one code block

description: string~~~StrTitleCase is a func balalbla bla bal~~~here is how the func looks like:~~~```htvm~~~StrTitleCase(string, [optanalName], string, [optanal], string, [optanal], [optanal])~~~```~~~

it must be ```htvm not ```cpp or others IT MUST BE ```htvm

all of the ~~~ and all the same format DONT change it only chamge words

allways start like this description: category_name~~~

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

respond in a ```txt all in one line

so the ~~~ = to a new line ok ~~~ is a new line and the first one where we typed string is the category and it must alwas be one word the bets word for thet category like string math gui io files bla...
THE description BUST BE ONLY IN ONE LINE
here is func and replay in one line:
================================================

// Function to sleep for a specified number of milliseconds
void Sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

```  

Open it in a text editor and make sure the response is in 1 line. Otherwise, if ChatGPT replies in more than one line, tell it:

```txt
I SAID REPLY IN ONE LINE
```

**Important**: Do not modify the first 162 lines of `HTVM-instructions.txt`.  

---

### 📜 Documentation Regeneration  

[Go Back To The Table of Contents ](#table-of-contents)

**Description**: Update your language’s documentation whenever new features or changes are made.

Go to the [HTVM Syntax Configurator Website](https://themaster1127.github.io/HTVM/), make your changes to your language, build your language, and you will get the new DOCUMENTATION. Or:

Regenerate `DOCUMENTATION.md` or `DOCUMENTATION.html` using:  
1. Compile the `DOCUMENTATION_Generator.cpp` file:  
   ```bash
   g++ DOCUMENTATION_Generator.cpp -o DOCUMENTATION_Generator
   ```  

2. Run the executable:  
   ```bash
   DOCUMENTATION_Generator.exe HTVM-instructions.txt
   ```  

   or in linux

   ```bash
   ./DOCUMENTATION_Generator HTVM-instructions.txt
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
  1. Open your terminal and update your package index:
     ```bash
     sudo apt update
     ```
  2. Install Node.js and npm using your package manager:
     ```bash
     sudo apt install nodejs npm
     ```

   > **Note**: Ensure you are using a terminal with `sudo` privileges to install the packages.

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

The specific version doesn't matter as long as it's compatible.

#### **Check if npm is Installed**

npm is a package manager that comes with Node.js. To check if **npm** is installed, use the following command:

```bash
npm --version
```

If npm is installed, this will display the version number, for example:

```
10.2.4
```

Again, the specific version doesn't matter as long as it's compatible.

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

#### **Troubleshooting**:

- If you encounter issues with `npm install` or `npm start`, make sure that **Node.js** and **npm** are correctly installed.
- On **Linux**, if you run into permission errors during installation, prepend `sudo` to the `npm install` or `npm start` commands (e.g., `sudo npm install`).

---

### **How to Use the HTVM IDE and Its Keyboard Shortcuts**

[Go Back](#%EF%B8%8F-htvm-ide)

### **Defined Global Hotkeys**
1. **Run and Compile:**
   - **`F5`**: Runs the current file and saves it.
   - **`Ctrl+F7`**: Compiles the current file and saves it.

2. **File Management:**
   - **`Ctrl+S`**: Saves the current file.
   - **`Ctrl+N`**: Creates a new file.
   - **`Ctrl+O`**: Opens an existing file.
   - **`Ctrl+W`**: Saves and closes the current tab, updates file tracking, and manages active tabs.
   - **`Ctrl+Shift+T`**: Reopens the last closed tab and restores it to the active session.

3. **Tab Navigation:**
   - **`Ctrl+Tab`**: Switches between open tabs, with logic for cycling through tabs and tracking the most recent tab.

4. **Advanced Features:**
   - **`Ctrl+Shift+Alt+F`**: **Warning!** This command **permanently** formats the current code with no undo option. Use with extreme caution, as there is no way to recover the original formatting once this action is performed.
   - **`Ctrl+Shift+Alt+V`**: Toggles Vim mode on and off.

5. **Drag-and-Drop Support:**
   - Allows users to drag files into the IDE to open them as new tabs.

6. **Others:**
   - Press `Ctrl+Shift+R` to reload the IDE.

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

---

### HTVM IDE Property Files

[Go Back](#%EF%B8%8F-htvm-ide)

HTVM IDE uses property files with the extensions `.htpc` and `.htpr` for compiling and running your code. These files provide the commands needed to execute or compile your code based on the file type (e.g., `.cpp`, `.py`, `.js` or more...). The files are located in the `/property files/` folder in the IDE, and you can create your own property files for different languages.

---

### File Extensions and Corresponding Property Files

For each programming language you use in the **HTVM IDE**, the property files should have matching names with the extension `.htpc` for compile commands and `.htpr` for run commands. For example:

| Language        | File Extension     | HTVM Property File Extensions |
|-----------------|--------------------|-------------------------------|
| C++             | .cpp               | `cpp.htpc` (compile), `cpp.htpr` (run)  |
| Python          | .py                | `py.htpc` (compile), `py.htpr` (run)    |
| JavaScript      | .js                | `js.htpc` (compile), `js.htpr` (run)    |
| Go              | .go                | `go.htpc` (compile), `go.htpr` (run)    |
| Lua             | .lua               | `lua.htpc` (compile), `lua.htpr` (run)  |
| C#              | .cs                | `cs.htpc` (compile), `cs.htpr` (run)    |
| Java            | .java              | `java.htpc` (compile), `java.htpr` (run)|
| Kotlin          | .kt                | `kt.htpc` (compile), `kt.htpr` (run)    |
| Ruby            | .rb                | `rb.htpc` (compile), `rb.htpr` (run)    |
| Nim             | .nim               | `nim.htpc` (compile), `nim.htpr` (run)  |
| AutoHotKey      | .ahk               | `ahk.htpc` (compile), `ahk.htpr` (run)  |
| Swift           | .swift             | `swift.htpc` (compile), `swift.htpr` (run)|
| Dart            | .dart              | `dart.htpc` (compile), `dart.htpr` (run)|
| TypeScript      | .ts                | `ts.htpc` (compile), `ts.htpr` (run)    |
| Groovy          | .groovy            | `groovy.htpc` (compile), `groovy.htpr` (run)|

Or any other file extention

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

#### Example Property File (`htvm.htpr`)

The following example shows how to set up a property file to run code in C++, Python, and JavaScript. In this example, the lines for Python and JavaScript are commented out, but they can be enabled by removing the semicolon (`;`).

```plaintext
; for cpp

"C:\Users\The_M\OneDrive\Desktop\GitHub~~~Projects\HTVM\HTVM\HTVM.exe" "%FILENAME%" "C:\Users\The_M\OneDrive\Desktop\GitHub~~~Projects\HTVM\HTVM\HTVM-instructions.txt" "cpp"
g++ "%ONLYFILENAME%.cpp" "-o" "%ONLYFILENAME%"
cd "%DIRFULLPATH%" && "%ONLYFILENAME%.exe"

; for py

;"C:\Users\The_M\OneDrive\Desktop\GitHub~~~Projects\HTVM\HTVM\HTVM.exe" "%FILENAME%" "C:\Users\The_M\OneDrive\Desktop\GitHub~~~Projects\HTVM\HTVM\HTVM-instructions.txt" "py"
;cd "%DIRFULLPATH%" && node "%ONLYFILENAME%.js"

; for js

;"C:\Users\The_M\OneDrive\Desktop\GitHub~~~Projects\HTVM\HTVM\HTVM.exe" "%FILENAME%" "C:\Users\The_M\OneDrive\Desktop\GitHub~~~Projects\HTVM\HTVM\HTVM-instructions.txt" "js"
;cd "%DIRFULLPATH%" && node "%ONLYFILENAME%.js"
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

---

### 💡 Why HTVM Was Created: Understanding Its Purpose, Problems Solved, Use Cases, and Who It Benefits

[Go Back To The Table of Contents ](#table-of-contents)

#### Why was HTVM made?

HTVM was born out of a frustration with the limitations and complexities inherent in traditional programming languages. The core motivations were:

*   **To Combat Rigidity:** Existing languages force developers into predefined syntaxes and paradigms, stifling creativity and potentially slowing down development. HTVM was created to break free from these constraints.
*   **To Fulfill the Promise of Simplicity:** While many languages aim for simplicity, they often fall short. HTVM was designed to empower the *user* to define what simplicity means to them through customizable syntax. The result? Less verbose code means potentially smaller source files, too.
*   **To Increase Coding Speed and Reduce Keystrokes:** Let's be real, typing less is faster. HTVM is built around minimizing keystrokes. You can create super concise syntax, like maybe `Loop, 5`. Now, some people might say, "But autocomplete makes standard languages fast!" Sure, it helps. But guess what? The [HTVM IDE](#%EF%B8%8F-htvm-ide) has autocomplete too! And even *with* autocomplete, writing `Loop, 5` is fundamentally quicker and needs fewer completions than something like Python's `for i in range(5):`. HTVM aims to reduce the sheer amount you have to type or autocomplete in the first place.
*   **To Enable True Personalization:** Programming should adapt to the programmer, not the other way around. HTVM was built to allow anyone to create a language that fits their mental model and workflow.

#### What is HTVM made for?

HTVM is fundamentally a **meta-programming system** and **language workbench** designed for:

1.  **Creating Custom Programming Languages:** Its primary purpose is to let users define their *own* syntax, keywords, operators, and overall language structure.
2.  **Multi-Target Code Generation:** Translating code written in a user's custom HTVM language into 15 different standard programming languages (C++, Python, JS, etc.).
3.  **Simplifying Development:** Making coding more intuitive and potentially faster by allowing personalized syntax and aiming to reduce library import boilerplate through built-in functions. You can add your own, too.
4.  **Exploring New Methodology For Structuring Code:** Introducing concepts like OSP (Ordinal Struct Programming) as alternatives to traditional approaches.
5.  **Bridging Abstraction and Native Code:** Providing [Programming Blocks](https://github.com/TheMaster1127/HTVM/blob/main/DOCUMENTATION.md#programming-blocks) as a mechanism to include target-specific code seamlessly when HTVM's abstractions aren't enough or native features are required.
6.  **Inter-HTVM Conversion:** Enabling conversion *between different HTVM language syntaxes*, allowing collaboration even when individuals use personalized versions of HTVM.

#### What problem does it solve?

HTVM addresses several key pain points in modern programming:

1.  **The Broken Promise of Simplicity:** Delivers genuine simplicity by letting the user define it, abstracting the complexity of target languages.
2.  **Syntax Rigidity:** Offers unparalleled freedom from fixed language rules, allowing personalized, readable code.
3.  **Coding Speed and Fewer Keystrokes:** Focuses on minimizing typing through concise, customizable syntax (e.g., `Loop, 5`). Even with the [HTVM IDE](#%EF%B8%8F-htvm-ide)'s autocomplete, the base syntax requires less input compared to more verbose languages even Python.
4.  **Cognitive Load in Multi-Language Projects:** Provides a potential single source language that generates code for multiple targets, reducing the mental switching cost.
5.  **High Barrier to Entry:** Significantly lowers the entry barrier for non-programmers or beginners by allowing intuitive, self-designed languages.
6.  **Accessibility Challenges (e.g., ADHD/Dyslexia):** Standard languages have long, complex, or easily misspelled keywords (like `push_back`, `finally`, `continue`). For people with dyslexia or ADHD, this can be a real barrier. HTVM allows customizing these keywords to something shorter, simpler, or personally memorable, making coding significantly more accessible. (As the creator, even I sometimes struggle to spell `continue` right!).
7.  **Collaboration Across Personalized Syntaxes:** Allows developers using different custom HTVM syntaxes to understand each other's code by converting it to their own preferred format.
8.  **Abstraction Gaps:** Intelligently uses [Programming Blocks](https://github.com/TheMaster1127/HTVM/blob/main/DOCUMENTATION.md#programming-blocks) to provide access to native features without sacrificing the benefits of the high-level HTVM language.

#### What it can be used for?

HTVM's flexibility opens up a wide range of applications:

*   **Domain-Specific Languages (DSLs):** Creating languages optimized for fields like science, game development, finance, data analysis, education, etc.
*   **Educational Tools:** Teaching programming concepts by allowing students to experiment with language design, focusing on logic over syntax hurdles.
*   **Rapid Prototyping:** Quickly sketching application logic and generating functional code for multiple platforms simultaneously.
*   **Personal Automation & Scripting:** Enabling individuals (even non-coders) to automate tasks using a syntax they find comfortable.
*   **Accessibility Tools:** Designing coding environments tailored for users with specific needs (like dyslexia).
*   **Enhanced Collaboration:** Allowing team members to use personalized syntaxes locally while sharing code in a standard format or enabling easy conversion between team members' preferred HTVM languages.
*   **Research & Language Experimentation:** Exploring novel programming paradigms, syntax ideas, and language features.
*   **Creative Coding:** Designing intuitive languages for artists and designers working on generative or interactive projects.

#### Who should use it?

HTVM is particularly well-suited for:

*   **Educators and Students:** For teaching and learning programming fundamentals flexibly.
*   **Domain Experts (Non-Programmers):** Scientists, analysts, artists needing custom tools without deep coding knowledge.
*   **Developers Seeking Customization:** Programmers frustrated by existing syntax who desire ultimate control.
*   **Hobbyists and Language Enthusiasts:** Anyone interested in the art and science of language design.
*   **Prototypers:** Individuals or teams needing fast, multi-target code generation.
*   **DSL Creators:** Anyone needing to build a specialized language for a specific niche.
*   **Individuals Benefiting from Simplified Syntax:** Including those with dyslexia, ADHD, or anyone who finds standard syntax cumbersome.
*   **Collaborative Teams:** Who want to leverage individual preferences while maintaining understandability (via HTVM-to-HTVM conversion).

#### Who should not use it (or should consider carefully)?

While powerful, HTVM might not be the *best* fit for *every* scenario:

1.  **Professionals (10-15+ years) Highly Optimized in Standard Languages:** If you're extremely fluent and fast in multiple standard languages, adopting HTVM *might* initially feel different. It *could* slow you down temporarily. **However,** once comfortable, the ability to generate code for 15 languages, the focus on fewer keystrokes, and custom abstraction *could significantly speed up* your development, especially for multi-target projects or where standard verbosity is a pain. It really depends on what you're doing and if you leverage HTVM's strengths.
2.  **If You Need Seamless Integration with Mature Ecosystems *Instantly*:** Projects heavily reliant on specific, complex native frameworks or tooling *might* require some integration effort with the generated code. You use the target language's tools, but there's an abstraction layer.
3.  **For Extreme, Low-Level Performance Optimization:** While generated code performance depends on the target language, scenarios requiring hand-tuned, cycle-critical optimization *might* be better served by direct native coding.
4.  **In Large Teams Without a Shared HTVM Standard *or Workflow*:** The customization power *could* lead to fragmentation *if* a team doesn't agree on a workflow. **However, HTVM enables a powerful solution:** team members can code in their *own* preferred HTVM syntax locally. Before pushing to a shared repo, they convert their code to an agreed-upon *standard team HTVM syntax*. Anyone pulling can then read the standard or convert it back to their own preference. This allows both individual freedom and team consistency.
5.  **If Wide Adoption is Paramount *Today*:** Established languages offer larger current communities and library ecosystems. HTVM prioritizes innovation and customization over immediate ubiquity.

#### But Wait, What About Programming Blocks?

Okay, let's address this head-on. Some might think, "Why bother with HTVM's custom stuff if I can just dump native code into [Programming Blocks](https://github.com/TheMaster1127/HTVM/blob/main/DOCUMENTATION.md#programming-blocks)?" Honestly, if that's all you do, you're missing the entire point of HTVM. Blocks are awesome, but they're the *escape hatch*, the *supplement*, not the main event. You use them when you absolutely *need* a specific native library HTVM doesn't cover yet, or for that tiny, hyper-optimized performance bit, or maybe for something HTVM just hasn't built-in yet.

The *real* power, the reason HTVM exists, is writing the bulk of your logic in *your* clean, custom HTVM syntax and letting it generate code for 15 languages. If you just fill your files with programming blocks, you're basically just using HTVM as a weird preprocessor, throwing away the simplicity and multi-target magic. Use the HTVM language first, blocks second. There's literally no reason *not* to use HTVM's core features if you're using HTVM; blocks are just there for when you hit the edges.

---

### 🤔 Concerns, Questions, and Misunderstandings of HTVM

[Go Back To The Table of Contents ](#table-of-contents)

While developing HTVM, we anticipate potential questions and concerns. Here are some common points and the creator's perspective on how HTVM addresses them:

1.  **Concern: Feasibility and Complexity Across 15 Languages**
    *   *The Question:* Reliably mapping *any* custom syntax to 15 target languages, handling their nuances (type systems, error handling, standard libraries, concurrency models, idioms), seems extraordinarily difficult. How can HTVM ensure correct, idiomatic code without excessive bugs?
    *   **The Creator's Perspective:** This is indeed the core challenge, but it's managed strategically.
        *   **Bootstrapping:** HTVM is bootstrapped to C++ and JavaScript, ensuring the core engine's logic is sound and tested in two key environments.
        *   **Daily Use & Testing:** As the creator, I use HTVM daily. Bugs are found and fixed constantly, making the system increasingly robust. Bugs are actually rare now and typically minor.
        *   **Pragmatic Mapping:** HTVM doesn't try to magically map *every* conceivable language feature perfectly across all 15 targets if it's impractical or leads to fragile code. Some complex or highly language-specific constructs (like complex switch cases or nuanced error handling in Go/Lua) are intentionally *not* directly mapped.
        *   **Programming Blocks as a Solution:** For cases where direct mapping is impossible or undesirable, **[Programming Blocks](https://github.com/TheMaster1127/HTVM/blob/main/DOCUMENTATION.md#programming-blocks)** are the *designed* solution. They allow users to leverage native code precisely when needed, acknowledging language differences rather than trying to force an imperfect universal abstraction.
        *   **Simplicity Focus:** HTVM prioritizes a powerful *core* set of customizable features that *can* be reliably translated.

2.  **Concern: "Under Development" Status**
    *   *The Question:* The README states HTVM is under development with a 2025 timeline. Does this mean the claims are purely theoretical and nothing works yet?
    *   **The Creator's Perspective:** The "Under Development" status is an honest statement of the current phase. It means not *all* features described are fully polished or implemented *yet*. However, the core engine exists, is actively used by the creator, and is demonstrably functional (especially given it's bootstrapped). The timeline reflects the goal for full feature completion and polish. It's about managing expectations, not indicating a lack of progress.

3.  **Concern: Parser Robustness and Ambiguity**
    *   *The Question:* Customizable syntax can be notoriously difficult to parse without ambiguity. How does HTVM handle conflicting custom rules or syntax edge cases?
    *   **The Creator's Perspective:** The parser (HTVM v2) was a major focus and months of development. While customizable syntax presents challenges, ambiguity is minimized through:
        *   **Careful Design:** The range of customizations, while vast, has constraints designed to prevent most ambiguities.
        *   **Testing:** Extensive testing identifies and resolves edge cases.
        *   **Clear Rules:** The configuration process guides users towards defining unambiguous syntax. The system is designed to handle the defined customizations reliably.

4.  **Concern: Debugging Experience**
    *   *The Question:* Debugging usually happens in the generated code (C++, Python, etc.). Won't it be hard to trace errors from complex generated code back to the original custom HTVM source?
    *   **The Creator's Perspective:** This is a valid concern, addressed in several ways:
        *   **Readable Generated Code:** The output code is intentionally formatted (like K&R style) and structured to closely mirror the original HTVM logic, making manual tracing feasible. It's not obfuscated spaghetti code.
        *   **Planned IDE Integration:** The future HTVM IDE aims to include AI-powered assistance (leveraging APIs like Gemini, free tier sufficient for many users) specifically designed to analyze errors in the generated code and pinpoint the corresponding line(s) in the *original HTVM source*, potentially even suggesting fixes.
        *   **Standard Techniques:** Basic debugging (like adding print statements in your HTVM code) works as expected.

5.  **Concern: Leaky Abstractions & Performance**
    *   *The Question:* Will generated code be performant? Does it leverage target language strengths, or is it generic? Does over-reliance on Programming Blocks defeat the purpose?
    *   **The Creator's Perspective:**
        *   **Performance:** HTVM itself doesn't dictate runtime performance; that depends on the target language's compiler or interpreter. HTVM focuses on generating *correct* code that the target environment optimizes.
        *   **Idiomatic Code:** Where possible, HTVM tries to map concepts idiomatically (e.g., handling Python's `global` scope correctly through the global keyword).
        *   **Programming Blocks are Supplemental:** Blocks are intended for *specific* needs (native libraries, hyper-optimization, features HTVM doesn't cover). The creator finds they are rarely needed for core logic, indicating the main HTVM language is powerful on its own. Using blocks is leveraging HTVM's flexibility, not negating its benefits.

6.  **Concern: "No More Build-In Libraries" Claim**
    *   *The Question:* This seems potentially misleading, as built-in functions clearly wrap target language libraries/imports.
    *   **The Creator's Perspective:** The claim is about the **user experience in the HTVM source code**. The goal is *simplicity* for the HTVM coder – you often don't need to write `import` or `#include` statements yourself because HTVM manages adding the necessary dependencies to the *generated* code based on the built-in functions used. The dependencies still exist, but the *boilerplate* is abstracted away from the HTVM developer.

7.  **Concern: OSP Explanation**
    *   *The Question:* The README mentions OSP but doesn't explain it.
    *   **The Creator's Perspective:** Correct. OSP (Ordinal Struct Programming) is a distinct concept detailed in the main HTVM documentation (which is generated based on your custom language configuration). The README serves as an overview and links to deeper resources.

8.  **Concern: Maintenance Burden**
    *   *The Question:* Maintaining correct transpilation for 15 evolving languages seems like a massive task.
    *   **The Creator's Perspective:** It's significant, but manageable:
        *   **Bootstrapping:** Ensures the core C++/JS targets stay robustly maintained.
        *   **Practical Usage:** Most users will target only one language at a time and only some handful of users will handle 2 or even more languages at a time for a given project. Maintenance can be prioritized based on usage and reported issues. It's not typically necessary for all 15 to be perfectly up-to-the-minute simultaneously for every user.

9.  **Concern: Hype vs. Reality**
    *   *The Question:* The enthusiastic tone ("revolution," "insane") sets very high expectations for an unfinished project.
    *   **The Creator's Perspective:** The enthusiasm is genuine, born from using HTVM and believing in its potential to solve real problems and offer unprecedented flexibility. While ambitious, the claims are based on the implemented design, the bootstrapped foundation, and the clear path forward. The "insanity" refers to the level of customization and multi-target power, which is truly unique.

---

### 🏛️ The Philosophy Of HTVM

[Go Back](#table-of-contents)

HTVM isn't just about technical features; it's driven by a core philosophy aimed at fundamentally improving the developer experience. Traditional programming often feels restrictive, verbose, and unnecessarily complex. HTVM challenges this status quo.

**1. Fewer Keystrokes, Maximum Efficiency:**
At its heart, HTVM is built to **minimize the effort required to express logic**. Inspired by the conciseness of languages like AutoHotKey, HTVM encourages syntax that gets the job done with fewer characters. Features like simplified loop structures (`Loop, 5`) and customizable commands aim to drastically reduce typing compared to the often-boilerplate-heavy syntax of mainstream languages.
Some might argue, "But IDEs have autocomplete!" HTVM has autocomplete too, via its dedicated IDE. However, **autocomplete helps you type existing verbose syntax faster; HTVM aims to make the syntax itself fundamentally shorter and more direct**. There's simply less *to* type or autocomplete in the first place. Why write `for i in range(5):` when `Loop, 5` achieves the same result with less mental and physical friction?

**2. Absolute Customization: Programming Your Way:**
Standard languages force you into their predefined structure. HTVM believes **the language should adapt to the programmer, not the other way around**. This is the "Linux vs Windows" principle applied to coding:
*   *Standard Languages (like Windows):* Offer a fixed experience. You learn *their* rules, *their* keywords, *their* structure.
*   *HTVM (like Linux):* Gives you the keys to the kingdom. You define the rules, keywords, operators, and structure that best fit **your mental model and workflow**. Don't like curly braces? Use Pythonic indentation or Lua/Ruby style with the `end` keyword **which is also customizable**. Find `true`/`false` too long? Use `T`/`F` or `on`/`off`. It's about building an environment where you feel most productive and comfortable.

**3. Accessibility First:**
The rigidity of standard syntax can be a significant barrier. Long, complex, or easily misspelled keywords (`finally` or `continue`) can be particularly challenging for individuals with dyslexia, ADHD, or even just everyday typos. HTVM's customization is a powerful accessibility tool. By allowing **any keyword to be changed to something shorter, simpler, or personally memorable**, HTVM dramatically lowers the barrier, making coding more attainable and less frustrating for everyone. (Even the creator sometimes misspells `continue`!).

**4. Sensible Abstraction with Escape Hatches:**
HTVM provides high-level abstractions and built-ins to simplify common tasks. However, it acknowledges that no abstraction is perfect. That's why **[Programming Blocks](#https://github.com/TheMaster1127/HTVM/blob/main/DOCUMENTATION.md#programming-blocks)** exist. They are the designed escape hatch, allowing you to drop down to native target-language code *when necessary*. But the core philosophy remains: write the bulk of your logic in your clean, custom HTVM syntax. Use blocks as supplements for specific libraries or optimizations, not as the default. Abusing programming blocks misses the point and negates the benefits of HTVM's simplification and multi-target generation.

**5. Developer Control vs. The Limits of AI Generation:**
There's increasing talk about AI writing code or even creating languages. Some might wonder, "Can't AI just do what HTVM does?" or say "AI can do that!" The answer is definitively **No**, especially at scale and with the level of personalized control HTVM offers.

*   **Structured, Consistent Generation:** HTVM translates your custom syntax into target languages based on **defined, repeatable rules** stored in your `HTVM-instructions.txt`. This ensures consistent, predictable, and debuggable output every time. Current AI code generation, while impressive, often lacks this rigid consistency. Asking an AI to translate the same complex logic multiple times might yield slightly different, potentially less reliable results.
*   **Scalability and Reliability:** Imagine asking an AI to translate a million-line project written in your custom HTVM syntax into 15 different languages, ensuring perfect feature parity and correctness across all targets. The computational cost, potential for hallucinated errors, and lack of verifiable consistency make this **impractical, unreliable and straight-up impossible** with today's AI. HTVM, built on a deterministic engine, handles this conversion reliably, no matter the project size.
*   **Deep User-Defined Syntax:** AI *might* generate *a* language, but it cannot intuit the deeply personalized, nuanced syntax *you* design with HTVM. HTVM allows you to meticulously craft every keyword, operator, and structure to fit *your specific cognitive model*. You build the language; HTVM just makes it work everywhere. AI generates based on patterns; HTVM generates based on *your explicit design*.
*   **Beyond Simple Generation:** HTVM isn't just about generating code. It's an ecosystem with an IDE, syntax highlighting tailored *to your rules*, and built-in features like OSP and Programming Blocks. It provides a complete workbench for *your* language, something far beyond simple AI code generation prompts.

While AI is a powerful tool for *assisting* developers (and future HTVM IDE versions plan to leverage it for tasks like error mapping and more...), it doesn't replace the fundamental value proposition of HTVM: giving the developer **unprecedented, deterministic control** over their language syntax and enabling **reliable, large-scale, multi-target code generation** based on that personalized design. HTVM empowers *your* creativity and ensures *your* logic translates faithfully; it doesn't rely on the probabilistic nature of current AI models for core functionality.


#### **In essence, HTVM's philosophy is about reclaiming control, reducing friction, enhancing accessibility, and making programming a more personalized and efficient act of creation.** It’s about building *your* ideal programming experience.

---

### ⚙️ What Customizations HTVM Offers

[Go Back To The Table of Contents ](#table-of-contents)

### HTVM: Customizable Syntax for Your Needs

HTVM offers **extensive syntax customization**, giving you the freedom to tailor the language structure to your own preferences. Almost all of these customizations can be converted into 15 languages, providing flexibility while keeping things simple.

## Customization Features

### Code Block Delimiters

You can **customize the block delimiters**, which define the start and end of code blocks. You can use:

- Curly braces `{}` (default).
- **Other characters**, words, or even single letters, as long as the opening and closing delimiters are different from each other.

### Indentation Styles

You have the ability to choose between multiple **indentation styles**:

- **Pythonic indentation style**: This removes the need for block delimiters like curly braces, relying on indentation to define code blocks.
- **Lua indentation style**: Uses the customizable `end` keyword to close code blocks.

Both styles are fully customizable, and you can define your own keyword for closing blocks (such as `end`, or any other word).

### Toggleable Semicolons

Semicolons are **toggleable** in HTVM. By default, semicolons are not required to terminate statements, but you can enable the use of semicolons if you prefer them in your syntax. It's completely up to you whether or not to use them in your code.

### Parentheses Customization

For **conditional statements** like `if`, `else if`, and `while` loops, you can choose to **use or omit parentheses** around conditions. This customization allows you to streamline your code and make it more intuitive according to your preferences.

### Customizable Operators

HTVM allows you to **customize operators** to make your code more readable or suit your style. For example, instead of using `==` for equality, you can change it to a keyword like `is`. This means you can write more natural, human-readable code, such as:

- `if var1 is 5` (instead of `if var1 == 5`).

This flexibility extends across various operators, giving you full control over how your conditions and operations are structured.


## More Customization Options in HTVM

HTVM offers even **more customization** for your syntax and style. Here's a breakdown of additional features:

### Type Definition Styles

You can choose between **PostFix** or **Prefix** style for type definitions, similar to TypeScript:

- **PostFix**: Define the variable first, then the type after the colon (`var1: int`).
- **Prefix**: Define the type first, then the variable (`int var1`).

You can toggle between these styles depending on which one fits your preferred syntax better.

### Array Syntax Customization

HTVM lets you customize the array syntax by choosing between two options:

- **Regular braces** (`[]`): The default style for arrays.
- **Curly braces** (`{}`): If you prefer this style, you can toggle it on.

It's fully flexible, so you can use whichever syntax feels right for your code.

### Customizable Operators

HTVM extends **operator customizability** even further, allowing you to adjust a wide range of operators:

- **All operators**: You can customize **all operators**, including logical, comparison, and even **bitwise operators**.
- **Assignment operators**: You can customize assignment operators, such as `=`, to whatever you prefer (e.g., `is`, `set`, or any other single word).

However, remember that you are only allowed to use **one word** for customization—no spaces in operator names.

### Customizable Comments

Comments are also fully customizable:

- **Single-line comments**: Change the single-line comment syntax to whatever you like (e.g., `//`, `#`, or any word).
- **Multi-line comments**: Customize the syntax for multi-line comments, allowing for multiple words or characters if necessary.

### Custom Escape Characters

Escape characters can now be **customized**:

- **Escape character**: You are no longer limited to using just the backslash (`\`). You can choose any single character you want as your escape character—such as the backtick (`` ` ``) or something entirely different.

### Loop Index Customization

You can **change the index for regular loops**. By default, HTVM uses **zero-based indexing** for loops. However, you can change this for certain languages:

- **AutoHotKey and Lua**: By default, both of these languages use **one-based indexing** for arrays and loops.
- **Other languages**: It's important to note that **changing loop indices may cause issues** with some languages, as not all languages support customizable loop indexes. **Use caution** when making changes to this setting, especially when working with languages like Python, JavaScript, or C++.

HTVM allows for this change, but it’s recommended to keep the default zero-based indexing unless you’re specifically creating **meme languages** where the index may be something unconventional (like `-69` or `420`).

### Key Considerations for Indexing

- For **AutoHotKey** and **Lua**, the index starts at **one** by default.
- For **other languages**, **zero-based indexing** is the norm, so be mindful of this when converting to other languages.
  
If you are creating custom languages or experimenting with unconventional indexing, keep these limitations in mind to avoid potential issues when converting to other languages.

---


## Further Customization in HTVM

HTVM offers **even more customization options**, allowing you to tailor the language to your preferences, especially when it comes to types and arrays.

### Custom Type Names

HTVM allows you to **customize type names** to anything you like. For example:

- **Basic Types**: Instead of using the traditional `int`, you can use `number`, `i`, or any other word you prefer. The same goes for types like `double`, `char`, `boolean`, `float`, and more.
- **Integer Sizes**: You can change types like `int16` to `i16` or any naming convention you prefer.
  
**Important:** While you can use **multiple words** for type names, be cautious about potential conflicts in the parser. For instance, using common words that might be parsed as something else could lead to issues. Always ensure that the type names are unique and won't interfere with other syntax elements.

The available types you can customize include:

- **Void**: You can rename `void` to whatever you want.
- **Integers**: `int`, `int8`, `int16`, `int32`, `int64`, etc.
- **Unsigned Integers**: `uint8`, `uint16`, `uint32`, `uint64` (Note: be cautious when converting unsigned integers to Java, as Java doesn’t support them).
- **Floating Point**: `double`, `float`.
- **Character**: `char`.
- **String**: `string`.
- **Boolean**: `boolean`.

---

### Array Types Customization

In HTVM, you can customize the **array types** as well:

- **Four main array types**:
  - `arr str`: For arrays of strings.
  - `arr int`: For arrays of integers.
  - `arr float`: For arrays of floating-point numbers.
  - `arr bool`: For arrays of booleans.
  
- **Dynamic Arrays**: For dynamic-type languages, you can use the generic `array` keyword, but it defaults to a string array when converted to static type languages. This provides a flexible way to define arrays in your code.
  
**Note on Static vs. Dynamic Types**: In **static-type languages**, arrays are strictly defined, so if you use the `array` keyword, it will default to a **string array**. For **dynamic languages**, the array type is more flexible.

---

### Array Methods Customization

HTVM allows you to customize array methods with ease. These methods work by appending a dot (`.`) after the array, followed by the method name:

- **append**: Adds an element to the end of the array.
- **pop**: Removes the last element from the array.
- **size**: Retrieves the size (length) of the array.
- **insert**: Inserts an element at a specific index (not by value).
- **remove**: Removes an element at a specific index (not by value).
- **indexOf**: Finds the index of a value in the array.

These methods can be customized with different names or functionality if needed, making it easier to manipulate arrays according to your needs.

---

### Important Considerations

- **Java and Unsigned Integers**: Be careful when converting unsigned integers (`uint8`, `uint16`, etc.) to **Java**, as Java does not support unsigned integers. HTVM will **NOT** warn you when attempting this conversion.
- **Array Methods**: Ensure that you define methods like `insert` and `remove` clearly to avoid confusion with other types of array manipulations. Using the dot (`.`) ensures consistency and clarity in how methods are applied to arrays.

---

## Extensive Customization in HTVM

HTVM offers **wide-ranging customization options** to ensure the language suits your preferences, especially when it comes to keywords and functionality. You can customize several aspects of the language, ranging from basic variable declarations to control structures and even language-specific keywords.

### Customizing Keywords

HTVM allows you to customize many fundamental keywords that are used across different programming languages:

- **Variable Declarations**: Customize `var`, `let`, and `const` keywords. These are primarily used in **JavaScript** and **TypeScript**. 
  - The `const` keyword is supported in most languages, but in languages that don't have constants (e.g., **Python**, **AutoHotKey**, **Lua** and some more), it will be ignored, and the variable will be created as usual.
  
- **Boolean Keywords**: Change the `true` and `false` keywords to something else like `yeah` and `nah`. This customization provides flexibility in how logical values are represented.
  
- **Null Keyword**: You can also customize the `null` keyword, though be cautious—some languages do not support `null` in the same way (e.g., **Python**, **C++**, **AutoHotKey** and some more). For languages that don't support `null`, the value will simply be ignored or treated as an empty value.
  
- **End Keyword**: You can change the `end` keyword to something else. This is typically used for denoting the end of code blocks in various languages and is customizable in HTVM.

- **Global Keyword**: 
  - The `global` keyword works only in **Python** and **AutoHotKey**. It allows passing a global variable into a function and modifying it. In other languages, the `global` keyword will be ignored, but the variable will still be created.
  - You can also customize the `global` keyword to something else, keeping the functionality intact within supported languages.

---

### Main Label and Main Function Customization

HTVM allows you to **customize the main function label**. The main label refers to the starting point of your program, especially for languages like **C++** and many more but in **JavaScript** and **TypeScript** it's a bit different:

- **Main Label**: 
  - This is a customizable label where your main function is typically located. You can define a single word or even multiple words as the main label. The parser will ensure that the code below the label is treated as the main function's content. 
  - The main label is optional, and it’s simply a label—there’s no need to wrap the code in a block unless the language requires it (e.g., **Python** doesn’t need a `main` function, so the code will be placed directly beneath it).
  
- **Main Function**:
  - In **JavaScript** and **TypeScript**, you can toggle between an **async main function** and a regular one.
  - The language will default to creating asynchronous functions for all function definitions, but you can customize this behavior with the **async** keyword (which is also customizable to other terms if you prefer). Also, if you don’t use the main label keyword, the HTVM parser will assume that you haven't created any functions, and all the code will be placed in the main function if the target language has a main function.

---

### Function Customization

HTVM allows you to **customize various function-related keywords** to suit your needs:

- **Async Functions**: 
  - By default, all functions in HTVM are asynchronous. You can toggle this behavior or use the **asynchronous** keyword, which is customizable.
  - The **await** keyword can also be modified to something else (e.g., `wait`) to fit your naming preferences.
  
- **Loop Customization**: 
  - The loop syntax can be customized with terms like `A_Index` and `A_LoopField` to resemble **AutoHotKey**-style loops. These keywords provide a cleaner, more intuitive loop structure for those familiar with AutoHotKey.

---

### Important Considerations

- **Customizing Keywords**: When you customize keywords (e.g., `const`, `true`, `false`, `null`), ensure that they don’t conflict with existing language constructs. The parser will handle many of these customizations, but be aware of limitations in certain languages.
  
- **Global Variables**: The `global` keyword is supported in **Python** and **AutoHotKey**, but it will be ignored in other languages like **JavaScript** or **C++**. Ensure you understand how this will behave across different languages.

- **Async Functions in JavaScript/TypeScript**: This is especially useful for **JavaScript** and **TypeScript** but can be customized to suit your project’s needs.

---

HTVM provides a **high level of flexibility** for customizing how the language operates, allowing you to adapt it to the specific needs of your project. Whether you're working with variable declarations, loop structures, or customizing language-specific keywords, HTVM makes it easier to code in a way that feels natural to you.

---

## Advanced Customizations in HTVM

HTVM offers **advanced customizations** that allow you to control everything from ternary operators to error handling and even modularity with `include`. This flexibility makes it possible to tailor the language to your coding style and needs.

### Ternary Operator Customization

HTVM lets you customize the **ternary operator**:

- By default, HTVM uses the regular **C-style ternary operator** (`condition ? true : false`). This works in most languages, but certain languages (like **Go**) do not support this syntax.
- For languages that use a different syntax for ternary operators, HTVM will handle the conversion automatically, converting it to the appropriate format.
  - For example, **Python** uses the `condition if true else false` syntax.
  - HTVM will ensure that the ternary operator is properly converted, but if the target language does not support ternary operators, HTVM will generate a message and prevent execution in languages like **Go** where it won’t run. This ensures that you avoid runtime errors from unsupported syntax.

### Error Handling Customization

HTVM allows you to **customize error handling** as well:

- The `try`, `catch`, `finally`, and `throw` keywords are customizable, enabling you to tailor them to your preference.
- When using **throw**, you can customize the function name for the error message. This is how it works:
  - Type `throw`, followed by the function name (which is customizable), open parentheses, and inside the parentheses, you can pass a string that represents the error message.
  - Example:
    ```htvm
    throw customErrorFunction("Something went wrong!")
    ```
- **Conversion to Other Languages**:
  - HTVM converts error handling to most languages, but **Lua** and **Go** are exceptions. In those languages, the error handling structure is not supported, and HTVM will generate a string that alerts you about the lack of support.
  - HTVM does not provide error handling within itself. Instead, it relies on the target language to handle errors since HTVM assumes your code is flawless, and any issues should be identified by the language you're transpiling to.

### Include Keyword Customization

HTVM also supports **modularity** through the `include` keyword:

- The `include` keyword allows you to include other HTVM files at the top of your code.
- This is useful for organizing your code across multiple files or for reusing common functionality across different projects.
  - Example:
    ```htvm
    include "utility_functions.htvm"
    ```
- The `include` keyword is fully customizable, so you can change it to something else if preferred.

---

### Key Takeaways:

- **Ternary Operator**: Customizable to fit different syntaxes across languages, with automatic conversion. However, unsupported languages like **Go** and **Lua** will display a message instead of running.
  
- **Error Handling**: Customizable for the `try`, `catch`, `finally`, and `throw` keywords, and the function name for error messages can also be customized. HTVM does not handle errors itself but relies on the target language’s error handling.

- **Include**: Supports modularity by including external HTVM files, and the keyword itself is customizable.

These advanced customizations further enhance HTVM's flexibility, allowing you to adjust error handling, ternary operators, and file management to fit your needs. With these tools, HTVM can be tailored to suit your specific coding style and make your development process more efficient.

---

## Programming Blocks in HTVM

HTVM introduces **programming blocks** that allow you to **mix languages** seamlessly in your code. This feature is designed to handle cases where HTVM itself can't achieve something directly or when you'd prefer to rely on another language for specific tasks.

### How Programming Blocks Work

1. **Opening a Programming Block**: You can open a programming block for a specific target language with the following syntax:
    - One line to open the programming block.
    - Inside the block, you can write in the target language.
    - You close the block on a new line after your code.

    Example:
    ```htvm
    ; This is a JavaScript programming block. It will stay intact and included in the JS output.
    ___js start
    // The syntax highlighting will change to JavaScript here since this is now JavaScript code only.
    console.log("==========================")
    ___js end
    ```

2. **Incorporating Blocks into HTVM Code**:
    - When you write in HTVM, you can seamlessly insert target-language code using programming blocks.
    - For example, if you're converting to **JavaScript**, you can open a **JavaScript programming block**, and the code inside will be converted directly to JavaScript and placed in the converted code without alteration.
    - If the HTVM code contains loops or other structures, the programming block code stays intact in the appropriate place during conversion.

3. **Multiple Programming Blocks**: You can use **multiple programming blocks** for different target languages, but they will be context-sensitive:
    - **For JavaScript**: The **Python programming block** will be ignored during conversion.
    - **For Python**: The **JavaScript programming block** will be ignored.
    - In other words, only the relevant programming block for the target language will be included in the final code.

    Example:
    - **JavaScript block** in HTVM:
    ```htvm
    # Open JavaScript block
    console.log("Hello, world!");
    # End JavaScript block
    ```
    - **Python block** in HTVM:
    ```htvm
    # Open Python block
    print("Hello, world!")
    # End Python block
    ```
    When converting to **JavaScript**, the Python block will disappear, and only the JavaScript block will be included.

4. **Reverse Programming Blocks**:
    - You can also open an **HTVM programming block** within other target language code (e.g., C++). The block will then be converted into HTVM-compatible code.
    - For example, if you're writing in C++ and need to use HTVM-specific functionality, you can insert an HTVM block, and it will be transpiled into C++ when you convert the code.
    - The process works by specifying the **target file** (e.g., `main.cpp`), and the HTVM block inside it will be converted based on the file's extension.

5. **Universal Programming Block**:
    - If two languages share the same syntax for a particular construct, HTVM allows you to use a **universal programming block**. This block can handle situations where HTVM cannot achieve the desired behavior but the syntax matches in multiple languages.
    - This is useful when the target languages have compatible syntax for specific code constructs but HTVM doesn't support them directly.

6. **Conversion and Functionality**:
    - During conversion, HTVM ensures that only the relevant programming block is preserved based on the target language. Unused blocks are omitted.
    - When converting code, HTVM will automatically include any necessary built-in functions or libraries for the target language, displaying them in the console.


### Key Advantages of Programming Blocks:

- **Flexibility**: Allows mixing HTVM with other languages for complex or specialized tasks.
- **Modularity**: Enables using language-specific libraries or features when HTVM cannot do the job.
- **Customizability**: Supports a wide range of languages, with options to adjust and adapt as needed.
- **Seamless Conversion**: Code stays in place, and HTVM ensures proper language-specific syntax is followed.

---

### Key Takeaways:
- **Programming blocks** allow writing code in another language directly within HTVM, which will be preserved during conversion to that language.
- Multiple programming blocks can be used, but only the relevant block will be included based on the target language.
- **Reverse programming blocks** allow you to insert HTVM code into other target language code.
- The **universal programming block** enables handling languages with similar syntax for specific constructs.


#### **And More...**  
- Go to [HTVM's website](https://themaster1127.github.io/HTVM) to explore all the syntax customizability and create your own language.

### **The Power of HTVM – Beyond Anything Else**  
This isn’t just some hobby project. **HTVM Version 2 took many months just for the parser.** And that was with prior experience from HTVM Version 1 and all the work put into previous languages like HT++, HTH, and HTpy. Every single language had to be carefully mapped out—loops, if-statements, try/catch blocks, functions, variables, types—**every detail had to be considered, tested, and tweaked.**  

And here’s the thing: **HTVM doesn’t just output to one language at a time—it can compile to multiple languages simultaneously.** That means you can write a single HTVM file and have it generate both JavaScript and Python code at the same time. That alone is something **almost no other tool in the world can do.**  

---

### **Programming Blocks – Total Control Over Your Code**  
And then we have **Programming Blocks.** These allow you to **write native code for the target language directly inside HTVM files**. So if you’re converting to JavaScript and need something that HTVM doesn’t handle natively, you can just open a **JavaScript Programming Block**, write JavaScript inside it, and it will only be included when compiling to JavaScript.  

But it gets even crazier—**you can have multiple programming blocks for different languages in the same file.** That means you can mix HTVM, JavaScript, Python, and C++ **all in one place** and still have everything work correctly.  

And if that wasn’t enough, there are **Reverse Programming Blocks**—which allow for even more insane levels of customization. Even if nobody uses them, **HTVM is so complete that the feature is still there.**  

---

### **The Future of Programming**  
HTVM **isn’t just a transpiler—it’s the future of programming.**  

This is a system that allows **anyone** to create their own syntax, define how they want their language to behave, and then generate fully functional code in fifteen different programming languages. No more being stuck with a single syntax or workflow—**HTVM lets you build programming your way.**  

Think about it. If you had to manually convert HTVM to fifteen different languages, it would take months just for a single feature. But **HTVM automates that entire process**—**once your syntax is defined, your language works across all targets instantly.**  

### **HTVM – The Future of Programming**  
This level of customization **doesn’t exist anywhere else.** No other system gives you this much control over how your language looks and feels. You’re not just writing code—you’re **designing your own programming experience.**  

HTVM isn’t just powerful—it’s **insane.** This is how programming should be.

**HTVM doesn’t force you into a fixed way of coding—it lets you create your own language and then outputs it into real programming languages.**  

---

HTVM **isn’t just another programming tool. It’s a revolution.**

