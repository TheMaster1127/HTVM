// htvm-mode.js
'use strict';

(function() {
    function LoopParseFunc(varString, delimiter1="", delimiter2="") {
        if (!varString) return [];
        let items;
        if (!delimiter1 && !delimiter2) { items = [...varString]; }
        else { let pattern = new RegExp('[' + delimiter1.replace(/[.*+?^${}()|[\]\\]/g, '\\$&') + delimiter2.replace(/[.*+?^${}()|[\]\\]/g, '\\$&') + ']+'); items = varString.split(pattern); }
        return items;
    }

    function gui_option_toCaseInsensitivePattern(str) {
      return str.replace(/[-\/\\^$*+?.()|[\]{}]/g, '\\$&')
                .split('')
                .map(ch => {
                  if (/[a-zA-Z]/.test(ch)) {
                    return `[${ch.toUpperCase()}${ch.toLowerCase()}]`;
                  }
                  return ch;
                })
                .join('');
    }

    function Trim(inputString) { return inputString ? inputString.trim() : ""; }
    function StrReplace(originalString, find, replaceWith) { return originalString ? originalString.split(find).join(replaceWith) : ""; }
    function StringTrimRight(input, numChars) { return (input && numChars <= input.length) ? input.substring(0, input.length - numChars) : input; }

    // --- FIX: This function no longer interacts with localStorage. ---
    // It now receives the instruction content directly and defines the Ace mode.
    async function initializeHtvmMode(id, instructionContent = "") {
        const allKeyWordsIn = instructionContent.split('\n');

        const funcLines = allKeyWordsIn.slice(162);
        const allFunctionNamesString = Array.isArray(funcLines) ? funcLines
            .map(line => line.trim())
            .filter(line => line.startsWith("name: "))
            .map(line => line.replace("name: ", "").trim().split(','))
            .flat()
            .map(name => name.trim())
            .filter(Boolean)
            .filter((value, index, self) => self.indexOf(value) === index)
            .join('|') : "";

        let allKeyWordsIn_OUT = "";
        allKeyWordsIn.forEach((field, index) => {
            if (index > 1) { allKeyWordsIn_OUT += field + "\n"; }
        });
        const allKeyWordsOut = StringTrimRight(allKeyWordsIn_OUT, 1);

        ace.define("ace/mode/htvm", ["require", "exports", "module", "ace/lib/oop", "ace/mode/text", "ace/mode/text_highlight_rules"], function(require, exports, module) {
            var oop = require("ace/lib/oop");
            var TextMode = require("ace/mode/text").Mode;
            var TextHighlightRules = require("ace/mode/text_highlight_rules").TextHighlightRules;
            var HTVMHighlightRules = function() {
                // --- FIX: dbGet is now passed here for the operator highlighting toggle ---
                const dbGet = async (key) => {
                    const item = await db.settings.get(key);
                    return item ? item.value : null;
                };

                const allFunctionNamesString3 = allFunctionNamesString;
                const allKeyWordsOut3 = allKeyWordsOut;

                var builtInCommands_temp = "", htvmKeywords_temp = "", staticTypes_temp = "", builtInVars_temp = "A_Input|A_Id|A_Event|A_Value|",
                    symbol_operators_temp = "", word_operators_temp = "", arrayMethods_temp = "", programmingBlocksAndImport_temp = "",
                    htvm_trueFalseGlobalNull_temp = "", htvm_comment_temp = "", htvm_commentOpen1_temp = "",
                    htvm_commentClose2_temp = "";
                
                const lines = allKeyWordsOut3.split(/[\n\r]+/);

                if (lines.length > 0) {
                    const commandLine = lines[0];
                    commandLine.split(/[|,]/).forEach(cmd => {
                        const trimmedCmd = cmd.trim();
                        if (trimmedCmd) builtInCommands_temp += trimmedCmd + "|";
                    });
                }

                lines.forEach((A_LoopField3, A_Index3) => {
                    const trimmedLine = Trim(A_LoopField3);
                    if (trimmedLine) {
                        const originalLineNum = A_Index3 + 3 - 1;
                        if (originalLineNum >= 9 && originalLineNum <= 45) {
                            programmingBlocksAndImport_temp += trimmedLine + "|";
                        } else if ([48, 49, 50, 99].includes(originalLineNum)) {
                            htvm_trueFalseGlobalNull_temp += trimmedLine + "|";
                        } else if (originalLineNum >= 51 && originalLineNum <= 65) {
                            staticTypes_temp += trimmedLine + "|";
                        } else if (originalLineNum >= 66 && originalLineNum <= 68) {
                            htvmKeywords_temp += trimmedLine + "|";
                        } else if (originalLineNum >= 69 && originalLineNum <= 83) {
                            htvmKeywords_temp += trimmedLine + "|";
                        } else if (originalLineNum >= 3 & originalLineNum <= 7) {
                            htvmKeywords_temp += trimmedLine + "|";
                        } else if (originalLineNum >= 84 && originalLineNum <= 89) {
                            arrayMethods_temp += Trim(StrReplace(trimmedLine, ".", "")) + "|";
                        } else if (originalLineNum >= 90 && originalLineNum <= 94) {
                            staticTypes_temp += trimmedLine + "|";
                        } else if (originalLineNum >= 95 && originalLineNum <= 98) {
                            htvmKeywords_temp += trimmedLine + "|";
                        } else if (originalLineNum === 100) {
                            htvm_comment_temp = trimmedLine;
                        } else if (originalLineNum === 101) {
                            htvm_commentOpen1_temp = trimmedLine;
                        } else if (originalLineNum === 102) {
                            htvm_commentClose2_temp = trimmedLine;
                        } else if ((originalLineNum >= 106 && originalLineNum <= 142) || [143, 144].includes(originalLineNum)) {
                            if (/^[a-zA-Z_][a-zA-Z0-9_]*$/.test(trimmedLine)) {
                                word_operators_temp += trimmedLine + "|";
                            } else {
                                symbol_operators_temp += trimmedLine + "|";
                            }
                        } else if ([8, 147, 148].includes(originalLineNum)) {
                            builtInVars_temp += trimmedLine + "|"
                        }
                    }
                });

                const cleanAndBuild = (str, boundary = true) => { const p = str.split('|').filter(Boolean).map(s => s.trim().replace(/[.*+?^${}()|[\]\\]/g, '\\$&')); return p.length ? (boundary ? `\\b(?:${p.join('|')})\\b` : `(?:${p.join('|')})`) : "(?!)"; };
                const cleanAndBuildComma = (str) => { const p = str.split('|').filter(Boolean).map(s => s.trim().replace(/[.*+?^${}()|[\]\\]/g, '\\$&')); return p.length ? `\\b(?:${p.join('|')})(?=,)` : "(?!)"; };
                
                const final_word_operators = cleanAndBuild(word_operators_temp, true);
                const final_symbol_operators = cleanAndBuild(symbol_operators_temp, false);

                const gui_option_tokens1 = ["i", "v", "id", "elementId", "eid", "p", "parentId", "pid", "divId", "x", "xPos", "xCoord", "y", "yPos", "yCoord", "w", "width", "wight", "widh", "h", "height", "hight", "heigth", "z", "zIndex", "z-index", "d", "value", "val", "displayValue", "q", "placeholder", "plc", "ph", "grayText", "g", "f", "callback", "func", "fn", "call", "o", "backgroundColor", "bgColor", "bg", "bgc", "c", "color", "clr", "r", "rounding", "round", "rnd", "b", "border", "boder", "outline", "l", "rawCss", "css", "style", "luxury", "s", "size", "sz", "a", "isEnabled", "isEnb", "u", "isVisible", "isVsb", "n", "isDeleting", "del", "remove", "rm"];
                const gui_option_tokens2 = ["button", "text", "edit", "picture", "toggle", "rectangle", "circle", "video", "dropdown", "iframe"];
                const gui_option_pattern1 = gui_option_tokens1.map(gui_option_toCaseInsensitivePattern).join('|');
                const gui_option_pattern2 = gui_option_tokens2.map(gui_option_toCaseInsensitivePattern).join('|');
                const regexGuiOptions = new RegExp(`\\b(?:${gui_option_pattern1})(?=:)|\\b(?:${gui_option_pattern2})\\b`);

                this.$rules = {
                    start: [
                        { token: "comment", regex: (htvm_comment_temp.replace(/[.*+?^${}()|[\]\\]/g, '\\$&') || ";") + ".*$" },
                        { token: "comment.block", regex: htvm_commentOpen1_temp.replace(/[.*+?^${}()|[\]\\]/g, '\\$&') || "/\\*", next: "comment_block" },
                        { token: "string", regex: '".*?"' },
                        { token: "string", regex: "'.*?'" },
                        { token: "constant.numeric", regex: "\\b-?[0-9]+(?:\\.[0-9]+)?\\b" },
                        { token: "functions", regex: cleanAndBuild(allFunctionNamesString3) + "(?=\\()" },
                        { token: "keyword", regex: cleanAndBuild(htvmKeywords_temp) + "|\\bsubout\\b|\\bwhen\\b|\\bwehn\\b" },
                        { token: "BuildInFunc", regex: cleanAndBuild(builtInVars_temp) },
                        { token: "command", regex: cleanAndBuildComma(builtInCommands_temp) + "|\\bendpoint(?=,)\\b|\\bfileinit(?=,)\\b|\\bport(?=,)\\b" },
                        { token: "arrayMethods", regex: "\\." + cleanAndBuild(arrayMethods_temp) },
                        { token: "static_types", regex: cleanAndBuild(staticTypes_temp) + "|" + "\\b(?:" + "[Gg][Uu][Ii]" + "|" + "[Gg][Uu][Ii][Cc][Oo][Nn][Tt][Rr][Oo][Ll]" + ")\\b" },
                        { token: "programmingBlocksAndImport", regex: cleanAndBuild(programmingBlocksAndImport_temp) },
                        { token: "trueANDfalse", regex: cleanAndBuild(htvm_trueFalseGlobalNull_temp) },
                        { token: "guiOptions", regex: regexGuiOptions },
                        { token: "operators", regex: final_word_operators }
                    ],
                    comment_block: [{ token: "comment.block", regex: (htvm_commentClose2_temp.replace(/[.*+?^${}()|[\]\\]/g, '\\$&') || "\\*/"), next: "start" }, { defaultToken: "comment.block" }]
                };

                // Use an async IIFE to fetch the setting and add the rule.
                // This is a bit of a hack but necessary because the constructor is synchronous.
                (async () => {
                    const highlightOperators = await dbGet('highlightSymbolOperators');
                    if (highlightOperators !== false) {
                        this.$rules.start.push({ token: "operators", regex: final_symbol_operators });
                    }
                })();
            };
            oop.inherits(HTVMHighlightRules, TextHighlightRules);
            var Mode = function() { this.HighlightRules = HTVMHighlightRules; this.$behaviour = this.$defaultBehaviour; };
            oop.inherits(Mode, TextMode);
            exports.Mode = Mode;
        });
    }
    window.initializeHtvmMode = initializeHtvmMode;
})();