import { getLangList, getLangIDList, createDefault } from './storage.js';
import { applyConfig } from './uiActions.js';
import { drawSettings } from './settingWindows.js';
import { isOutOfView } from './utils.js';


function switchLang(langID){
    if(!langID) langID = Math.max(...(getLangIDList().length ? getLangIDList() : [0])) + 1;    
    let localStorageKey = "htvm_lang_" + langID
    if (!localStorage.getItem(localStorageKey)) createDefault(localStorageKey)
    const lang_ID = langID
    const lang_ID_str = localStorageKey
    drawSettings()
    createLangTabs()
    document.querySelector("#" + localStorageKey + "_tab_bt .active-lang").style.visibility = "visible"
}

function createLangTabs(){
    document.querySelectorAll(".lang-item:not(.display-none)").forEach(elm=>{
        elm.remove()
    })
    getLangList().forEach(lang=>{
        let langItem = document.querySelector(".lang-item.display-none").cloneNode(true)
        let langMenu = document.querySelector("#lang-menu")
        langItem.classList.remove("display-none")
        
        
        
        const langID = parseInt(lang.match(/\d+$/)[0])
        langItem.addEventListener("click", function(){
            switchLang(langID)
        })

        // langItem.querySelector(".lang-title").innerText = lang
        langItem.setAttribute("data-lang-key", lang)
        langItem.setAttribute("id", lang + "_tab_bt")


        langItem.querySelector(".option-bt").addEventListener("click", (event) => {
            event.preventDefault()
            event.stopPropagation()
            document.querySelector(".emoji-picker").style.display = "none"
            document.querySelector(".color-picker").style.display = "none"
            langMenu.style.display = "flex";
            
            const rect = langItem.getBoundingClientRect();
            langMenu.style.left = `${rect.right}px`;
            langMenu.style.top = `${rect.bottom - 100}px`;
            langMenu.setAttribute("data-target-lang", lang);
            langMenu.querySelector(".buttons").style.alignSelf = "flex-start"
            if(isOutOfView(langMenu)){
                langMenu.style.top = `${rect.bottom - langMenu.clientHeight}px`;
                langMenu.querySelector(".buttons").style.alignSelf = "flex-end"
            }
        });
        document.querySelector(".lang-container").append(langItem)
    })
    applyConfig()
}

export {switchLang, createLangTabs}