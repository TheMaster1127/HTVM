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
| Floor | Yes | Yes | Yes |
| Ln | Yes | Yes | Yes |
| Log | Yes | Yes | Yes |
| Mod | Yes | Yes | Yes |
| Random | Yes | Yes | Yes |
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

ACos is a function that returns the arc cosine (inverse cosine) of a number, which must be between -1 and 1.
here is how the func looks like:
```
ACos(float)
```

---

### ASin

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| ASin | Yes | Yes | Yes |

ASin is a function that calculates the arcsine (inverse sine) of a given value, throwing an error if the value is outside the range of -1 to 1.
here is how the func looks like:
```
ASin(float value)
```

---

### ATan

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| ATan | Yes | Yes | Yes |

ATan is a function that calculates the arctangent of a number, returning the angle in radians.
here is how the func looks like:
```
ATan(float)
```

---

### Abs

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Abs | Yes | Yes | Yes |

Abs is a function that returns the absolute value of the provided number.
here is how the func looks like:
```
Abs(int value)
```

---

### Ceil

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Ceil | Yes | Yes | Yes |

Ceil is a function that takes a numerical value and returns the smallest integer greater than or equal to that value.
here is how the func looks like:
```
Ceil(num)
```

---

### Cos

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Cos | Yes | Yes | Yes |

Cos is a function that calculates the cosine of a given angle in radians.
here is how the func looks like:
```
Cos(float angle)
```

---

### Exp

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Exp | Yes | Yes | Yes |

Exp is a function that takes a numeric value and returns the value of e raised to the power of the given value using the Math.exp() function.
here is how the func looks like:
```
Exp(value)
```

---

### Floor

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Floor | Yes | Yes | Yes |

Floor is a function that returns the largest integer less than or equal to a given number, or NaN if the input is not a number.
here is how the func looks like:
```
Floor(num)
```

---

### Ln

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Ln | Yes | Yes | Yes |

Ln is a function that calculates the natural logarithm (base e) of a given value.
here is how the func looks like:
```
Ln(int value)
```

---

### Log

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Log | Yes | Yes | Yes |

Log is a function that calculates the base 10 logarithm of a given value.
here is how the func looks like:
```
Log(int value)
```

---

### Mod

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Mod | Yes | Yes | Yes |

Mod is a function that returns the remainder when the dividend is divided by the divisor.
here is how the func looks like:
```
Mod(int dividend, int divisor)
```

---

### Random

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Random | Yes | Yes | Yes |

Random is a function that generates and returns a random integer between a specified minimum and maximum value, inclusive.
here is how the func looks like:
```
Random(min, max)
```

---

### Round

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Round | Yes | Yes | Yes |

Round is a function that rounds a given numeric value to the nearest integer.
here is how the func looks like:
```
Round(num)
```

---

### Sin

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Sin | Yes | Yes | Yes |

Sin is a function that takes an angle (in radians) and returns the sine of that angle.
here is how the func looks like:
```
Sin(float)
```

---

### Sqrt

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Sqrt | Yes | Yes | Yes |

Sqrt is a function that calculates the square root of a given numeric value.
here is how the func looks like:
```
Sqrt(num)
```

---

### Tan

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Tan | Yes | Yes | Yes |

Tan is a function that calculates the tangent of the given angle (in radians).
here is how the func looks like:
```
Tan(float)
```

---

## String Functions

[Go back](#built-in-functions)

1. [Asc](#asc)
2. [Chr](#chr)
3. [FLOAT](#float)
4. [HTVM_getLang_HTVM](#htvm_getlang_htvm)
5. [INT](#int)
6. [InStr](#instr)
7. [RegExMatch](#regexmatch)
8. [RegExReplace](#regexreplace)
9. [STR](#str)
10. [Sort](#sort)
11. [StrLen](#strlen)
12. [StrLower](#strlower)
13. [StrReplace](#strreplace)
14. [StrSplit](#strsplit)
15. [StrTitleCase](#strtitlecase)
16. [StringTrimLeft](#stringtrimleft)
17. [StringTrimRight](#stringtrimright)
18. [SubStr](#substr)
19. [Trim](#trim)
20. [countChars](#countchars)
21. [getUrlParams](#geturlparams)
22. [sortArr](#sortarr)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Asc | Yes | Yes | Yes |
| Chr | Yes | Yes | Yes |
| FLOAT | Yes | Yes | Yes |
| HTVM_getLang_HTVM | Yes | Yes | Yes |
| INT | Yes | Yes | Yes |
| InStr | Yes | Yes | Yes |
| RegExMatch | Yes | Yes | Yes |
| RegExReplace | Yes | Yes | Yes |
| STR | Yes | Yes | Yes |
| Sort | Yes | Yes | Yes |
| StrLen | Yes | Yes | Yes |
| StrLower | Yes | Yes | Yes |
| StrReplace | Yes | Yes | Yes |
| StrSplit | Yes | Yes | Yes |
| StrTitleCase | Yes | Yes | Yes |
| StringTrimLeft | Yes | Yes | Yes |
| StringTrimRight | Yes | Yes | Yes |
| SubStr | Yes | Yes | Yes |
| Trim | Yes | Yes | Yes |
| countChars | Yes | Yes | Yes |
| getUrlParams | No | No | Yes |
| sortArr | Yes | Yes | Yes |

---

### Asc

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Asc | Yes | Yes | Yes |

Asc is a function that takes a string and returns the ASCII value of its first character, or -1 if the string is empty.
here is how the func looks like:
```
Asc(str s)
```

---

### Chr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Chr | Yes | Yes | Yes |

Chr is a function that returns the character corresponding to the given Unicode code point or an empty string if the number is out of range.
here is how the func looks like:
```
Chr(int number)
```

---

### FLOAT

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FLOAT | Yes | Yes | Yes |

FLOAT is a function that converts a given value to a float and throws an error if the value cannot be converted.
here is how the func looks like:
```
FLOAT(str value)
```

---

### HTVM_getLang_HTVM

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| HTVM_getLang_HTVM | Yes | Yes | Yes |

HTVM_getLang_HTVM is a func that returns the current language of HTVM as a string
here is how the func looks like:
```
HTVM_getLang_HTVM()
```

---

### INT

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| INT | Yes | Yes | Yes |

INT is a function that converts a value to an integer, throwing an error if the conversion fails.
here is how the func looks like:
```
INT(str value)
```

---

### InStr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| InStr | Yes | Yes | Yes |

InStr is a function that finds the position of the substring needle within the string haystack and returns its position (1-based index), or 0 if the substring is not found.
here is how the func looks like:
```
InStr(str haystack, str needle)
```

---

### RegExMatch

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| RegExMatch | Yes | Yes | Yes |

RegExMatch is a function that returns the 1-based index of the first regex match or 0 if no match is found.
here is how the func looks like:
```
RegExMatch(str haystack, str needle)
```

---

### RegExReplace

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| RegExReplace | Yes | Yes | Yes |

RegExReplace is a function that performs a regular expression-based replacement on a string using a given pattern and replacement string.
here is how the func looks like:
```
RegExReplace(str inputStr, str regexPattern, str replacement)
```

---

### STR

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| STR | Yes | Yes | Yes |

STR is a function that converts a value to its string representation, handling numbers, booleans, and strings, while throwing an error for unsupported types.
here is how the func looks like:
```
STR(value)
```

---

### Sort

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Sort | Yes | Yes | Yes |

Sort is a function that takes a string and optional options to sort its elements based on various criteria such as numeric, random, alphabetical, case sensitivity, and more, with support for delimiters and unique filtering.
here is how the func looks like:
```
Sort(str varName, [str options = ""])
```

---

### StrLen

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StrLen | Yes | Yes | Yes |

StrLen is a function that takes a string as input and returns its length as a size_t value.
here is how the func looks like:
```
StrLen(str)
```

---

### StrLower

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StrLower | Yes | Yes | Yes |

StrLower is a function that takes a string as input and converts all characters to lowercase.
here is how the func looks like:
```
StrLower(string)
```

---

### StrReplace

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StrReplace | Yes | Yes | Yes |

StrReplace is a function that takes an original string, a substring to find, and a substring to replace it with, returning the modified string.
here is how the func looks like:
```
StrReplace(str originalString, str find, str replaceWith)
```

---

### StrSplit

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StrSplit | Yes | Yes | Yes |

StrSplit is a function that splits an input string by a specified delimiter and returns the part at the specified index, or an empty string if the index is out of range.
here is how the func looks like:
```
StrSplit(str inputStr, str delimiter, int num)
```

---

### StrTitleCase

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StrTitleCase | Yes | Yes | Yes |

StrTitleCase is a function that takes an input string and converts each word to title case, capitalizing the first letter of each word while making the rest lowercase.
here is how the func looks like:
```
StrTitleCase(str inputString)
```

---

### StringTrimLeft

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StringTrimLeft | Yes | Yes | Yes |

StringTrimLeft is a function that trims a specified number of characters from the left side of a given string.
here is how the func looks like:
```
StringTrimLeft(str input, int numChars)
```

---

### StringTrimRight

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| StringTrimRight | Yes | Yes | Yes |

StringTrimRight is a function that trims a specified number of characters from the right side of a given string.
here is how the func looks like:
```
StringTrimRight(str input, int numChars)
```

---

### SubStr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| SubStr | Yes | Yes | Yes |

SubStr is a function that extracts a substring from a given string, starting from a specified position and for a specified length, adjusting for edge cases like null inputs or missing parameters.
here is how the func looks like:
```
SubStr(str, int startPos, int length [= str.length - startPos + 1])
```

---

### Trim

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Trim | Yes | Yes | Yes |

Trim is a function that removes leading and trailing whitespace from the input string.
here is how the func looks like:
```
Trim(string)
```

---

### countChars

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| countChars | Yes | Yes | Yes |

countChars is a function that counts the occurrences of a specific character (`theChar`) in a given string.
here is how the func looks like:
```
countChars(str string, str theChar)
```

---

### getUrlParams

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| getUrlParams | No | No | Yes |

getUrlParams is a function that extracts and decodes parameter values from the URL query string, returning a combined string of values separated by '&'.
here is how the func looks like:
```
getUrlParams()
```

---

### sortArr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| sortArr | Yes | Yes | Yes |

sortArr is a function that takes an array, removes any duplicate values using a Set, and returns the array sorted in ascending order.
here is how the func looks like:
```
sortArr(arr str stringArray)
```

---

## System Functions

[Go back](#built-in-functions)

1. [BuildInVars](#buildinvars)
2. [ExitApp](#exitapp)
3. [Sleep](#sleep)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| BuildInVars | Yes | Yes | Yes |
| ExitApp | Yes | Yes | No |
| Sleep | Yes | Yes | Yes |

---

### BuildInVars

[Go back](#system-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| BuildInVars | Yes | Yes | Yes |

BuildInVars is a function that retrieves various system-related values or states, including screen dimensions, timestamps, key presses, and more, based on the specified variable name.
here is how the func looks like:
```
BuildInVars(str varName)
```

---

### ExitApp

[Go back](#system-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| ExitApp | Yes | Yes | No |

ExitApp is a function that terminates the application immediately.
here is how the func looks like:
```
ExitApp()
```

---

### Sleep

[Go back](#system-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Sleep | Yes | Yes | Yes |

Sleep is a function that pauses execution for a specified number of milliseconds.
here is how the func looks like:
```
Sleep(int milliseconds)
```

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

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileAppend | Yes | Yes | No |
| FileAppendJs | No | No | Yes |
| FileCreateDir | Yes | Yes | No |
| FileDelete | Yes | Yes | No |
| FileExist | Yes | Yes | No |
| FileRead | Yes | Yes | No |
| FileRemoveDir | Yes | Yes | No |

---

### FileAppend

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileAppend | Yes | Yes | No |

FileAppend is a function that appends the given content to a file at the specified path and returns a boolean indicating success or failure.
here is how the func looks like:
```
FileAppend(str content, str path)
```

---

### FileAppendJs

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileAppendJs | No | No | Yes |

FileAppendJs is a function that appends content to a file by creating a Blob, generating a download link, and triggering a download with the specified filename.
here is how the func looks like:
```
FileAppendJs(str content, str filename)
```

---

### FileCreateDir

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileCreateDir | Yes | Yes | No |

FileCreateDir is a function that checks if a directory exists, and if not, it creates the directory.
here is how the func looks like:
```
FileCreateDir(str directory)
```

---

### FileDelete

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileDelete | Yes | Yes | No |

FileDelete is a function that checks if a file exists at the given path and deletes it if found, returning True if the file is deleted, otherwise False.
here is how the func looks like:
```
FileDelete(str path)
```

---

### FileExist

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileExist | Yes | Yes | No |

FileExist is a function that checks if a file or directory exists at the specified path.
here is how the func looks like:
```
FileExist(str path)
```

---

### FileRead

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileRead | Yes | Yes | No |

FileRead is a function that reads the content of a file given a path, prepends the current working directory if the path is not absolute, and returns the file content as a string.
here is how the func looks like:
```
FileRead(path: str)
```

---

### FileRemoveDir

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| FileRemoveDir | Yes | Yes | No |

FileRemoveDir is a function that removes a directory and its contents if the directory exists.
here is how the func looks like:
```
FileRemoveDir(str directory)
```

---

## Io Functions

[Go back](#built-in-functions)

1. [GetParams](#getparams)
2. [RunCMD](#runcmd)
3. [getDataFromAPI](#getdatafromapi)
4. [input](#input)
5. [print](#print)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| GetParams | Yes | Yes | No |
| RunCMD | Yes | Yes | No |
| getDataFromAPI | Yes | Yes | Yes |
| input | Yes | Yes | Yes |
| print | Yes | Yes | Yes |

---

### GetParams

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| GetParams | Yes | Yes | No |

GetParams is a function that retrieves command line arguments, checks if they correspond to existing paths, and returns them as absolute paths in new lines, or as they are if they do not exist.
here is how the func looks like:
```
GetParams()
```

---

### RunCMD

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| RunCMD | Yes | Yes | No |

RunCMD is a function that executes a shell command and captures its output or errors.
here is how the func looks like:
```
RunCMD(str command)
```

---

### getDataFromAPI

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| getDataFromAPI | Yes | Yes | Yes |

getDataFromAPI is a function that asynchronously fetches JSON data from a given URL and returns it, handling errors and non-OK responses.
here is how the func looks like:
```
getDataFromAPI(str url)
```

---

### input

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| input | Yes | Yes | Yes |

input is a function that displays a prompt with the given text and returns the user's input.
here is how the func looks like:
```
input(str promptText)
```

---

### print

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| print | Yes | Yes | Yes |

print is a function that outputs the specified data to the console or standard output.
here is how the func looks like:
```
print(str)
```

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

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| GuiControl | No | No | Yes |
| Gui_Button | No | No | Yes |
| Gui_CheckBox | No | No | Yes |
| Gui_Color | No | No | Yes |
| Gui_DropDownList | No | No | Yes |
| Gui_Edit | No | No | Yes |
| Gui_Font | No | No | Yes |
| Gui_Font_Id | No | No | Yes |
| Gui_Hide | No | No | Yes |
| Gui_Image | No | No | Yes |
| Gui_Move | No | No | Yes |
| Gui_Show | No | No | Yes |
| Gui_Size | No | No | Yes |
| Gui_Size_Id | No | No | Yes |
| Gui_Text | No | No | Yes |
| Gui_Toggle | No | No | Yes |
| Gui_Update | No | No | Yes |
| MsgBox | No | No | Yes |

---

### GuiControl

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| GuiControl | No | No | Yes |

GuiControl is a function that handles various DOM manipulations like moving, showing, hiding, and modifying elements based on the provided action and parameters.
here is how the func looks like:
```
GuiControl(str action, str divId, str id, [any param1 = ?], [any param2 = ?], [any param3 = ?], [any param4 = ?])
```

---

### Gui_Button

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Button | No | No | Yes |

Gui_Button is a function that creates a button inside a specified div and allows customization of its position, size, color, and click behavior.
here is how the func looks like:
```
Gui_Button(str guiID, str buttonID, str buttonText, [int x = null], [int y = null], [int w = 150], [int h = 50], [str color = '#121212'], [str textColor = '#FFFFFF'], [bool removeBorder = false], [int roundness = null], [int zIndex = null], [func onClickCallback = null])
```

---

### Gui_CheckBox

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_CheckBox | No | No | Yes |

Gui_CheckBox is a function that creates a checkbox within a specified GUI element, allowing for custom label, position, color, initial checked state, and scaling. The checkbox is added to a specified parent div, and a callback function is executed when the checkbox state changes.
here is how the func looks like:
```
Gui_CheckBox(str guiID, str id, str label, [str color = "#ffffff"], int leftPos, int topPos, func checkFunction, [bool isCheckedAtTheBeginning = false], [float scale = 1.5])
```

---

### Gui_Color

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Color | No | No | Yes |

Gui_Color is a function that sets the background color of a specific HTML element identified by the given guiID. If the element is not found, it logs a warning.
here is how the func looks like:
```
Gui_Color(str guiID, str color)
```

---

### Gui_DropDownList

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_DropDownList | No | No | Yes |

Gui_DropDownList is a function that creates a dropdown list (select element) with options from a string, sets styles, attaches an event listener for selection changes, and appends it to a specified parent element.
here is how the func looks like:
```
Gui_DropDownList(parent, str id, str data, int leftPos, int topPos, int width, int height, str color, func onChangeFunction)
```

---

### Gui_Edit

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Edit | No | No | Yes |

Gui_Edit is a function that creates a textarea element within a div, allowing customization of its appearance, position, and behavior, with optional parameters for width, height, colors, borders, and a callback for input changes.
here is how the func looks like:
```
Gui_Edit(str guiID, str editID, str placeholderText, [int x = null], [int y = null], [int w = null], [int h = null], [str color = '#121212'], [str textColor = '#FFFFFF'], [bool removeBorder = false], [int roundness = null], [int zIndex = null], [func onChangeCallback = null])
```

---

### Gui_Font

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Font | No | No | Yes |

Gui_Font is a function that sets the font family for a specified element and all its descendants, including buttons, inputs, and textareas.
here is how the func looks like:
```
Gui_Font(str divID, str fontFamily)
```

---

### Gui_Font_Id

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Font_Id | No | No | Yes |

Gui_Font_Id is a function that changes the font family of specified elements in the HTML document based on provided div and element IDs.
here is how the func looks like:
```
Gui_Font_Id(str divID, str elementID, str fontFamily)
```

---

### Gui_Hide

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Hide | No | No | Yes |

Gui_Hide is a function that hides an HTML element by setting its display style to "none" based on the provided element ID.
here is how the func looks like:
```
Gui_Hide(str elementId)
```

---

### Gui_Image

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Image | No | No | Yes |

Gui_Image is a function that creates and displays an image within a specified div element on the webpage. It optionally sets the image's position, size, and corner roundness, while ensuring that the image maintains its aspect ratio if only one dimension is provided.
here is how the func looks like:
```
Gui_Image(str guiID, str imageID, str imageUrl, [int x = null], [int y = null], [int w = null], [int h = null], [int roundness = null])
```

---

### Gui_Move

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Move | No | No | Yes |

Gui_Move is a function that moves or resizes a GUI element by modifying its position and dimensions based on the provided parameters.
here is how the func looks like:
```
Gui_Move(str guiID, [int x = null], [int y = null], [int w = null], [int h = null])
```

---

### Gui_Show

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Show | No | No | Yes |

Gui_Show is a function that displays a div element on the screen with customizable properties such as position, size, border, background color, and z-index. It creates the div if it doesn't exist and centers it by default.
here is how the func looks like:
```
Gui_Show(guiID, [x], [y], [w], [h], [removeBorder = false], [color = '#121212'], [roundness], [zIndex])
```

---

### Gui_Size

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Size | No | No | Yes |

Gui_Size is a function that adjusts the font size of the specified HTML element and its children based on the given font size value.
here is how the func looks like:
```
Gui_Size(str divID, int fontSize)
```

---

### Gui_Size_Id

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Size_Id | No | No | Yes |

Gui_Size_Id is a function that changes the font size of a specified div and another specified element by their respective IDs.
here is how the func looks like:
```
Gui_Size_Id(str divID, str elementID, int fontSize)
```

---

### Gui_Text

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Text | No | No | Yes |

Gui_Text is a function that creates and inserts a text element into a specified GUI container, with optional parameters for positioning, color, roundness, and z-index.
here is how the func looks like:
```
Gui_Text(str guiID, str textID, str text, [int x = null], [int y = null], [str color = '#FFFFFF'], [int roundness = null], [int zIndex = null])
```

---

### Gui_Toggle

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Toggle | No | No | Yes |

Gui_Toggle is a function that creates a toggle switch UI element, allowing users to toggle between two states (on/off) with customizable properties such as label, position, size, and color. It also includes a callback function to handle the state change.
here is how the func looks like:
```
Gui_Toggle(str guiID, str id, str label, str [color = null], int leftPos, int topPos, [int width = null], [int height = null], func switchFunction, bool [isToggledAtTheBeginning = false])
```

---

### Gui_Update

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| Gui_Update | No | No | Yes |

Gui_Update is a function that updates or creates a div element based on the provided guiID, setting its dimensions, position, background color, border, border-radius, and z-index, with optional parameters for customization.
here is how the func looks like:
```
Gui_Update(str guiID, [int x = null], [int y = null], [int w = 450], [int h = 450], [bool removeBorder = false], [str color = '#121212'], [int roundness = null], [int zIndex = null])
```

---

### MsgBox

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| MsgBox | No | No | Yes |

MsgBox is a function that displays a message box with customizable text, title, buttons, and icons, handling various options based on the provided value and timeout.
here is how the func looks like:
```
MsgBox(str text, str [title = " "], int [value = 0], int [timeout = null])
```

---

## Other Functions

[Go back](#built-in-functions)

1. [MakeHotKey](#makehotkey)
2. [isWindows](#iswindows)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| MakeHotKey | No | No | Yes |
| isWindows | Yes | Yes | No |

---

### MakeHotKey

[Go back](#other-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| MakeHotKey | No | No | Yes |

MakeHotKey is a function that listens for a specific key combination (hotkey) and triggers a callback when the hotkey is pressed. It handles modifiers like Ctrl, Shift, and Alt, as well as specific keys such as arrows and backspace. The callback function is invoked with the hotkey in either uppercase or lowercase, depending on the Shift modifier.
here is how the func looks like:
```
MakeHotKey(str hotkey, function callback)
```

---

### isWindows

[Go back](#other-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| isWindows | Yes | Yes | No |

isWindows is a function that checks if the current operating system is Windows by comparing the system name to "windows".
here is how the func looks like:
```
isWindows()
```

---

## Backend Functions

[Go back](#built-in-functions)

1. [addEndpoint](#addendpoint)
2. [createBackendInit](#createbackendinit)
3. [getDataFromEndpoint](#getdatafromendpoint)
4. [startServer](#startserver)

---

**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| addEndpoint | No | Yes | No |
| createBackendInit | No | Yes | No |
| getDataFromEndpoint | No | No | Yes |
| startServer | No | Yes | No |

---

### addEndpoint

[Go back](#backend-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| addEndpoint | No | Yes | No |

addEndpoint is a function that registers a given function as an endpoint with a specified HTTP method (default is POST).
here is how the func looks like:
```
addEndpoint(func func, str method [default = "POST"])
```
Here is an exmaple how to use the backend
```py
# Initialize Flask app
createBackendInit()
# Define your custom endpoint functions using camelCase
def helloWord(data):
    # Handle data and return plain text response
    return f"Hello, you sent: {data['message']}"
def uppercaseText(data):
    # Handle data and return plain text response
    return data['text'].upper()
# Register the endpoints
addEndpoint(helloWord)
addEndpoint(uppercaseText)
# Start the server
startServer()
```
This exmaple is in python but the funcs works in HTVM like normal funcs.

---

### createBackendInit

[Go back](#backend-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| createBackendInit | No | Yes | No |

createBackendInit is a function that initializes a Flask app, sets up a default route to serve an `index.html` file, and registers a custom 404 error handler and uses the app variable so never use the app variable please
here is how the func looks like:
```
createBackendInit([filename = "index.html"])
```
Here is an exmaple how to use the backend
```py
# Initialize Flask app
createBackendInit()
# Define your custom endpoint functions using camelCase
def helloWord(data):
    # Handle data and return plain text response
    return f"Hello, you sent: {data['message']}"
def uppercaseText(data):
    # Handle data and return plain text response
    return data['text'].upper()
# Register the endpoints
addEndpoint(helloWord)
addEndpoint(uppercaseText)
# Start the server
startServer()
```
This exmaple is in python but the funcs works in HTVM like normal funcs.

---

### getDataFromEndpoint

[Go back](#backend-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| getDataFromEndpoint | No | No | Yes |

getDataFromEndpoint is a function that fetches data from a specified endpoint using a provided HTTP method (default is POST), sends the data as a JSON string, and parses the response based on its content type.
here is how the func looks like:
```
getDataFromEndpoint(data, endpoint, method = "POST")
```

---

### startServer

[Go back](#backend-functions)

**HTVM build-in functions availability.**

| Function | C++ | Python | JavaScript |
|----------|----------|----------|----------|
| startServer | No | Yes | No |

startServer is a function that runs a Flask web application on a specified host and port, with default values for the host and port parameters.
here is how the func looks like:
```
startServer([port=8000], [host="0.0.0.0"])
```
Here is an exmaple how to use the backend
```py
# Initialize Flask app
createBackendInit()
# Define your custom endpoint functions using camelCase
def helloWord(data):
    # Handle data and return plain text response
    return f"Hello, you sent: {data['message']}"
def uppercaseText(data):
    # Handle data and return plain text response
    return data['text'].upper()
# Register the endpoints
addEndpoint(helloWord)
addEndpoint(uppercaseText)
# Start the server
startServer()
```
This exmaple is in python but the funcs works in HTVM like normal funcs.

---

