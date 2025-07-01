import { getLangList, getLangIDList, createDefault, setLastOpenedTab, changeConfig } from './storage.js'
import { applyConfig } from './uiActions.js'
import { drawSettings } from './settingWindows.js'
import { isOutOfView } from './utils.js'
import { handle_keys } from './search.js'

function switchLang(langID, newName) {
    if (!langID) langID = Math.max(...(getLangIDList().length ? getLangIDList() : [0])) + 1;
    let localStorageKey = "htvm_lang_" + langID
    window.lang_ID_str = localStorageKey
    window.lang_ID = langID
    if (!localStorage.getItem(localStorageKey)) {
        createDefault(localStorageKey);
        if (newName) {
            changeConfig(localStorageKey, { name: newName });
        }
    }
    drawSettings()
    createLangTabs() // This will now auto-scroll
    setLastOpenedTab(langID)
    const newTab = document.querySelector("#" + localStorageKey + "_tab_bt");
    if (newTab) {
        newTab.querySelector(".active-lang").style.visibility = "visible"
    }
    document.querySelectorAll(".setting-i input, .setting-i textarea").forEach(el => el.addEventListener("keydown", handle_keys))
}

function createLangTabs() {
    document.querySelectorAll(".lang-item:not(.display-none)").forEach(elm => {
        elm.remove()
    })
    const langContainer = document.querySelector(".lang-container");
    getLangList().forEach(lang => {
        changeConfig(lang) // Ensures config exists before applying it
        let langItem = document.querySelector(".lang-item.display-none").cloneNode(true)
        let langMenu = document.querySelector("#lang-menu")
        langItem.classList.remove("display-none")



        const langID = parseInt(lang.match(/\d+$/)[0])
        langItem.addEventListener("click", function () {
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
            if (isOutOfView(langMenu)) {
                langMenu.style.top = `${rect.bottom - langMenu.clientHeight}px`;
                langMenu.querySelector(".buttons").style.alignSelf = "flex-end"
            }
        });
        langContainer.append(langItem)
    })
    applyConfig()

    // --- AUTO-SCROLL LOGIC ---
    if(langContainer.lastElementChild){
        langContainer.lastElementChild.scrollIntoView({ behavior: 'smooth', block: 'end' });
    }
}

export { switchLang, createLangTabs }