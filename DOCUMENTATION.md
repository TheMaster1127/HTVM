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
  - Finally blocks (except in C++)
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
```cpp
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
  ``` cpp
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
   ```cpp
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
```cpp
def obj Standalone {
    prop int value = 10
    prop str name = "Independent"
}
```

to access later just use:

```cpp
Standalone.value
Standalone.name
```

---

### **Methods in Alliances**
- Methods can also be defined directly in an **alliance**, without being part of a **crew** and the opposite is well.

### **Example: Method in an Alliance**
```cpp
alliance ExampleAlliance {
    method void greet() {
        print("Hello from ExampleAlliance!")
    }
}
```

to call greet just do:

```cpp
ExampleAlliance.greet()
```

## Global Accessibility:  
  - There are no scopes in OSP. As long as a variable or structure is defined above, it is accessible below. Everything is global, and the full path must always be used.  

## Arrays:  
  - When using arrays you need to create a temporary array and then copy it to another like this:

```py
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

```cpp
alliance Movable {
    crew Vehicles {
        def obj Car {
            prop int door = 4
            prop int fuel = 100
            prop bool hasFUEL = true
        }
        def obj Bike {
            prop bool hasGears = true
            prop int energy = 100
            prop bool hasENERGY = true
        }

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
    }
    
    crew settings {
        def obj GeneralSettings {
            prop str difficulty = "normal"
            prop int volume = 50
            prop str resolution = "1920x1080"
        }
        def obj AudioSettings {
            prop int masterVolume = 70
            prop int musicVolume = 50
            prop int sfxVolume = 40
        }
        def obj DisplaySettings {
            prop bool fullscreen = true
            prop str aspectRatio = "16:9"
        }
    }
    
    crew actions {
        // General Settings Methods
        method void resetGeneralSettings() {
            Movable.settings.GeneralSettings.difficulty = STR("normal")
            Movable.settings.GeneralSettings.volume = 50
            Movable.settings.GeneralSettings.resolution = STR("1920x1080")
            print("General settings reset to default.")
        }
        method void printGeneralSettings() {
            print("General Settings:")
            print("Difficulty: " + Movable.settings.GeneralSettings.difficulty)
            print("Volume: " + STR(Movable.settings.GeneralSettings.volume))
            print("Resolution: " + Movable.settings.GeneralSettings.resolution)
        }

        // Audio Settings Methods
        method void resetAudioSettings() {
            Movable.settings.AudioSettings.masterVolume = 70
            Movable.settings.AudioSettings.musicVolume = 50
            Movable.settings.AudioSettings.sfxVolume = 40
            print("Audio settings reset to default.")
        }
        method void printAudioSettings() {
            print("Audio Settings:")
            print("Master Volume: " + STR(Movable.settings.AudioSettings.masterVolume))
            print("Music Volume: " + STR(Movable.settings.AudioSettings.musicVolume))
            print("SFX Volume: " + STR(Movable.settings.AudioSettings.sfxVolume))
        }

        // Display Settings Methods
        method void resetDisplaySettings() {
            Movable.settings.DisplaySettings.fullscreen = true
            Movable.settings.DisplaySettings.aspectRatio = STR("16:9")
            print("Display settings reset to default.")
        }
        method void printDisplaySettings() {
            print("Display Settings:")
            print("Fullscreen: " + STR(Movable.settings.DisplaySettings.fullscreen))
            print("Aspect Ratio: " + Movable.settings.DisplaySettings.aspectRatio)
        }
    }

    crew array {
        def obj name {
            arr str temp
            prop arr str prop1 = temp
            prop arr str prop2 = temp
            prop arr str prop3 = temp
            prop arr str prop4 = temp
        }
    }
    
}

main
// Test vehicle movement
while (Movable.Vehicles.Car.hasFUEL == true) && (Movable.Vehicles.Bike.hasENERGY = true) {
    Movable.Vehicles.move(Movable.Vehicles.Car)
    Movable.Vehicles.move(Movable.Vehicles.Bike)
    print("=====================================")
}

// Test settings manipulation
Movable.settings.GeneralSettings.difficulty = STR("hard")
Movable.settings.GeneralSettings.volume = 80
Movable.settings.GeneralSettings.resolution = STR("2560x1440")
Movable.settings.AudioSettings.masterVolume = 90
Movable.settings.AudioSettings.musicVolume = 60
Movable.settings.AudioSettings.sfxVolume = 50
Movable.settings.DisplaySettings.fullscreen = false
Movable.settings.DisplaySettings.aspectRatio = STR("21:9")

Movable.actions.printGeneralSettings()
Movable.actions.printAudioSettings()
Movable.actions.printDisplaySettings()

Movable.actions.resetGeneralSettings()
Movable.actions.resetAudioSettings()
Movable.actions.resetDisplaySettings()

Movable.actions.printGeneralSettings()
Movable.actions.printAudioSettings()
Movable.actions.printDisplaySettings()

// Test array manipulation
Movable.array.name.prop1.push("1text1")
Movable.array.name.prop1.push("1text2")
Movable.array.name.prop1.push("1text3")
Movable.array.name.prop2.push("2text1")
Movable.array.name.prop2.push("2text2")
Movable.array.name.prop2.push("2text3")
Movable.array.name.prop3.push("3text1")
Movable.array.name.prop3.push("3text2")
Movable.array.name.prop3.push("3text3")
Movable.array.name.prop4.push("4text1")
Movable.array.name.prop4.push("4text2")
Movable.array.name.prop4.push("4text3")

// why this
// cuz python used len(param) insed of param.len() so it meses up evrything
// if using OSP objects that have a dot (.) it doset work in python to get the lenght
// but for a name whit no dots it works

arr str arrayTempOnlyGetSize1 = Movable.array.name.prop1
arr str arrayTempOnlyGetSize2 = Movable.array.name.prop2
arr str arrayTempOnlyGetSize3 = Movable.array.name.prop3
arr str arrayTempOnlyGetSize4 = Movable.array.name.prop4




Loop, % arrayTempOnlyGetSize1.size() 
{
print(Movable.array.name.prop1[A_Index])
}
Loop, % arrayTempOnlyGetSize2.size() {
    print(Movable.array.name.prop2[A_Index])
}
Loop, % arrayTempOnlyGetSize3.size() {
    print(Movable.array.name.prop3[A_Index])
}
Loop, % arrayTempOnlyGetSize4.size() {
    print(Movable.array.name.prop4[A_Index])
}

```

OSP simplifies programming while ensuring compatibility with **C++**, **Python**, and **JavaScript**.  

---

## Built-in Functions  

[Go back](#htvm-documentation) 

HTVM includes a variety of built-in functions organized into categories for convenience.

1. [Math Functions](#math-functions)
2. [Asc Func Is A Func Functions](#asc-func-is-a-func-functions)
3. [Buildinvars Is A Function To Get Built-in Variables Like A_tickcount, A_now, And Date/time-related Values. Functions](#buildinvars-is-a-function-to-get-built-in-variables-like-a_tickcount,-a_now,-and-date/time-related-values.-functions)
4. [Returns A Character Corresponding To The Provided Unicode Code Point. Functions](#returns-a-character-corresponding-to-the-provided-unicode-code-point.-functions)
5. [Exitapp Is A Function To Exit The Application. Functions](#exitapp-is-a-function-to-exit-the-application.-functions)
6. [Float Func Is A Func Functions](#float-func-is-a-func-functions)
7. [Fileappend Func Is A Func Functions](#fileappend-func-is-a-func-functions)
8. [Filecreatedir Is A Function To Create A Directory If It Does Not Exist. Functions](#filecreatedir-is-a-function-to-create-a-directory-if-it-does-not-exist.-functions)
9. [Filedelete Func Is A Func Functions](#filedelete-func-is-a-func-functions)
10. [Fileexist Is A Function To Check If A File Or Directory Exists. Functions](#fileexist-is-a-function-to-check-if-a-file-or-directory-exists.-functions)
11. [Fileread Func Is A Func Functions](#fileread-func-is-a-func-functions)
12. [Fileremovedir Is A Function To Remove A Directory If It Exists. Functions](#fileremovedir-is-a-function-to-remove-a-directory-if-it-exists.-functions)
13. [Rounds Down A Floating-point Number To The Nearest Integer. Functions](#rounds-down-a-floating-point-number-to-the-nearest-integer.-functions)
14. [Getparams Is A Func For Platform-specific Handling For Command-line Arguments And Getting Parameters. Functions](#getparams-is-a-func-for-platform-specific-handling-for-command-line-arguments-and-getting-parameters.-functions)
15. [A Function That Handles Various Actions (move, Focus, Text, Hide, Show, Enable, Disable, Font, Destroy, Color, Picture, Textide) On Dom Elements, Divs, And Canvas Elements, Allowing For Dynamic Manipulation Based On The Specified Action. Functions](#a-function-that-handles-various-actions-(move,-focus,-text,-hide,-show,-enable,-disable,-font,-destroy,-color,-picture,-textide)-on-dom-elements,-divs,-and-canvas-elements,-allowing-for-dynamic-manipulation-based-on-the-specified-action.-functions)
16. [A Function That Creates A Button Inside A Div With Customizable Appearance, Size, Position, And Click Behavior, Based On A Unique Button Id. Functions](#a-function-that-creates-a-button-inside-a-div-with-customizable-appearance,-size,-position,-and-click-behavior,-based-on-a-unique-button-id.-functions)
17. [A Function To Create A Classic Checkbox With Customizable Position, Scaling, And Color. It Also Triggers A Specified Function When Checked Or Unchecked. Functions](#a-function-to-create-a-classic-checkbox-with-customizable-position,-scaling,-and-color.-it-also-triggers-a-specified-function-when-checked-or-unchecked.-functions)
18. [A Function To Set The Background Color Of A Div Using A Specified Color. Functions](#a-function-to-set-the-background-color-of-a-div-using-a-specified-color.-functions)
19. [A Function To Create And Populate A Dropdown List (select Element) Dynamically Within A Specified Parent Div, With Custom Styles, Options, And A Change Event Handler. Functions](#a-function-to-create-and-populate-a-dropdown-list-(select-element)-dynamically-within-a-specified-parent-div,-with-custom-styles,-options,-and-a-change-event-handler.-functions)
20. [A Function That Creates A Textarea Input Inside A Div With Customizable Appearance, Size, Position, And Change Behavior, Based On A Unique Edit Id. Functions](#a-function-that-creates-a-textarea-input-inside-a-div-with-customizable-appearance,-size,-position,-and-change-behavior,-based-on-a-unique-edit-id.-functions)
21. [A Function That Sets The Font Family For The Specified Div And All Its Child Elements, Including Buttons, Inputs, And Textareas. Functions](#a-function-that-sets-the-font-family-for-the-specified-div-and-all-its-child-elements,-including-buttons,-inputs,-and-textareas.-functions)
22. [A Function That Sets The Font Family For The Specified Div And A Specific Element Within It By Id. Functions](#a-function-that-sets-the-font-family-for-the-specified-div-and-a-specific-element-within-it-by-id.-functions)
23. [A Function To Hide An Html Element With A Specified Id By Setting Its Display Style To "none". Functions](#a-function-to-hide-an-html-element-with-a-specified-id-by-setting-its-display-style-to-"none".-functions)
24. [A Function To Create And Display An Image Within A Div, With Optional Resizing, Positioning, And Rounded Corners. Functions](#a-function-to-create-and-display-an-image-within-a-div,-with-optional-resizing,-positioning,-and-rounded-corners.-functions)
25. [A Function To Move And Resize A Div By Updating Its Position And Dimensions Based On Provided Values For X, Y, Width, And Height. Functions](#a-function-to-move-and-resize-a-div-by-updating-its-position-and-dimensions-based-on-provided-values-for-x,-y,-width,-and-height.-functions)
26. [A Function That Creates Or Shows A Custom Styled Div On The Screen With Configurable Position, Size, And Appearance, Using A Unique Id To Manage It. Functions](#a-function-that-creates-or-shows-a-custom-styled-div-on-the-screen-with-configurable-position,-size,-and-appearance,-using-a-unique-id-to-manage-it.-functions)
27. [A Function That Sets The Font Size For The Specified Div And All Its Child Elements, Including Buttons, Inputs, And Textareas. Functions](#a-function-that-sets-the-font-size-for-the-specified-div-and-all-its-child-elements,-including-buttons,-inputs,-and-textareas.-functions)
28. [A Function That Sets The Font Size For The Specified Div And A Specific Element Within It By Id. Functions](#a-function-that-sets-the-font-size-for-the-specified-div-and-a-specific-element-within-it-by-id.-functions)
29. [A Function That Creates A Text Element Inside A Div With Customizable Appearance, Size, Position, And Other Styles. Functions](#a-function-that-creates-a-text-element-inside-a-div-with-customizable-appearance,-size,-position,-and-other-styles.-functions)
30. [A Function To Create A Toggle Switch With Customizable Positioning, Size, And Color. It Also Calls A Specified Function When Toggled. Functions](#a-function-to-create-a-toggle-switch-with-customizable-positioning,-size,-and-color.-it-also-calls-a-specified-function-when-toggled.-functions)
31. [A Function That Updates The Properties (position, Size, Appearance) Of An Existing Div Or Creates A New One If It Doesn't Exist, Based On A Unique Id. Functions](#a-function-that-updates-the-properties-(position,-size,-appearance)-of-an-existing-div-or-creates-a-new-one-if-it-doesn't-exist,-based-on-a-unique-id.-functions)
32. [Int Func Is A Func Functions](#int-func-is-a-func-functions)
33. [Instr Func Is A Func Functions](#instr-func-is-a-func-functions)
34. [A Function To Create A Hotkey. Functions](#a-function-to-create-a-hotkey.-functions)
35. [Returns The Remainder Of The Division Of Two Integers. Functions](#returns-the-remainder-of-the-division-of-two-integers.-functions)
36. [A Function That Displays A Custom Message Box With Options Like Title, Text, Buttons, Icon, And Timeout, Based On A Value Parameter That Determines Button Behavior. Functions](#a-function-that-displays-a-custom-message-box-with-options-like-title,-text,-buttons,-icon,-and-timeout,-based-on-a-value-parameter-that-determines-button-behavior.-functions)
37. [Random Func Is A Func Functions](#random-func-is-a-func-functions)
38. [Regexmatch Is A Function To Perform Regex Matching And Return The Match Position. Functions](#regexmatch-is-a-function-to-perform-regex-matching-and-return-the-match-position.-functions)
39. [Regexreplace Is A Function To Perform Regex Replacement. Functions](#regexreplace-is-a-function-to-perform-regex-replacement.-functions)
40. [Runcmd Is A Function To Run A System Command And Capture The Output. Functions](#runcmd-is-a-function-to-run-a-system-command-and-capture-the-output.-functions)
41. [Str Func Is A Func Functions](#str-func-is-a-func-functions)
42. [Sleep Func Is A Func Functions](#sleep-func-is-a-func-functions)
43. [Sort Func Is A Func Functions](#sort-func-is-a-func-functions)
44. [Strlen Func Is A Func Functions](#strlen-func-is-a-func-functions)
45. [Converts All Characters In A String To Lowercase. Functions](#converts-all-characters-in-a-string-to-lowercase.-functions)
46. [String Functions](#string-functions)
47. [Splits A String By A Delimiter And Returns The Nth Split. Functions](#splits-a-string-by-a-delimiter-and-returns-the-nth-split.-functions)
48. [Trims Characters From The Left Side Of The String Based On The Specified Number Of Characters. Functions](#trims-characters-from-the-left-side-of-the-string-based-on-the-specified-number-of-characters.-functions)
49. [Trims Characters From The Right Side Of The String Based On The Specified Number Of Characters. Functions](#trims-characters-from-the-right-side-of-the-string-based-on-the-specified-number-of-characters.-functions)
50. [Counts The Occurrences Of A Specific Character In A String. Functions](#counts-the-occurrences-of-a-specific-character-in-a-string.-functions)
51. [Getdatafromapi Is A Function To Fetch Data From An Api. Functions](#getdatafromapi-is-a-function-to-fetch-data-from-an-api.-functions)
52. [Geturlparams Is A Func Functions](#geturlparams-is-a-func-functions)
53. [Input Func Is A Func Functions](#input-func-is-a-func-functions)
54. [Iswindows Is A Function To Check If The Operating System Is Windows Functions](#iswindows-is-a-function-to-check-if-the-operating-system-is-windows-functions)
55. [Hello That Is Func Mhm Functions](#hello-that-is-func-mhm-functions)
56. [Function To Sort A String Array And Remove Duplicates. Functions](#function-to-sort-a-string-array-and-remove-duplicates.-functions)

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
8. [Ln](#ln)
9. [Log](#log)
10. [Round](#round)
11. [Sin](#sin)
12. [Sqrt](#sqrt)
13. [Tan](#tan)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| ACos | Yes | Yes | Yes |
| ASin | Yes | Yes | Yes |
| ATan | Yes | Yes | Yes |
| Abs | Yes | Yes | Yes |
| Ceil | Yes | Yes | Yes |
| Cos | Yes | Yes | Yes |
| Exp | Yes | Yes | Yes |
| Ln | Yes | Yes | Yes |
| Log | Yes | Yes | Yes |
| Round | Yes | Yes | Yes |
| Sin | Yes | Yes | Yes |
| Sqrt | Yes | Yes | Yes |
| Tan | Yes | Yes | Yes |

---

### ACos

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| ACos | Yes | Yes | Yes |

ACos func calculates the arc cosine of a value

---

### ASin

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| ASin | Yes | Yes | Yes |

ASin func calculates the arc sine of a value, with error handling for out-of-range inputs

---

### ATan

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| ATan | Yes | Yes | Yes |

ATan func calculates the arc tangent of a value

---

### Abs

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Abs | Yes | Yes | Yes |

Abs func is a func

---

### Ceil

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Ceil | Yes | Yes | Yes |

Ceil func rounds a value upwards to the nearest integer

---

### Cos

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Cos | Yes | Yes | Yes |

Cos func calculates the cosine of an angle

---

### Exp

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Exp | Yes | Yes | Yes |

Exp func calculates the exponential of a value

---

### Ln

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Ln | Yes | Yes | Yes |

Ln func calculates the natural logarithm of a value

---

### Log

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Log | Yes | Yes | Yes |

Log func calculates the base-10 logarithm of a value

---

### Round

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Round | Yes | Yes | Yes |

Round func rounds a value to the nearest integer

---

### Sin

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Sin | Yes | Yes | Yes |

Sin func calculates the sine of an angle

---

### Sqrt

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Sqrt | Yes | Yes | Yes |

Sqrt func calculates the square root of a value

---

### Tan

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Tan | Yes | Yes | Yes |

Tan func calculates the tangent of an angle

---

## Asc Func Is A Func Functions

[Go back](#built-in-functions)

1. [Asc](#asc)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Asc | Yes | Yes | Yes |

---

### Asc

[Go back](#asc-func-is-a-func-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Asc | Yes | Yes | Yes |


---

## Buildinvars Is A Function To Get Built-in Variables Like A_tickcount, A_now, And Date/time-related Values. Functions

[Go back](#built-in-functions)

1. [BuildInVars](#buildinvars)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| BuildInVars | Yes | Yes | Yes |

---

### BuildInVars

[Go back](#buildinvars-is-a-function-to-get-built-in-variables-like-a_tickcount,-a_now,-and-date/time-related-values.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| BuildInVars | Yes | Yes | Yes |


---

## Returns A Character Corresponding To The Provided Unicode Code Point. Functions

[Go back](#built-in-functions)

1. [Chr](#chr)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Chr | Yes | Yes | Yes |

---

### Chr

[Go back](#returns-a-character-corresponding-to-the-provided-unicode-code-point.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Chr | Yes | Yes | Yes |


---

## Exitapp Is A Function To Exit The Application. Functions

[Go back](#built-in-functions)

1. [ExitApp](#exitapp)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| ExitApp | Yes | Yes | No |

---

### ExitApp

[Go back](#exitapp-is-a-function-to-exit-the-application.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| ExitApp | Yes | Yes | No |


---

## Float Func Is A Func Functions

[Go back](#built-in-functions)

1. [FLOAT](#float)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FLOAT | Yes | Yes | Yes |

---

### FLOAT

[Go back](#float-func-is-a-func-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FLOAT | Yes | Yes | Yes |


---

## Fileappend Func Is A Func Functions

[Go back](#built-in-functions)

1. [FileAppend](#fileappend)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileAppend | Yes | Yes | Yes |

---

### FileAppend

[Go back](#fileappend-func-is-a-func-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileAppend | Yes | Yes | Yes |


---

## Filecreatedir Is A Function To Create A Directory If It Does Not Exist. Functions

[Go back](#built-in-functions)

1. [FileCreateDir](#filecreatedir)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileCreateDir | Yes | Yes | No |

---

### FileCreateDir

[Go back](#filecreatedir-is-a-function-to-create-a-directory-if-it-does-not-exist.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileCreateDir | Yes | Yes | No |


---

## Filedelete Func Is A Func Functions

[Go back](#built-in-functions)

1. [FileDelete](#filedelete)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileDelete | Yes | Yes | No |

---

### FileDelete

[Go back](#filedelete-func-is-a-func-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileDelete | Yes | Yes | No |


---

## Fileexist Is A Function To Check If A File Or Directory Exists. Functions

[Go back](#built-in-functions)

1. [FileExist](#fileexist)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileExist | Yes | Yes | No |

---

### FileExist

[Go back](#fileexist-is-a-function-to-check-if-a-file-or-directory-exists.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileExist | Yes | Yes | No |


---

## Fileread Func Is A Func Functions

[Go back](#built-in-functions)

1. [FileRead](#fileread)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileRead | Yes | Yes | No |

---

### FileRead

[Go back](#fileread-func-is-a-func-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileRead | Yes | Yes | No |


---

## Fileremovedir Is A Function To Remove A Directory If It Exists. Functions

[Go back](#built-in-functions)

1. [FileRemoveDir](#fileremovedir)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileRemoveDir | Yes | Yes | No |

---

### FileRemoveDir

[Go back](#fileremovedir-is-a-function-to-remove-a-directory-if-it-exists.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileRemoveDir | Yes | Yes | No |


---

## Rounds Down A Floating-point Number To The Nearest Integer. Functions

[Go back](#built-in-functions)

1. [Floor](#floor)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Floor | Yes | Yes | Yes |

---

### Floor

[Go back](#rounds-down-a-floating-point-number-to-the-nearest-integer.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Floor | Yes | Yes | Yes |


---

## Getparams Is A Func For Platform-specific Handling For Command-line Arguments And Getting Parameters. Functions

[Go back](#built-in-functions)

1. [GetParams](#getparams)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| GetParams | Yes | Yes | No |

---

### GetParams

[Go back](#getparams-is-a-func-for-platform-specific-handling-for-command-line-arguments-and-getting-parameters.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| GetParams | Yes | Yes | No |


---

## A Function That Handles Various Actions (move, Focus, Text, Hide, Show, Enable, Disable, Font, Destroy, Color, Picture, Textide) On Dom Elements, Divs, And Canvas Elements, Allowing For Dynamic Manipulation Based On The Specified Action. Functions

[Go back](#built-in-functions)

1. [GuiControl](#guicontrol)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| GuiControl | No | No | Yes |

---

### GuiControl

[Go back](#a-function-that-handles-various-actions-(move,-focus,-text,-hide,-show,-enable,-disable,-font,-destroy,-color,-picture,-textide)-on-dom-elements,-divs,-and-canvas-elements,-allowing-for-dynamic-manipulation-based-on-the-specified-action.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| GuiControl | No | No | Yes |


---

## A Function That Creates A Button Inside A Div With Customizable Appearance, Size, Position, And Click Behavior, Based On A Unique Button Id. Functions

[Go back](#built-in-functions)

1. [Gui_Button](#gui_button)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Button | No | No | Yes |

---

### Gui_Button

[Go back](#a-function-that-creates-a-button-inside-a-div-with-customizable-appearance,-size,-position,-and-click-behavior,-based-on-a-unique-button-id.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Button | No | No | Yes |


---

## A Function To Create A Classic Checkbox With Customizable Position, Scaling, And Color. It Also Triggers A Specified Function When Checked Or Unchecked. Functions

[Go back](#built-in-functions)

1. [Gui_CheckBox](#gui_checkbox)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_CheckBox | No | No | Yes |

---

### Gui_CheckBox

[Go back](#a-function-to-create-a-classic-checkbox-with-customizable-position,-scaling,-and-color.-it-also-triggers-a-specified-function-when-checked-or-unchecked.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_CheckBox | No | No | Yes |


---

## A Function To Set The Background Color Of A Div Using A Specified Color. Functions

[Go back](#built-in-functions)

1. [Gui_Color](#gui_color)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Color | No | No | Yes |

---

### Gui_Color

[Go back](#a-function-to-set-the-background-color-of-a-div-using-a-specified-color.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Color | No | No | Yes |


---

## A Function To Create And Populate A Dropdown List (select Element) Dynamically Within A Specified Parent Div, With Custom Styles, Options, And A Change Event Handler. Functions

[Go back](#built-in-functions)

1. [Gui_DropDownList](#gui_dropdownlist)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_DropDownList | No | No | Yes |

---

### Gui_DropDownList

[Go back](#a-function-to-create-and-populate-a-dropdown-list-(select-element)-dynamically-within-a-specified-parent-div,-with-custom-styles,-options,-and-a-change-event-handler.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_DropDownList | No | No | Yes |


---

## A Function That Creates A Textarea Input Inside A Div With Customizable Appearance, Size, Position, And Change Behavior, Based On A Unique Edit Id. Functions

[Go back](#built-in-functions)

1. [Gui_Edit](#gui_edit)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Edit | No | No | Yes |

---

### Gui_Edit

[Go back](#a-function-that-creates-a-textarea-input-inside-a-div-with-customizable-appearance,-size,-position,-and-change-behavior,-based-on-a-unique-edit-id.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Edit | No | No | Yes |


---

## A Function That Sets The Font Family For The Specified Div And All Its Child Elements, Including Buttons, Inputs, And Textareas. Functions

[Go back](#built-in-functions)

1. [Gui_Font](#gui_font)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Font | No | No | Yes |

---

### Gui_Font

[Go back](#a-function-that-sets-the-font-family-for-the-specified-div-and-all-its-child-elements,-including-buttons,-inputs,-and-textareas.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Font | No | No | Yes |


---

## A Function That Sets The Font Family For The Specified Div And A Specific Element Within It By Id. Functions

[Go back](#built-in-functions)

1. [Gui_Font_Id](#gui_font_id)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Font_Id | No | No | Yes |

---

### Gui_Font_Id

[Go back](#a-function-that-sets-the-font-family-for-the-specified-div-and-a-specific-element-within-it-by-id.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Font_Id | No | No | Yes |


---

## A Function To Hide An Html Element With A Specified Id By Setting Its Display Style To "none". Functions

[Go back](#built-in-functions)

1. [Gui_Hide](#gui_hide)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Hide | No | No | Yes |

---

### Gui_Hide

[Go back](#a-function-to-hide-an-html-element-with-a-specified-id-by-setting-its-display-style-to-"none".-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Hide | No | No | Yes |


---

## A Function To Create And Display An Image Within A Div, With Optional Resizing, Positioning, And Rounded Corners. Functions

[Go back](#built-in-functions)

1. [Gui_Image](#gui_image)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Image | No | No | Yes |

---

### Gui_Image

[Go back](#a-function-to-create-and-display-an-image-within-a-div,-with-optional-resizing,-positioning,-and-rounded-corners.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Image | No | No | Yes |


---

## A Function To Move And Resize A Div By Updating Its Position And Dimensions Based On Provided Values For X, Y, Width, And Height. Functions

[Go back](#built-in-functions)

1. [Gui_Move](#gui_move)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Move | No | No | Yes |

---

### Gui_Move

[Go back](#a-function-to-move-and-resize-a-div-by-updating-its-position-and-dimensions-based-on-provided-values-for-x,-y,-width,-and-height.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Move | No | No | Yes |


---

## A Function That Creates Or Shows A Custom Styled Div On The Screen With Configurable Position, Size, And Appearance, Using A Unique Id To Manage It. Functions

[Go back](#built-in-functions)

1. [Gui_Show](#gui_show)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Show | No | No | Yes |

---

### Gui_Show

[Go back](#a-function-that-creates-or-shows-a-custom-styled-div-on-the-screen-with-configurable-position,-size,-and-appearance,-using-a-unique-id-to-manage-it.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Show | No | No | Yes |


---

## A Function That Sets The Font Size For The Specified Div And All Its Child Elements, Including Buttons, Inputs, And Textareas. Functions

[Go back](#built-in-functions)

1. [Gui_Size](#gui_size)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Size | No | No | Yes |

---

### Gui_Size

[Go back](#a-function-that-sets-the-font-size-for-the-specified-div-and-all-its-child-elements,-including-buttons,-inputs,-and-textareas.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Size | No | No | Yes |


---

## A Function That Sets The Font Size For The Specified Div And A Specific Element Within It By Id. Functions

[Go back](#built-in-functions)

1. [Gui_Size_Id](#gui_size_id)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Size_Id | No | No | Yes |

---

### Gui_Size_Id

[Go back](#a-function-that-sets-the-font-size-for-the-specified-div-and-a-specific-element-within-it-by-id.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Size_Id | No | No | Yes |


---

## A Function That Creates A Text Element Inside A Div With Customizable Appearance, Size, Position, And Other Styles. Functions

[Go back](#built-in-functions)

1. [Gui_Text](#gui_text)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Text | No | No | Yes |

---

### Gui_Text

[Go back](#a-function-that-creates-a-text-element-inside-a-div-with-customizable-appearance,-size,-position,-and-other-styles.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Text | No | No | Yes |


---

## A Function To Create A Toggle Switch With Customizable Positioning, Size, And Color. It Also Calls A Specified Function When Toggled. Functions

[Go back](#built-in-functions)

1. [Gui_Toggle](#gui_toggle)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Toggle | No | No | Yes |

---

### Gui_Toggle

[Go back](#a-function-to-create-a-toggle-switch-with-customizable-positioning,-size,-and-color.-it-also-calls-a-specified-function-when-toggled.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Toggle | No | No | Yes |


---

## A Function That Updates The Properties (position, Size, Appearance) Of An Existing Div Or Creates A New One If It Doesn't Exist, Based On A Unique Id. Functions

[Go back](#built-in-functions)

1. [Gui_Update](#gui_update)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Update | No | No | Yes |

---

### Gui_Update

[Go back](#a-function-that-updates-the-properties-(position,-size,-appearance)-of-an-existing-div-or-creates-a-new-one-if-it-doesn't-exist,-based-on-a-unique-id.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Update | No | No | Yes |


---

## Int Func Is A Func Functions

[Go back](#built-in-functions)

1. [INT](#int)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| INT | Yes | Yes | Yes |

---

### INT

[Go back](#int-func-is-a-func-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| INT | Yes | Yes | Yes |


---

## Instr Func Is A Func Functions

[Go back](#built-in-functions)

1. [InStr](#instr)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| InStr | Yes | Yes | Yes |

---

### InStr

[Go back](#instr-func-is-a-func-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| InStr | Yes | Yes | Yes |


---

## A Function To Create A Hotkey. Functions

[Go back](#built-in-functions)

1. [MakeHotKey](#makehotkey)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| MakeHotKey | No | No | Yes |

---

### MakeHotKey

[Go back](#a-function-to-create-a-hotkey.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| MakeHotKey | No | No | Yes |


---

## Returns The Remainder Of The Division Of Two Integers. Functions

[Go back](#built-in-functions)

1. [Mod](#mod)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Mod | Yes | Yes | Yes |

---

### Mod

[Go back](#returns-the-remainder-of-the-division-of-two-integers.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Mod | Yes | Yes | Yes |


---

## A Function That Displays A Custom Message Box With Options Like Title, Text, Buttons, Icon, And Timeout, Based On A Value Parameter That Determines Button Behavior. Functions

[Go back](#built-in-functions)

1. [MsgBox](#msgbox)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| MsgBox | No | No | Yes |

---

### MsgBox

[Go back](#a-function-that-displays-a-custom-message-box-with-options-like-title,-text,-buttons,-icon,-and-timeout,-based-on-a-value-parameter-that-determines-button-behavior.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| MsgBox | No | No | Yes |


---

## Random Func Is A Func Functions

[Go back](#built-in-functions)

1. [Random](#random)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Random | Yes | Yes | Yes |

---

### Random

[Go back](#random-func-is-a-func-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Random | Yes | Yes | Yes |


---

## Regexmatch Is A Function To Perform Regex Matching And Return The Match Position. Functions

[Go back](#built-in-functions)

1. [RegExMatch](#regexmatch)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| RegExMatch | Yes | Yes | Yes |

---

### RegExMatch

[Go back](#regexmatch-is-a-function-to-perform-regex-matching-and-return-the-match-position.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| RegExMatch | Yes | Yes | Yes |


---

## Regexreplace Is A Function To Perform Regex Replacement. Functions

[Go back](#built-in-functions)

1. [RegExReplace](#regexreplace)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| RegExReplace | Yes | Yes | Yes |

---

### RegExReplace

[Go back](#regexreplace-is-a-function-to-perform-regex-replacement.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| RegExReplace | Yes | Yes | Yes |


---

## Runcmd Is A Function To Run A System Command And Capture The Output. Functions

[Go back](#built-in-functions)

1. [RunCMD](#runcmd)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| RunCMD | Yes | Yes | No |

---

### RunCMD

[Go back](#runcmd-is-a-function-to-run-a-system-command-and-capture-the-output.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| RunCMD | Yes | Yes | No |


---

## Str Func Is A Func Functions

[Go back](#built-in-functions)

1. [STR](#str)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| STR | Yes | Yes | Yes |

---

### STR

[Go back](#str-func-is-a-func-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| STR | Yes | Yes | Yes |


---

## Sleep Func Is A Func Functions

[Go back](#built-in-functions)

1. [Sleep](#sleep)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Sleep | Yes | Yes | Yes |

---

### Sleep

[Go back](#sleep-func-is-a-func-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Sleep | Yes | Yes | Yes |


---

## Sort Func Is A Func Functions

[Go back](#built-in-functions)

1. [Sort](#sort)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Sort | Yes | Yes | Yes |

---

### Sort

[Go back](#sort-func-is-a-func-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Sort | Yes | Yes | Yes |


---

## Strlen Func Is A Func Functions

[Go back](#built-in-functions)

1. [StrLen](#strlen)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StrLen | Yes | Yes | Yes |

---

### StrLen

[Go back](#strlen-func-is-a-func-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StrLen | Yes | Yes | Yes |


---

## Converts All Characters In A String To Lowercase. Functions

[Go back](#built-in-functions)

1. [StrLower](#strlower)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StrLower | Yes | Yes | Yes |

---

### StrLower

[Go back](#converts-all-characters-in-a-string-to-lowercase.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StrLower | Yes | Yes | Yes |


---

## String Functions

[Go back](#built-in-functions)

1. [StrReplace](#strreplace)
2. [StrTitleCase](#strtitlecase)
3. [SubStr](#substr)
4. [Trim](#trim)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StrReplace | Yes | Yes | Yes |
| StrTitleCase | Yes | Yes | Yes |
| SubStr | Yes | Yes | Yes |
| Trim | Yes | Yes | Yes |

---

### StrReplace

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StrReplace | Yes | Yes | Yes |

Replaces all occurrences of a substring with another string in the given string.

---

### StrTitleCase

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StrTitleCase | Yes | Yes | Yes |

StrTitleCase

---

### SubStr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| SubStr | Yes | Yes | Yes |

Extracts a substring from a given string starting at a specified position with an optional length.

---

### Trim

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Trim | Yes | Yes | Yes |

Removes leading and trailing whitespace from a string.

---

## Splits A String By A Delimiter And Returns The Nth Split. Functions

[Go back](#built-in-functions)

1. [StrSplit](#strsplit)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StrSplit | Yes | Yes | Yes |

---

### StrSplit

[Go back](#splits-a-string-by-a-delimiter-and-returns-the-nth-split.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StrSplit | Yes | Yes | Yes |


---

## Trims Characters From The Left Side Of The String Based On The Specified Number Of Characters. Functions

[Go back](#built-in-functions)

1. [StringTrimLeft](#stringtrimleft)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StringTrimLeft | Yes | Yes | Yes |

---

### StringTrimLeft

[Go back](#trims-characters-from-the-left-side-of-the-string-based-on-the-specified-number-of-characters.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StringTrimLeft | Yes | Yes | Yes |


---

## Trims Characters From The Right Side Of The String Based On The Specified Number Of Characters. Functions

[Go back](#built-in-functions)

1. [StringTrimRight](#stringtrimright)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StringTrimRight | Yes | Yes | Yes |

---

### StringTrimRight

[Go back](#trims-characters-from-the-right-side-of-the-string-based-on-the-specified-number-of-characters.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StringTrimRight | Yes | Yes | Yes |


---

## Counts The Occurrences Of A Specific Character In A String. Functions

[Go back](#built-in-functions)

1. [countChars](#countchars)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| countChars | Yes | Yes | Yes |

---

### countChars

[Go back](#counts-the-occurrences-of-a-specific-character-in-a-string.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| countChars | Yes | Yes | Yes |


---

## Getdatafromapi Is A Function To Fetch Data From An Api. Functions

[Go back](#built-in-functions)

1. [getDataFromAPI](#getdatafromapi)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| getDataFromAPI | Yes | Yes | Yes |

---

### getDataFromAPI

[Go back](#getdatafromapi-is-a-function-to-fetch-data-from-an-api.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| getDataFromAPI | Yes | Yes | Yes |


---

## Geturlparams Is A Func Functions

[Go back](#built-in-functions)

1. [getUrlParams](#geturlparams)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| getUrlParams | No | No | Yes |

---

### getUrlParams

[Go back](#geturlparams-is-a-func-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| getUrlParams | No | No | Yes |


---

## Input Func Is A Func Functions

[Go back](#built-in-functions)

1. [input](#input)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| input | Yes | No | Yes |

---

### input

[Go back](#input-func-is-a-func-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| input | Yes | No | Yes |


---

## Iswindows Is A Function To Check If The Operating System Is Windows Functions

[Go back](#built-in-functions)

1. [isWindows](#iswindows)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| isWindows | Yes | Yes | No |

---

### isWindows

[Go back](#iswindows-is-a-function-to-check-if-the-operating-system-is-windows-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| isWindows | Yes | Yes | No |


---

## Hello That Is Func Mhm Functions

[Go back](#built-in-functions)

1. [print](#print)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| print | Yes | No | Yes |

---

### print

[Go back](#hello-that-is-func-mhm-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| print | Yes | No | Yes |


---

## Function To Sort A String Array And Remove Duplicates. Functions

[Go back](#built-in-functions)

1. [sortArr](#sortarr)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| sortArr | Yes | Yes | Yes |

---

### sortArr

[Go back](#function-to-sort-a-string-array-and-remove-duplicates.-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| sortArr | Yes | Yes | Yes |


---

