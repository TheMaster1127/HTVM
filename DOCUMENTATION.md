# HTVM Documentation

1. [Introduction](#introduction-to-htvm) 
Understand why HTVM is the future of programming.  

2. [OSP (Objectively Simplified Programming) Paradigm](#osp-objectively-simplified-programming-paradigm)  
Learn about the new paradigm that replaces traditional object-oriented programming.  

3. [Built-in Functions](#built-in-functions)  
Explore the wide range of built-in functions categorized for ease of use.  

---

## Introduction to HTVM

[Go back](#htvm-documentation) 

HTVM is a revolutionary tool designed to replace traditional programming. With HTVM, you can create your own programming language directly [here](https://themaster1127.github.io/HTVM/).

What makes HTVM powerful:  
- **Syntax Customization**:  
  Here’s what you can change:  
  - **Keywords**: Modify the keywords used for `if` statements, `while` loops, `for` loops, and more.  
  - **Operators**: Change the operators like `==`, `!=`, and others to suit your needs.  

- **Inspiration from AutoHotKey**:  
  Features like `Loop` and `Loop, Parse` (just like in AutoHotKey) are supported and customizable.  

- **Cross-Language Compatibility**:  
  Languages created with HTVM can be transpiled into **C++**, **Python**, and **JavaScript**.  

- **Static Typing**:  
  Types are required when converting to C++, but are optional for Python and JavaScript.  

- **Built-in Functions**:  
  Instead of libraries, HTVM offers built-in functions organized into categories. Scroll to the [Built-in Functions](#built-in-functions) section for more details.  

## Core Features

### Language Configuration
- **Target Language Selection**
  - Choose between **C++**, **Python** and **JavaScript** 
  - Specify file extensions for output files
  - Configure HTML wrapping for JavaScript output

### Syntax Customization
- **Code Block Style**
  - Toggle between curly braces `{}` or `end` keywords
  - Enable/disable Python-style colon syntax
  - Customize parentheses usage
  - Control semicolon placement

- **Function Definitions**
  - Toggle function keywords
  - Customize async main function for JavaScript
  - Configure global variable handling

### Type System
- **Basic Types**
  - Integer (INT)
  - String (STR)
  - Boolean (BOOL)
  - Float (FLOAT)

- **Extended Integer Types**
  - INT8
  - INT16
  - INT32
  - INT64

### Control Structures
- **Conditional Statements**
  - If/Else/ElseIf
  - Switch/Case/Default
  - Custom keywords for all conditional operators

- **Loops**
  - While loops
  - For loops with customizable syntax
  - Infinite loops
  - Parse loops (AutoHotkey-style)
  - Custom indexing (0-based or 1-based)
  - Loop control (break, continue)

### Arrays and Collections
- **Array Types**
  - Integer arrays
  - String arrays
  - Float arrays
  - Boolean arrays

- **Array Operations**
  - Append
  - Pop
  - Insert
  - Remove
  - Size
  - IndexOf

### Error Handling
- **Exception Management**
  - Try blocks
  - Catch blocks
  - Finally blocks
  - Custom error messages
  - Throw statements

### JavaScript-Specific Features
- **Variable Declaration**
  - var, let, const keywords
  - Automatic var declaration option
  - await keyword support

### Operators
- **Assignment Operators**
  - Basic assignment
  - Addition assignment
  - Subtraction assignment
  - Multiplication assignment
  - Division assignment
  - Concatenation assignment

- **Comparison Operators**
  - Equal to
  - Not equal to
  - Greater than
  - Less than
  - Greater than or equal to
  - Less than or equal to

- **Logical Operators**
  - AND
  - OR
  - NOT

### Comments
- Single-line comments
- Multi-line comments
- Custom comment symbols

### AutoHotkey-Inspired Features
- **Loop Variables**
  - A_Index (customizable)
  - A_LoopField (customizable)
- **Loop Types**
  - Parse loops
  - Count loops
  - Infinite loops

## Configuration Options

### Syntax Style
- `useFuncKeyWord`: Toggle function definition keywords
- `useCurlyBraces`: Toggle curly brace block definitions
- `useEnd`: Toggle 'end' keyword for block closure
- `useSemicolon`: Toggle statement-ending semicolons
- `useParentheses`: Configure parentheses requirements
- `usePythonicColonSyntax`: Enable Python-style block definitions

### JavaScript Configuration
- `useInJavaScriptAlwaysUseVar`: Force 'var' declarations
- `useJavaScriptInAfullHTMLfile`: Enable HTML wrapping
- `useJavaScriptAmainFuncDef`: Configure async main function

### Loop Configuration
- `AHKlikeLoopsIndexedAt`: Set loop index starting value
- `forLoopLang`: Select loop syntax style
- `keyWordAIndex`: Customize loop index variable name
- `keyWordALoopField`: Customize loop field variable name


HTVM empowers developers to create programming languages tailored to their needs while maintaining compatibility with modern technologies.  

---

## OSP (Objectively Simplified Programming) Paradigm  

[Go back](#htvm-documentation) 

OSP (Objectively Simplified Programming) is a paradigm designed to replace OOP since OOP was a mistake. To learn OSP you need to first forget everything about OOP. Forget about concepts like inheritance, polymorphism, encapsulation, private/public keywords and instances.

OSP eliminates the complexities of object-oriented programming.  

Here’s how OSP works:  
- **Hierarchies**:  
  - **Alliance**: The top-level structure, defined using the `alliance` keyword. 
  - **Crew**: Sub-levels within an alliance, defined using the `crew` keyword.  
  - **Method**: Functions defined within alliances or crews using the `method` keyword.  
  - **Object**: Objects are defined using the `def obj` keyword.  

- **Properties**:  
  - Defined within objects using the `porp` keyword. You must specify the type, even when converting to Python or JavaScript, for readability.  


### **The `this` Keyword**:

- **Definition**:  
  The `this` keyword is a reference to the current object that invoked a method. In OSP, `this` is **explicitly required to refer to objects**, and **you must always specify the full path** of objects and their properties when using it. Additionally, `this` is **only valid within methods**, as it represents the object calling that specific method.

---

### **Key Rules**:
1. **Full Path Requirement**:  
   - In OSP, **you must always specify the full path** of objects and properties when using `this`.  
   - For example:  
     - **Correct**: `Movable.Vehicles.Car.fuel`  
     - **Incorrect**: `fuel`

2. **Only Inside Methods**:  
   - The `this` keyword can **only** be used inside a method. It refers to the object that invoked the method and provides context for operations on that object.  
   - Using `this` outside of a method will result in an error, as there is no calling object to reference.

---

### **Explanation Using the Example**:
```htvm
method void move(this) {
    if (this == "Movable.Vehicles.Car") {
        if (Movable.Vehicles.Car.fuel > 0) {
            print("The car is driving.")
            Movable.Vehicles.Car.fuel = Movable.Vehicles.Car.fuel - 10
        } else {
            print("The car is out of fuel.")
            Movable.Vehicles.Car.hasFUEL = false
        }
    }
    else if (this == "Movable.Vehicles.Bike") {
        if (Movable.Vehicles.Bike.energy > 0) {
            print("The bike is pedaling.")
            Movable.Vehicles.Bike.energy = Movable.Vehicles.Bike.energy - 5
        } else {
            print("The bike is out of energy.")
            Movable.Vehicles.Bike.hasENERGY = false
        }
    }
}
```
- The `this` keyword in this method represents the specific object calling `move()`.  
  For instance:
  - If `this == "Movable.Vehicles.Car"`, the method knows the caller is the **Car object**, and it manipulates `Movable.Vehicles.Car` properties.
  - Similarly, if `this == "Movable.Vehicles.Bike"`, the method operates on the **Bike object**.

- If you try to use `this` **outside of any method**, it won’t work because `this` has no object context to refer to.  
  For example:
  ``` htvm
  def obj Car {
      prop int fuel = 100
      print(this)  // This will cause an error!
  }
  ```

---

### **Why This Restriction Exists**:
1. **Object Context**:  
   - The `this` keyword needs a calling object to provide context. Without a method invocation, there’s no object to reference.

2. **Scope Control**:  
   - Limiting `this` to methods ensures clear and explicit usage, making code easier to understand and debug.

3. **Example: Calling a Method with an Object**:  
   - To use the `this` keyword, you must **pass an object** when invoking the method:  
   ```htvm
   allianceName.crewName.move(allianceName.crewName.objName)
   ```
   - Here:
     - `allianceName` is the main alliance.
     - `crewName` is the crew containing the method `move`.
     - `objName` is the specific object being passed to the method. This allows `this` to refer to `objName` inside the method.

---

## **You Don’t Need an Alliance or Crew to Define Objects**
- In OSP, you can define objects (`def obj`) directly without placing them inside an **alliance** or a **crew**.  
- This makes it flexible to create standalone objects when you don’t need a larger structure.  

### **Example: Standalone Object Definition**
```htvm
def obj Standalone {
    prop int value = 10
    prop str name = "Independent"
}
```

to access later just use:

```htvm
Standalone.value
Standalone.name
```

---

### **Methods in Alliances**
- Methods can also be defined directly in an **alliance**, without being part of a **crew** and the opposite is well.

### **Example: Method in an Alliance**
```htvm
alliance ExampleAlliance {
    method void greet() {
        print("Hello from ExampleAlliance!")
    }
}
```

to call greet just do:

```htvm
ExampleAlliance.greet()
```

## Global Accessibility:  
  - There are no scopes in OSP. As long as a variable or structure is defined above, it is accessible below. Everything is global, and the full path must always be used.  

## Arrays:  
  - When using arrays you need to create a temporary array and then copy it to another like this:

```htvm
def obj name {
    arr str temp
    prop arr str prop1 = temp
    prop arr str prop2 = temp
    prop arr str prop3 = temp
    prop arr str prop4 = temp
}
```

### **Summary**:
- **Full Paths Always**: Explicit references, such as `Movable.Vehicles.Car.fuel`, are mandatory in OSP. Always use the full path to reference objects. This avoids ambiguity and ensures that each object is uniquely identified within the code.
- **Only Inside Methods**: The `this` keyword can only be used inside a method to refer to the calling object. It is not valid outside of a method because it requires the context of the method invocation to work correctly.
- **Promotes Clarity**: These rules ensure consistency, clarity, and unambiguous functionality in OSP. By restricting the use of `this` to methods and requiring full paths, the code remains explicit and easier to follow.
- **Helps with Debugging**: Since `this` is only valid inside methods, errors related to improper use are easier to detect. Using full paths also helps pinpoint issues more precisely by avoiding confusion with similarly named objects.
- **Encourages Best Practices**: These guidelines encourage a more structured and organized approach to coding in OSP, fostering a clearer and more maintainable codebase in larger projects.

---

## Note:

### Never use underscores when naming things in OSP. Otherwise, you can use them, but be cautious because underscores can be unstable.


#### Example of OSP

```htvm
def obj Movable.Vehicles.Car {
    prop int door := 4
    prop int fuel := 100
    prop bool hasFUEL := true
}
def obj Movable.Vehicles.Bike {
    prop bool hasGears := true
    prop int energy := 100
    prop bool hasENERGY := true
}
func void move(this) {
    global Movable.Vehicles.Car.fuel
    global Movable.Vehicles.Car.hasFUEL
    global Movable.Vehicles.Bike.energy
    global Movable.Vehicles.Bike.hasENERGY
    if (this = "Movable.Vehicles.Car") {
        if (Movable.Vehicles.Car.fuel > 0) {
            print("The car is driving.")
            Movable_Vehicles_Car_fuel := Movable.Vehicles.Car.fuel - 10
        }
        else {
            print("The car is out of fuel.")
            Movable_Vehicles_Car_hasFUEL := false
        }
    }
    else if (this = "Movable.Vehicles.Bike") {
        if (Movable.Vehicles.Bike.energy > 0) {
            print("The bike is pedaling.")
            Movable_Vehicles_Bike_energy := Movable.Vehicles.Bike.energy - 5
        }
        else {
            print("The bike is out of energy.")
            Movable_Vehicles_Bike_hasENERGY := false
        }
    }
}
def obj Movable.settings.GeneralSettings {
    prop str difficulty := "normal"
    prop int volume := 50
    prop str resolution := "1920x1080"
}
def obj Movable.settings.AudioSettings {
    prop int masterVolume := 70
    prop int musicVolume := 50
    prop int sfxVolume := 40
}
def obj Movable.settings.DisplaySettings {
    prop bool fullscreen := true
    prop str aspectRatio := "16:9"
}
func void resetGeneralSettings(this) {
    Movable_settings_GeneralSettings_difficulty := STR("normal")
    Movable_settings_GeneralSettings_volume := 50
    Movable_settings_GeneralSettings_resolution := STR("1920x1080")
    print("General settings reset to default.")
}
func void printGeneralSettings(this) {
    print("General Settings:")
    print("Difficulty: " . Movable.settings.GeneralSettings.difficulty)
    print("Volume: " . STR(Movable.settings.GeneralSettings.volume))
    print("Resolution: " . Movable.settings.GeneralSettings.resolution)
}
func void resetAudioSettings(this) {
    Movable_settings_AudioSettings_masterVolume := 70
    Movable_settings_AudioSettings_musicVolume := 50
    Movable_settings_AudioSettings_sfxVolume := 40
    print("Audio settings reset to default.")
}
func void printAudioSettings(this) {
    print("Audio Settings:")
    print("Master Volume: " . STR(Movable.settings.AudioSettings.masterVolume))
    print("Music Volume: " . STR(Movable.settings.AudioSettings.musicVolume))
    print("SFX Volume: " . STR(Movable.settings.AudioSettings.sfxVolume))
}
func void resetDisplaySettings(this) {
    Movable_settings_DisplaySettings_fullscreen := true
    Movable_settings_DisplaySettings_aspectRatio := STR("16:9")
    print("Display settings reset to default.")
}
func void printDisplaySettings(this) {
    print("Display Settings:")
    print("Fullscreen: " . STR(Movable.settings.DisplaySettings.fullscreen))
    print("Aspect Ratio: " . Movable.settings.DisplaySettings.aspectRatio)
}
def obj Movable.array.name {
    prop arr str prop1
    prop arr str prop2
    prop arr str prop3
    prop arr str prop4
}
main
; Test vehicle movement
while (Movable.Vehicles.Car.hasFUEL = true) and (Movable.Vehicles.Bike.hasENERGY = true) {
    Movable.Vehicles.move("Movable.Vehicles.Car")
    Movable.Vehicles.move("Movable.Vehicles.Bike")
    print("=====================================")
}
; Test settings manipulation
Movable_settings_GeneralSettings_difficulty := STR("hard")
Movable_settings_GeneralSettings_volume := 80
Movable_settings_GeneralSettings_resolution := STR("2560x1440")
Movable_settings_AudioSettings_masterVolume := 90
Movable_settings_AudioSettings_musicVolume := 60
Movable_settings_AudioSettings_sfxVolume := 50
Movable_settings_DisplaySettings_fullscreen := false
Movable_settings_DisplaySettings_aspectRatio := STR("21:9")
Movable.actions.printGeneralSettings()
Movable.actions.printAudioSettings()
Movable.actions.printDisplaySettings()
Movable.actions.resetGeneralSettings()
Movable.actions.resetAudioSettings()
Movable.actions.resetDisplaySettings()
Movable.actions.printGeneralSettings()
Movable.actions.printAudioSettings()
Movable.actions.printDisplaySettings()
; Test array manipulation
Movable.array.name.prop1.add("1text1")
Movable.array.name.prop1.add("1text2")
Movable.array.name.prop1.add("1text3")
Movable.array.name.prop2.add("2text1")
Movable.array.name.prop2.add("2text2")
Movable.array.name.prop2.add("2text3")
Movable.array.name.prop3.add("3text1")
Movable.array.name.prop3.add("3text2")
Movable.array.name.prop3.add("3text3")
Movable.array.name.prop4.add("4text1")
Movable.array.name.prop4.add("4text2")
Movable.array.name.prop4.add("4text3")
Loop, % Movable.array.name.prop1.size() {
    print(Movable.array.name.prop1[A_Index])
}
Loop, % Movable.array.name.prop2.size() {
    print(Movable.array.name.prop2[A_Index])
}
Loop, % Movable.array.name.prop3.size() {
    print(Movable.array.name.prop3[A_Index])
}
Loop, % Movable.array.name.prop4.size() {
    print(Movable.array.name.prop4[A_Index])
}

```

OSP simplifies programming while ensuring compatibility with **C++**, **Python**, and **JavaScript**.  

---

## Built-in Functions  

[Go back](#htvm-documentation) 

HTVM includes a variety of built-in functions organized into categories for convenience.

1. [Math Functions](#math-functions)
2. [String Functions](#string-functions)
3. [System Functions](#system-functions)
4. [File Functions](#file-functions)
5. [Io Functions](#io-functions)
6. [Gui Functions](#gui-functions)
7. [Other Functions](#other-functions)
8. [Backend Functions](#backend-functions)

---

## Math Functions

[Go back](#built-in-functions)

1. [ACos](#acos)
2. [ASin](#asin)
3. [ATan](#atan)
4. [Abs](#abs)
5. [Ceil](#ceil)
6. [Cos](#cos)
7. [Exp](#exp)
8. [Floor](#floor)
9. [Ln](#ln)
10. [Log](#log)
11. [Mod](#mod)
12. [Random](#random)
13. [Round](#round)
14. [Sin](#sin)
15. [Sqrt](#sqrt)
16. [Tan](#tan)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| ACos | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| ASin | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| ATan | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Abs | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Ceil | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Cos | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Exp | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Floor | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Ln | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Log | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Mod | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Random | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Round | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Sin | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Sqrt | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Tan | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |

---

### ACos

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| ACos | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### ASin

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| ASin | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### ATan

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| ATan | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Abs

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Abs | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Ceil

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Ceil | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Cos

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Cos | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Exp

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Exp | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Floor

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Floor | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Ln

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Ln | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Log

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Log | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Mod

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Mod | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Random

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Random | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Round

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Round | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Sin

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Sin | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Sqrt

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Sqrt | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Tan

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Tan | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

## String Functions

[Go back](#built-in-functions)

1. [Asc](#asc)
2. [Chr](#chr)
3. [FLOAT](#float)
4. [INT](#int)
5. [InStr](#instr)
6. [RegExMatch](#regexmatch)
7. [RegExReplace](#regexreplace)
8. [STR](#str)
9. [Sort](#sort)
10. [StrLen](#strlen)
11. [StrLower](#strlower)
12. [StrReplace](#strreplace)
13. [StrSplit](#strsplit)
14. [StrTitleCase](#strtitlecase)
15. [StringTrimLeft](#stringtrimleft)
16. [StringTrimRight](#stringtrimright)
17. [SubStr](#substr)
18. [Trim](#trim)
19. [countChars](#countchars)
20. [getUrlParams](#geturlparams)
21. [sortArr](#sortarr)
22. [sortArrByLenOnly](#sortarrbylenonly)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Asc | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Chr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| FLOAT | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| INT | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| InStr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| RegExMatch | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| RegExReplace | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| STR | Yes | Yes | Yes | Yes |Yes |Yes |Yes |No |No |Yes |Yes |Yes |Yes |Yes |Yes |
| Sort | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| StrLen | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| StrLower | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| StrReplace | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| StrSplit | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| StrTitleCase | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| StringTrimLeft | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| StringTrimRight | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| SubStr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Trim | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| countChars | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| getUrlParams | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| sortArr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| sortArrByLenOnly | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |

---

### Asc

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Asc | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Chr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Chr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### FLOAT

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FLOAT | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### INT

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| INT | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### InStr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| InStr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### RegExMatch

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| RegExMatch | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### RegExReplace

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| RegExReplace | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### STR

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| STR | Yes | Yes | Yes | Yes |Yes |Yes |Yes |No |No |Yes |Yes |Yes |Yes |Yes |Yes |


---

### Sort

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Sort | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### StrLen

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StrLen | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### StrLower

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StrLower | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### StrReplace

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StrReplace | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### StrSplit

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StrSplit | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### StrTitleCase

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StrTitleCase | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### StringTrimLeft

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StringTrimLeft | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### StringTrimRight

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StringTrimRight | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### SubStr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| SubStr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Trim

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Trim | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### countChars

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| countChars | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### getUrlParams

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| getUrlParams | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### sortArr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| sortArr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### sortArrByLenOnly

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| sortArrByLenOnly | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

## System Functions

[Go back](#built-in-functions)

1. [BuildInVars](#buildinvars)
2. [ExitApp](#exitapp)
3. [HTVM_getLang_HTVM](#htvm_getlang_htvm)
4. [Sleep](#sleep)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| BuildInVars | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| ExitApp | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| HTVM_getLang_HTVM | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Sleep | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |

---

### BuildInVars

[Go back](#system-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| BuildInVars | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### ExitApp

[Go back](#system-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| ExitApp | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### HTVM_getLang_HTVM

[Go back](#system-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| HTVM_getLang_HTVM | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Sleep

[Go back](#system-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Sleep | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

## File Functions

[Go back](#built-in-functions)

1. [FileAppend](#fileappend)
2. [FileAppendJs](#fileappendjs)
3. [FileCreateDir](#filecreatedir)
4. [FileDelete](#filedelete)
5. [FileExist](#fileexist)
6. [FileRead](#fileread)
7. [FileRemoveDir](#fileremovedir)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileAppend | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| FileAppendJs | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| FileCreateDir | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| FileDelete | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| FileExist | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| FileRead | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| FileRemoveDir | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |

---

### FileAppend

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileAppend | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### FileAppendJs

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileAppendJs | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### FileCreateDir

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileCreateDir | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### FileDelete

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileDelete | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### FileExist

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileExist | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### FileRead

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileRead | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### FileRemoveDir

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileRemoveDir | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

## Io Functions

[Go back](#built-in-functions)

1. [GetParams](#getparams)
2. [RunCMD](#runcmd)
3. [getDataFromAPI](#getdatafromapi)
4. [input](#input)
5. [print](#print)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| GetParams | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| RunCMD | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| getDataFromAPI | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| input | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| print | Yes | Yes | Yes | Yes |Yes |Yes |Yes |No |No |Yes |Yes |Yes |Yes |Yes |Yes |

---

### GetParams

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| GetParams | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### RunCMD

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| RunCMD | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### getDataFromAPI

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| getDataFromAPI | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### input

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| input | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### print

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| print | Yes | Yes | Yes | Yes |Yes |Yes |Yes |No |No |Yes |Yes |Yes |Yes |Yes |Yes |


---

## Gui Functions

[Go back](#built-in-functions)

1. [GuiControl](#guicontrol)
2. [Gui_Button](#gui_button)
3. [Gui_CheckBox](#gui_checkbox)
4. [Gui_Color](#gui_color)
5. [Gui_DropDownList](#gui_dropdownlist)
6. [Gui_Edit](#gui_edit)
7. [Gui_Font](#gui_font)
8. [Gui_Font_Id](#gui_font_id)
9. [Gui_Hide](#gui_hide)
10. [Gui_Image](#gui_image)
11. [Gui_Move](#gui_move)
12. [Gui_Show](#gui_show)
13. [Gui_Size](#gui_size)
14. [Gui_Size_Id](#gui_size_id)
15. [Gui_Text](#gui_text)
16. [Gui_Toggle](#gui_toggle)
17. [Gui_Update](#gui_update)
18. [MsgBox](#msgbox)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| GuiControl | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Button | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_CheckBox | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Color | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_DropDownList | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Edit | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Font | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Font_Id | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Hide | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Image | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Move | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Show | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Size | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Size_Id | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Text | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Toggle | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Update | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| MsgBox | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |

---

### GuiControl

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| GuiControl | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Button

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Button | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_CheckBox

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_CheckBox | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Color

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Color | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_DropDownList

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_DropDownList | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Edit

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Edit | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Font

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Font | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Font_Id

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Font_Id | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Hide

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Hide | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Image

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Image | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Move

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Move | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Show

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Show | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Size

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Size | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Size_Id

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Size_Id | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Text

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Text | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Toggle

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Toggle | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Update

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Update | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### MsgBox

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| MsgBox | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

## Other Functions

[Go back](#built-in-functions)

1. [HTVM_v2_HTVM](#htvm_v2_htvm)
2. [MakeHotKey](#makehotkey)
3. [isWindows](#iswindows)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| HTVM_v2_HTVM | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| MakeHotKey | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| isWindows | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |

---

### HTVM_v2_HTVM

[Go back](#other-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| HTVM_v2_HTVM | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### MakeHotKey

[Go back](#other-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| MakeHotKey | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### isWindows

[Go back](#other-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| isWindows | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

## Backend Functions

[Go back](#built-in-functions)

1. [addEndpoint](#addendpoint)
2. [createBackendInit](#createbackendinit)
3. [getDataFromEndpoint](#getdatafromendpoint)
4. [startServer](#startserver)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| addEndpoint | No | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| createBackendInit | No | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| getDataFromEndpoint | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| startServer | No | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |

---

### addEndpoint

[Go back](#backend-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| addEndpoint | No | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### createBackendInit

[Go back](#backend-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| createBackendInit | No | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### getDataFromEndpoint

[Go back](#backend-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| getDataFromEndpoint | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### startServer

[Go back](#backend-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| startServer | No | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

