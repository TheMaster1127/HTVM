// Define the HTVM mode for Ace Editor
ace.define("ace/mode/htvm", ["require", "exports", "module", "ace/lib/oop", "ace/mode/text", "ace/mode/text_highlight_rules"], function(require, exports, module) {
    var oop = require("ace/lib/oop");
    var TextMode = require("ace/mode/text").Mode;
    var TextHighlightRules = require("ace/mode/text_highlight_rules").TextHighlightRules;

    var HTVMHighlightRules = function() {
        
        console.log(new URLSearchParams(window.location.search).get('id'));

        
        var htvmKeywords = "if|else if|else|def obj|prop|crew|alliance|method|while|for|Loop|Loop,|Loop, Parse,|continue|break|func|await|switch|case|throw|try|catch|finally|var|let|const|return|end";
        var builtInCommands = "StringTrimLeft|StringTrimRight|Random|Sleep|FileRead|FileAppend|FileDelete|Sort|MsgBox";
        var builtInFunctions = "HTVM_func1|LoopParseFunc|print|STR|INT|FLOAT|InStr|Random|Sleep|input|FileRead|FileAppend|FileDelete|StrLen|Asc|Abs|ACos|ASin|ATan|Ceil|Cos|Exp|Ln|Log|Round|Sin|Sqrt|Tan|SubStr|Trim|StrReplace|StringTrimLeft|StringTrimRight|StrLower|StrSplit|Chr|Mod|Floor|Sort|getDataFromAPI|FileCreateDir|FileRemoveDir|FileExist|isWindows|GetParams|BuildInVars|RegExReplace|RunCMD|RegExMatch|ExitApp|Gui_Show|Gui_Update|Gui_Button|Gui_Edit|Gui_Text|Gui_Size|Gui_Font|GuiControl|MakeHotKey|sortArr|countChars|StrTitleCase|createBackendInit|addEndpoint|startServer|getDataFromEndpoint|HTVM_getLang_HTVM|ErrorMsg";
        var staticTypes = "int|str|void|bool|float|int8|int16|int32|int64|arr|arr int|arr str|arr float|arr bool";
        var builtInVars = "A_Index|A_LoopField|this";
        var arrayMethods = "add|pop|size|insert|rm|indexOf";

        this.$rules = {
            start: [
                { token: "comment", regex: ";.*$" },
                { token: "comment.block", regex: /'''1/, next: "comment_block" },
                { token: "keyword", regex: "\\b(?:" + htvmKeywords + ")\\b" },
                { token: "command", regex: "\\b(?:" + builtInCommands + ")(?=\\,)" },
                { token: "functions", regex: "\\b(?:" + builtInFunctions + ")(?=\\()" },
                { token: "BuildInFunc", regex: "\\b(?:" + builtInVars + ")\\b" },
                { token: "arrayMethods", regex: "\\.(?:" + arrayMethods + ")\\b" },
                { token: "static_types", regex: "\\b(?:" + staticTypes + ")\\b" },
                { token: "operators", regex: "&&|\\|\\||and|or" },
                { token: "trueANDfalse", regex: "\\b(true|false|global)\\b" },
                { token: "variables", regex: "\\b[a-zA-Z_][a-zA-Z0-9_]*\\b" },
                { token: "constant.numeric", regex: "\\b[0-9]+\\b" },
                { token: "braces_Open", regex: "\\{" },
                { token: "braces_Close", regex: "\\}" },
                { token: "string", regex: '".*?"' }
            ],
            comment_block: [
                { token: "comment.block", regex: /.*?'''2/, next: "start" },
                { token: "comment.block", regex: /.*/ }
            ]
        };
    };

    oop.inherits(HTVMHighlightRules, TextHighlightRules);

    var Mode = function() {
        this.HighlightRules = HTVMHighlightRules;
    };
    oop.inherits(Mode, TextMode);

    exports.Mode = Mode;
});

