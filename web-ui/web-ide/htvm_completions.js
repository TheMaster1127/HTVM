// htvm_completions.js
'use strict';

(function() {
    let htvmKeywordCompletions = [];

    function parseHtvmInstructions(allKeyWordsIn) {
        if (!Array.isArray(allKeyWordsIn)) allKeyWordsIn = [];
        
        const keywords = new Set();

        allKeyWordsIn.forEach((line, index) => {
            const trimmedLine = line.trim();
            if (!trimmedLine) return;

            if (index === 2) {
                const commandGroups = trimmedLine.split('|');
                commandGroups.forEach(group => {
                    const firstCommand = group.split(',')[0].trim();
                    if (firstCommand) keywords.add(firstCommand.replace(/^\./, ''));
                });
                return;
            }

            if (index > 2 && index < 162) {
                if (index === 146 || index >= 149) return;
                if (trimmedLine && !/[[\]]/.test(trimmedLine)) {
                    keywords.add(trimmedLine.replace(/^\./, ''));
                }
            }

            if (index >= 162) {
                if (trimmedLine.startsWith("name:")) {
                    const descLine = allKeyWordsIn[index + 2]?.trim() || "";
                    const isDescriptionNull = descLine.toLowerCase() === "description: null";

                    if (!isDescriptionNull) {
                        const funcNamesLine = trimmedLine.substring(5).trim();
                        const funcNames = funcNamesLine.split(',').map(f => f.trim()).filter(Boolean);
                        funcNames.forEach(name => keywords.add(name.replace(/^\./, '')));
                    }
                }
            }
        });

        return Array.from(keywords).map(name => ({ caption: name, value: name, meta: "htvm" }));
    }

    // --- FIX: This function now accepts the instruction content directly ---
    async function initializeCompleters(id, editorInstance, instructionContent = "") {
        const htvmInstructions = instructionContent.split('\n');
        
        htvmKeywordCompletions = parseHtvmInstructions(htvmInstructions);

        const hardcodedHtvmWords = ["endpoint", "fileinit", "subout", "when", "port", "gui", "A_Input", "A_Id", "A_Event", "A_Value", "elementId", "parentId", "divId", "xPos", "xCoord", "yPos", "yCoord", "width", "wight", "widh", "height", "hight", "heigth", "zIndex", "z-index", "value", "displayValue", "placeholder", "grayText", "callback", "func", "call", "backgroundColor", "bgColor", "color", "clr", "rounding", "round", "rnd", "border", "boder", "outline", "rawCss", "style", "luxury", "size", "isEnabled", "isEnb", "isVisible", "isVsb", "isDeleting", "remove", "button", "text", "edit", "picture", "toggle", "rectangle", "circle", "video", "dropdown", "iframe"];

        hardcodedHtvmWords.forEach(word => {
            htvmKeywordCompletions.push({ caption: word, value: word, meta: "htvm" });
        });

        window.LanguageCompleter = {
            getCompletions: async function (editor, session, pos, prefix, callback) {
                // Master switch for autocomplete
                if (await dbGet('autocomplete-master') === false) {
                    callback(null, []);
                    return;
                }
                
                let completions = [];
                const mode = session.getMode().$id.split('/').pop();
                
                if (await dbGet('autocomplete-keywords') !== false) {
                    if (mode === 'htvm') {
                        completions.push(...htvmKeywordCompletions);
                    } else {
                        // For other languages, load from localStorage (this is fine, as it's not workspace-specific)
                        const langKeywords = JSON.parse(localStorage.getItem(`lang_completions_${mode}`) || '[]');
                        if (Array.isArray(langKeywords)) {
                            const langCompletions = langKeywords.map(word => ({
                                caption: word, value: word, meta: mode
                            }));
                            completions.push(...langCompletions);
                        }
                    }
                }
                
                if (await dbGet('autocomplete-local') !== false) {
                    const userWords = session.getValue().match(/\.?[a-zA-Z_][a-zA-Z0-9_]*/g) || [];
                    const userCompletions = [...new Set(userWords)].map(word => ({
                        caption: word, value: word, meta: "local"
                    }));
                    completions.push(...userCompletions);
                }
                
                const allCompletions = completions.filter((v, i, a) => a.findIndex(t => t.value === v.value) === i);

                if (prefix.length === 0) {
                    callback(null, allCompletions);
                    return;
                }
                const prefixLower = prefix.toLowerCase();
                const filtered = allCompletions.filter(c => c.value.toLowerCase().startsWith(prefixLower));
                callback(null, filtered);
            }
        };

        if (editorInstance) {
            const langTools = ace.require("ace/ext/language_tools");
            langTools.setCompleters([window.LanguageCompleter, langTools.snippetCompleter]);
        }
    }
    
    window.initializeCompleters = initializeCompleters;
})();