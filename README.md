# HTVM

## HTVM: The Adaptive, Multi-Language, Customizable Syntax and Code Generation Engine

HTVM is a powerful engine that converts code to 15 languages, including C++, Python, JavaScript, and more (see langs.txt for the full list). It offers extreme customizability in syntax and code generation, along with a built-in IDE.

!!! HTVM IS STILL IN DEVELOPMENT !!!

**What is HTVM?**  
HTVM is an Adaptive, Multi-Language, Customizable Syntax and Code Generation Engine. It allows users to create their own programming languages. It’s not just about programming in a new language, but about designing your own syntax. This means that whether you're a professional programmer or even someone with basic computer skills, you can tailor the way you write code to fit your preferences. It’s like giving everyone the power to define the grammar rules for their code without having to be stuck with traditional programming language limitations.


**Why is HTVM useful?**  
HTVM solves several real-life problems by allowing a level of **flexibility** and **personalization** that traditional programming languages don't offer. You can create a language that fits the problem at hand, the way your mind works, or how you like to communicate logic. This is especially powerful because **current programming languages** are often rigid, requiring you to work within set syntaxes and paradigms, which can be a barrier for many people or even slow down the development process for complex projects.

1. **Accessibility for non-programmers**: If someone with no programming experience wants to build a tool that helps them in their work (for example, automating some office tasks), they can create their own language that fits their needs, even if they don’t know how to code. With HTVM, they can use simple tools like toggling switches and text boxes to make a language that’s intuitive to them.

2. **Reducing friction**: Developers often spend a lot of time learning and adapting to new languages. HTVM lets them **choose the syntax** that makes the most sense for their project, which can dramatically cut down the learning curve and make code easier to read and write.

3. **Problem-specific syntax**: If you’re working on a very specific domain (like AI, game development, or scientific calculations), you can design a language that's optimized for that specific problem. You don’t have to force a general-purpose language to fit your needs.

**What real-life problems does HTVM solve?**  
1. **Inaccessible programming for beginners**: Many people who could benefit from automation or custom tools avoid programming because of the steep learning curve. With HTVM, those people can design a language that speaks to them in terms they understand. It's more intuitive and less intimidating than traditional programming languages.

2. **Bureaucratic or business process automation**: Businesses often deal with repetitive tasks that can be automated but might not have the coding resources or skills to do so. A business analyst or manager could use HTVM to create a custom scripting language that automates workflows based on their specific needs, without needing to be a software developer.

3. **Customization of development environments**: Developers and teams can create tailored coding experiences, optimizing their IDE for the kinds of projects they work on. This reduces confusion and helps increase productivity.

**Real-world use cases?**  
- **Personalized automation**: A person could design a language to automate their daily tasks, like managing emails or organizing files, using a syntax they’re comfortable with.  
- **Domain-specific languages**: A scientist might want to automate certain kinds of data analysis but prefers to do so using syntax that closely matches their mathematical work. HTVM would allow them to create that custom language.  
- **Educational purposes**: HTVM could be used in classrooms or workshops to teach programming by allowing students to experiment with different syntaxes, making learning more hands-on and intuitive.

Alright, let's make this crystal clear.  

### **What HTVM Is NOT**  
HTVM is **not** a general-purpose transpiler that lets you convert between existing languages. You **cannot** use HTVM to convert Python to JavaScript, JavaScript to C++, or any other combination like that. If you have a Python script and want to turn it into JavaScript, **HTVM is not what you're looking for.**  

Similarly, you **cannot** take existing code from languages like Python, Java, or C# and convert it to HTVM. That’s simply not how HTVM works. **HTVM is its own thing**—it’s a language that has its own syntax, which can be customized to your liking, and that syntax is what gets converted into other languages.  

However, what **is** possible is converting **HTVM to HTVM**—meaning, you can have different custom syntaxes within HTVM and convert between them. That’s something no other system really does. But again, **HTVM does not translate between standard programming languages—it only translates its own customizable syntax to these languages.**  

---

### **What HTVM Actually Is**  
HTVM is **a revolutionary, next-level programming system** that lets you define your own syntax and then convert that syntax into **fifteen different programming languages**:  

**C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript, and Groovy.**  

It’s not just a transpiler—it’s an entire **ecosystem** that allows you to **create your own language, structure it however you want, and then generate real-world code in multiple target languages.**  

But here’s where it gets insane: **HTVM is not locked into any one syntax.** You can **completely customize** how your code looks. 

### **Total Syntax Customization – The Ultimate Flexibility**  

HTVM **isn’t just about converting your custom language to multiple targets—it’s about letting you build your language exactly the way you want.** And when I say customizable, I mean **everything** is customizable:  

# HTVM: Customizable Syntax for Your Needs

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

- **Async Functions in JavaScript/TypeScript**: By default, functions are asynchronous. This is especially useful for **JavaScript** and **TypeScript** but can be customized to suit your project’s needs.

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
- Go to [HTVM's website](https://themaster1127.github.io/HTVM) (**STILL IN DEVELOPMENT—don’t go there yet, come back another day!** But you can still check the progress of the website.) to explore all the syntax customizability and create your own language.  
- Visit [The HTVM Web IDE](https://themaster1127.github.io/HTVM/src-website/online-ide.html?id=1) (**STILL IN DEVELOPMENT—don’t go there yet, come back another day!** But you can still check the progress.) First, go to the main website, then you can get redirected to the IDE to use it with your own language. HTVM can also be run **locally** by first compiling `HTVM.cpp`, and you can use the **HTVM IDE** as well. (**Docs are coming soon!**)  

### **The Power of HTVM – Beyond Anything Else**  
This isn’t just some hobby project. **HTVM Version 2 took over three months just for the parser.** And that was with prior experience from HTVM Version 1 and all the work put into previous languages like HT++, HTH, and HTpy. Every single language had to be carefully mapped out—loops, if-statements, try/catch blocks, functions, variables, types—**every detail had to be considered, tested, and tweaked.**  

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



---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---

# HTVM  

### HTVM: The Revolution in Programming  

## HTVM: The Adaptive, Multi-Language, Customizable Syntax and Code Generation Engine

HTVM is a powerful engine that converts code to 15 languages, including C++, Python, JavaScript, and more (see langs.txt for the full list). It offers extreme customizability in syntax and code generation, along with a built-in IDE. And introducing groundbreaking features:  
- **Customizable Syntax**: Define your own syntax without restrictions.  
- **No More Build-In Libraries**: Forget importing libraries—everything you need is built-in for simplicity and efficiency.  
- **HTVM IDE**: To enhance your development experience, HTVM comes with a dedicated IDE.

HTVM makes programming simpler, more flexible, and revolutionary.  

---

!!! HTVM IS STILL IN DEVELOPMENT !!!

**What is HTVM?**  
HTVM is an Adaptive, Multi-Language, Customizable Syntax and Code Generation Engine. It allows users to create their own programming languages. It’s not just about programming in a new language, but about designing your own syntax. This means that whether you're a professional programmer or even someone with basic computer skills, you can tailor the way you write code to fit your preferences. It’s like giving everyone the power to define the grammar rules for their code without having to be stuck with traditional programming language limitations.

BTW, HTVM is bootstrapped to `C++` so it can run locally and to `JavaScript` so it can work in the browser.

Alright, let's make this crystal clear.  

### **What HTVM Is NOT**  
HTVM is **not** a general-purpose transpiler that lets you convert between existing languages. You **cannot** use HTVM to convert Python to JavaScript, JavaScript to C++, or any other combination like that. If you have a Python script and want to turn it into JavaScript, **HTVM is not what you're looking for.**  

Similarly, you **cannot** take existing code from languages like Python, Java, or C# and convert it to HTVM. That’s simply not how HTVM works. **HTVM is its own thing**—it’s a language that has its own syntax, which can be customized to your liking, and that syntax is what gets converted into other languages.  

However, what **is** possible is converting **HTVM to HTVM**—meaning, you can have different custom syntaxes within HTVM and convert between them. That’s something no other system really does. But again, **HTVM does not translate between standard programming languages—it only translates its own customizable syntax to these languages.**  

---

### **What HTVM Actually Is**  
HTVM is **a revolutionary, next-level programming system** that lets you define your own syntax and then convert that syntax into **fifteen different programming languages**:  

**C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript, and Groovy.**  

It’s not just a transpiler—it’s an entire **ecosystem** that allows you to **create your own language, structure it however you want, and then generate real-world code in multiple target languages.**  

But here’s where it gets insane: **HTVM is not locked into any one syntax.** You can **completely customize** how your code looks. 

### **Total Syntax Customization – The Ultimate Flexibility**  

HTVM **isn’t just about converting your custom language to multiple targets—it’s about letting you build your language exactly the way you want.** And when I say customizable, I mean **everything** is customizable:  

---

### 🌐 OSP: Objectively Simplified Programming Paradigm  
HTVM introduces the **Objectively Simplified Programming (OSP)** paradigm, which eliminates the complexities of traditional object-oriented programming while still supporting objects.  
- OSP focuses on intuitive and powerful object usage.  
- For more details, check out the **[OSP Documentation](https://github.com/TheMaster1127/HTVM/blob/main/DOCUMENTATION.md#osp-objectively-simplified-programming-paradigm)**.
- Or, build your own HTVM language, and the documentation for it will be generated once you create it here on the [HTVM Syntax Configurator Website](https://themaster1127.github.io/HTVM/). Then, you can read about OSP.

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

### Table of Contents

1. [📘 Usage](#-usage)  
   **Description**: Learn how to compile and execute your language code using HTVM and the HTVM IDE.

2. [📂 Adding Built-In Functions](#-adding-built-in-functions)  
   **Description**: Add custom built-in functions to your language by following simple syntax rules.

3. [📜 Documentation Regeneration](#-documentation-regeneration)  
   **Description**: Update your language’s documentation whenever new features or changes are made.

4. [🛠️ HTVM IDE](#%EF%B8%8F-htvm-ide)  
   **Description**: Set up and use the HTVM IDE for coding, testing, and compiling your language.
     
5. [💡 Usecases For HTVM](#usecases-for-htvm)  
   **Description**: Explore the various scenarios and contexts in which HTVM can be used to revolutionize programming workflows and enhance productivity.
   
6. [⚙️ What Customizations HTVM Offers](#what-customizations-htvm-offers)  
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
HTVM <yourCodeFileName.yourExtension> <HTVM-instructions.txt> [optional LangToTranspileTo]
```  

#### Options  
- **Required Parameters**:  
  - `yourCodeFileName.yourExtension`: The source code file.  
  - `HTVM-instructions.txt`: Instructions file for transpilation.  
- **Optional**:  
  - Specify the target language (`cpp`, `py`, `js`, `go`, `lua`, `cs`, `java`, `kt`, `rb`, `nim`, `ahk`, `swift`, `dart`, `ts`, `groovy`, `htvm` or <yourExtension>) directly in the command.  

**Example**:  
```bash
HTVM main.htvm HTVM-instructions.txt cpp
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

description: string~~~StrTitleCase is a func balalbla bla bal~~~here is how the func looks like:~~~```~~~StrTitleCase(string, [optanalName], string, [optanal], string, [optanal], [optanal])~~~```~~~

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

### 💡 Usecases For HTVM

**Why is HTVM useful?**  
HTVM solves several real-life problems by allowing a level of **flexibility** and **personalization** that traditional programming languages don't offer. You can create a language that fits the problem at hand, the way your mind works, or how you like to communicate logic. This is especially powerful because **current programming languages** are often rigid, requiring you to work within set syntaxes and paradigms, which can be a barrier for many people or even slow down the development process for complex projects.

1. **Accessibility for non-programmers**: If someone with no programming experience wants to build a tool that helps them in their work (for example, automating some office tasks), they can create their own language that fits their needs, even if they don’t know how to code. With HTVM, they can use simple tools like toggling switches and text boxes to make a language that’s intuitive to them.

2. **Reducing friction**: Developers often spend a lot of time learning and adapting to new languages. HTVM lets them **choose the syntax** that makes the most sense for their project, which can dramatically cut down the learning curve and make code easier to read and write.

3. **Problem-specific syntax**: If you’re working on a very specific domain (like AI, game development, or scientific calculations), you can design a language that's optimized for that specific problem. You don’t have to force a general-purpose language to fit your needs.

**What real-life problems does HTVM solve?**  
1. **Inaccessible programming for beginners**: Many people who could benefit from automation or custom tools avoid programming because of the steep learning curve. With HTVM, those people can design a language that speaks to them in terms they understand. It's more intuitive and less intimidating than traditional programming languages.

2. **Bureaucratic or business process automation**: Businesses often deal with repetitive tasks that can be automated but might not have the coding resources or skills to do so. A business analyst or manager could use HTVM to create a custom scripting language that automates workflows based on their specific needs, without needing to be a software developer.

3. **Customization of development environments**: Developers and teams can create tailored coding experiences, optimizing their IDE for the kinds of projects they work on. This reduces confusion and helps increase productivity.

**Real-world use cases?**  
- **Personalized automation**: A person could design a language to automate their daily tasks, like managing emails or organizing files, using a syntax they’re comfortable with.  
- **Domain-specific languages**: A scientist might want to automate certain kinds of data analysis but prefers to do so using syntax that closely matches their mathematical work. HTVM would allow them to create that custom language.  
- **Educational purposes**: HTVM could be used in classrooms or workshops to teach programming by allowing students to experiment with different syntaxes, making learning more hands-on and intuitive.

---

### ⚙️ What Customizations HTVM Offers


# HTVM: Customizable Syntax for Your Needs

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

- **Async Functions in JavaScript/TypeScript**: By default, functions are asynchronous. This is especially useful for **JavaScript** and **TypeScript** but can be customized to suit your project’s needs.

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
This isn’t just some hobby project. **HTVM Version 2 took over three months just for the parser.** And that was with prior experience from HTVM Version 1 and all the work put into previous languages like HT++, HTH, and HTpy. Every single language had to be carefully mapped out—loops, if-statements, try/catch blocks, functions, variables, types—**every detail had to be considered, tested, and tweaked.**  

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

