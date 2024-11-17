// Define the custom "ht" language for Ace Editor with AHK rules
ace.define("ace/mode/ht", ["require", "exports", "module", "ace/lib/oop", "ace/mode/text", "ace/mode/text_highlight_rules"], function (require, exports, module) {
  var oop = require("ace/lib/oop");
  var TextMode = require("ace/mode/text").Mode;
  var TextHighlightRules = require("ace/mode/text_highlight_rules").TextHighlightRules;

  var HTHighlightRules = function () {
    this.$rules = {
      start: [
{ token: "comment", regex: ";.*$" },
              { token: "keywords", regex: "\\b(if|else if|else|def obj|prop|crew|alliance|method|while|for|Loop|Loop,|Loop, Parse,|continue|break|func|await|switch|case|throw|try|catch|finally|var|let|const|return|end)\\b" },
              { token: "command", regex: "\\b(StringTrimLeft|StringTrimRight|Random|Sleep|FileRead|FileAppend|FileDelete|Sort|MsgBox)(?=\\,)" },
              { token: "functions", regex: "\\b(LoopParseFunc|LoopParseFunc|LoopParseFunc|HTVM_func1|print|print|STR|INT|FLOAT|STR|INT|FLOAT|INT|STR|FLOAT|InStr|Random|Sleep|input|FileRead|FileAppend|FileDelete|StrLen|Asc|Abs|ACos|ASin|ATan|Ceil|Cos|Exp|Ln|Log|Round|Sin|Sqrt|Tan|SubStr|Trim|StrReplace|StringTrimLeft|StringTrimRight|StrLower|StrSplit|Chr|Mod|Floor|Sort|getDataFromAPI|FileCreateDir|FileRemoveDir|FileExist|isWindows|GetParams|BuildInVars|RegExReplace|RunCMD|RegExMatch|ExitApp|InStr|InStr|Random|Random|Sleep|Sleep|input|FileAppend|FileDelete|FileAppend|FileRead|StrLen|StrLen|Chr|Chr|Asc|Abs|ACos|ASin|ATan|Ceil|Cos|Exp|Ln|Log|Round|Sin|Sqrt|Tan|Asc|Abs|ACos|ASin|ATan|Ceil|Cos|Exp|Ln|Log|Round|Sin|Sqrt|Tan|SubStr|SubStr|Trim|StrReplace|StringTrimLeft|StringTrimRight|StrLower|StrSplit|Mod|Floor|Trim|StrReplace|StringTrimLeft|StringTrimRight|StrLower|StrSplit|Mod|Floor|Sort|getDataFromAPI|FileCreateDir|FileRemoveDir|FileExist|isWindows|GetParams|BuildInVars|RegExReplace|RunCMD|RegExMatch|ExitApp|Sort|getDataFromAPI|getUrlParams|BuildInVars|RegExReplace|RegExMatch|MsgBox|Gui_Show|Gui_Update|Gui_Button|Gui_Edit|Gui_Text|Gui_Size|Gui_Font|Gui_Font_Id|Gui_Size_Id|GuiControl|Gui_DropDownList|Gui_Hide|Gui_Move|Gui_Color|Gui_Image|Gui_Toggle|Gui_CheckBox|MakeHotKey|sortArr|sortArr|sortArr|countChars|countChars|countChars|ErrorMsg)(?=\\()" },
              { token: "BuildInFunc", regex: "\\b(A_Index|A_LoopField|this)\\b" },
              { token: "arrayMethods", regex: "\\.(\\add|\\pop|\\size|\\insert|\\rm|\\indexOf)\\b" },
              { token: "static_types", regex: "\\b(int|str|void|bool|float|int8|int16|int32|int64|arr|arr int|arr str|arr float|arr bool)\\b" },
              { token: "operators", regex: " && | or | and | && " },
              { token: "trueANDfalse", regex: "\\b(true|false|global)\\b" },
              { token: "variables", regex: "\\b[a-zA-Z_][a-zA-Z0-9_]*\\b" },
              { token: "constant.numeric", regex: "\\b[0-9]+\\b" },
              { token: "braces_Open", regex: "\\{" },
              { token: "braces_Close", regex: "\\}" },
              { token: "string", regex: '".*?"' },
              // Multi-line comments
              {
                token: "comment.block", // Token for multi-line comments
                regex: /'''1/, // Start of multi-line comment
                next: "comment_block",
              },
            ],
            comment_block: [
              {
                token: "comment.block",
                regex: /.*?'''2/, // End of multi-line comment
                next: "start", // Go back to the start state
              },
              {
                token: "comment.block",
                regex: /.*/, // Any other content within the comment
              },
            ],
          };
        };

  oop.inherits(HTHighlightRules, TextHighlightRules);

  var HTMode = function () {
    this.HighlightRules = HTHighlightRules;
  };
  oop.inherits(HTMode, TextMode);

  exports.Mode = HTMode;
});

let HTVM_Syntax_AutoComplete = [{ name: "if" }, { name: "else if" }, { name: "else" }, { name: "def obj" }, { name: "prop" }, { name: "crew" }, { name: "alliance" }, { name: "method" }, { name: "while" }, { name: "for" }, { name: "Loop" }, { name: "Loop," }, { name: "Loop, Parse," }, { name: "continue" }, { name: "break" }, { name: "func" }, { name: "await" }, { name: "switch" }, { name: "case" }, { name: "throw" }, { name: "try" }, { name: "catch" }, { name: "finally" }, { name: "var" }, { name: "let" }, { name: "const" }, { name: "return" }, { name: "end" }, { name: "StringTrimLeft" }, { name: "StringTrimRight" }, { name: "Random" }, { name: "Sleep" }, { name: "FileRead" }, { name: "FileAppend" }, { name: "FileDelete" }, { name: "Sort" }, { name: "MsgBox" }, { name: "LoopParseFunc" }, { name: "LoopParseFunc" }, { name: "LoopParseFunc" }, { name: "HTVM_func1" }, { name: "print" }, { name: "print" }, { name: "STR" }, { name: "INT" }, { name: "FLOAT" }, { name: "STR" }, { name: "INT" }, { name: "FLOAT" }, { name: "INT" }, { name: "STR" }, { name: "FLOAT" }, { name: "InStr" }, { name: "Random" }, { name: "Sleep" }, { name: "input" }, { name: "FileRead" }, { name: "FileAppend" }, { name: "FileDelete" }, { name: "StrLen" }, { name: "Asc" }, { name: "Abs" }, { name: "ACos" }, { name: "ASin" }, { name: "ATan" }, { name: "Ceil" }, { name: "Cos" }, { name: "Exp" }, { name: "Ln" }, { name: "Log" }, { name: "Round" }, { name: "Sin" }, { name: "Sqrt" }, { name: "Tan" }, { name: "SubStr" }, { name: "Trim" }, { name: "StrReplace" }, { name: "StringTrimLeft" }, { name: "StringTrimRight" }, { name: "StrLower" }, { name: "StrSplit" }, { name: "Chr" }, { name: "Mod" }, { name: "Floor" }, { name: "Sort" }, { name: "getDataFromAPI" }, { name: "FileCreateDir" }, { name: "FileRemoveDir" }, { name: "FileExist" }, { name: "isWindows" }, { name: "GetParams" }, { name: "BuildInVars" }, { name: "RegExReplace" }, { name: "RunCMD" }, { name: "RegExMatch" }, { name: "ExitApp" }, { name: "InStr" }, { name: "InStr" }, { name: "Random" }, { name: "Random" }, { name: "Sleep" }, { name: "Sleep" }, { name: "input" }, { name: "FileAppend" }, { name: "FileDelete" }, { name: "FileAppend" }, { name: "FileRead" }, { name: "StrLen" }, { name: "StrLen" }, { name: "Chr" }, { name: "Chr" }, { name: "Asc" }, { name: "Abs" }, { name: "ACos" }, { name: "ASin" }, { name: "ATan" }, { name: "Ceil" }, { name: "Cos" }, { name: "Exp" }, { name: "Ln" }, { name: "Log" }, { name: "Round" }, { name: "Sin" }, { name: "Sqrt" }, { name: "Tan" }, { name: "Asc" }, { name: "Abs" }, { name: "ACos" }, { name: "ASin" }, { name: "ATan" }, { name: "Ceil" }, { name: "Cos" }, { name: "Exp" }, { name: "Ln" }, { name: "Log" }, { name: "Round" }, { name: "Sin" }, { name: "Sqrt" }, { name: "Tan" }, { name: "SubStr" }, { name: "SubStr" }, { name: "Trim" }, { name: "StrReplace" }, { name: "StringTrimLeft" }, { name: "StringTrimRight" }, { name: "StrLower" }, { name: "StrSplit" }, { name: "Mod" }, { name: "Floor" }, { name: "Trim" }, { name: "StrReplace" }, { name: "StringTrimLeft" }, { name: "StringTrimRight" }, { name: "StrLower" }, { name: "StrSplit" }, { name: "Mod" }, { name: "Floor" }, { name: "Sort" }, { name: "getDataFromAPI" }, { name: "FileCreateDir" }, { name: "FileRemoveDir" }, { name: "FileExist" }, { name: "isWindows" }, { name: "GetParams" }, { name: "BuildInVars" }, { name: "RegExReplace" }, { name: "RunCMD" }, { name: "RegExMatch" }, { name: "ExitApp" }, { name: "Sort" }, { name: "getDataFromAPI" }, { name: "getUrlParams" }, { name: "BuildInVars" }, { name: "RegExReplace" }, { name: "RegExMatch" }, { name: "MsgBox" }, { name: "Gui_Show" }, { name: "Gui_Update" }, { name: "Gui_Button" }, { name: "Gui_Edit" }, { name: "Gui_Text" }, { name: "Gui_Size" }, { name: "Gui_Font" }, { name: "Gui_Font_Id" }, { name: "Gui_Size_Id" }, { name: "GuiControl" }, { name: "Gui_DropDownList" }, { name: "Gui_Hide" }, { name: "Gui_Move" }, { name: "Gui_Color" }, { name: "Gui_Image" }, { name: "Gui_Toggle" }, { name: "Gui_CheckBox" }, { name: "MakeHotKey" }, { name: "sortArr" }, { name: "sortArr" }, { name: "sortArr" }, { name: "countChars" }, { name: "countChars" }, { name: "countChars" }, { name: "ErrorMsg" }, { name: "A_LoopField" }, { name: "A_Index" }, { name: "add" }, { name: "pop" }, { name: "size" }, { name: "insert" }, { name: "rm" }, { name: "indexOf" }, { name: "int" }, { name: "str" }, { name: "void" }, { name: "bool" }, { name: "float" }, { name: "int8" }, { name: "int16" }, { name: "int32" }, { name: "int64" }, { name: "arr" }, { name: "arr int" }, { name: "arr str" }, { name: "arr float" }, { name: "arr bool" }, { name: "global" }, { name: "this" }]
