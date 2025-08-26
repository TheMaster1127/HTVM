import { getLangList, getLangIDList, createDefault, setLastOpenedTab, changeConfig, getLastOpenedTab } from './storage.js'
import { applyConfig } from './uiActions.js'
import { drawSettings } from './settingWindows.js'
import { isOutOfView } from './utils.js'
import { handle_keys } from './search.js'

function switchLang(langID, newName) {
    const isCreatingNew = !langID && newName; // Flag for creating a new language
    let targetLangID = langID;

    // If no ID is provided, figure out what to do.
    if (!targetLangID) {
        const lastOpened = getLastOpenedTab();
        const existingIDs = getLangIDList();
        
        if (lastOpened && existingIDs.includes(parseInt(lastOpened))) {
            // If there's a valid last-opened tab, use it.
            targetLangID = lastOpened;
        } else if (existingIDs.length > 0) {
            // Otherwise, use the highest existing ID.
            targetLangID = Math.max(...existingIDs);
        } else {
            // If no languages exist at all, create a new one.
            targetLangID = 1;
        }
    }
    
    // If we're explicitly creating a new one.
    if (isCreatingNew) {
        targetLangID = Math.max(...(getLangIDList().length ? getLangIDList() : [0])) + 1;
    }

    let localStorageKey = "htvm_lang_" + targetLangID
    window.lang_ID_str = localStorageKey
    window.lang_ID = targetLangID
    
    if (!localStorage.getItem(localStorageKey)) {
        createDefault(localStorageKey);
        if (newName) {
            changeConfig(localStorageKey, { name: newName });
        }
    }

    drawSettings();
    createLangTabs(isCreatingNew, localStorageKey);
    setLastOpenedTab(targetLangID);

    const activeTab = document.querySelector("#" + localStorageKey + "_tab_bt");
    if (activeTab) {
        activeTab.querySelector(".active-lang").style.visibility = "visible";
    }

    document.querySelectorAll(".setting-i input, .setting-i textarea").forEach(el => el.addEventListener("keydown", handle_keys))
}

function createLangTabs(isCreatingNew = false, keyToScrollTo = null) {
    document.querySelectorAll(".lang-item:not(.display-none)").forEach(elm => {
        elm.remove()
    })
    const langContainer = document.querySelector(".lang-container");
    getLangList().forEach(lang => {
        changeConfig(lang) 
        let langItem = document.querySelector(".lang-item.display-none").cloneNode(true)
        let langMenu = document.querySelector("#lang-menu")
        langItem.classList.remove("display-none")



        const langID = parseInt(lang.match(/\d+$/)[0])
        langItem.addEventListener("click", function () {
            switchLang(langID)
        })

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

    let elementToScrollTo;
    if (isCreatingNew && langContainer.lastElementChild) {
        elementToScrollTo = langContainer.lastElementChild;
    } else if (keyToScrollTo) {
        elementToScrollTo = document.querySelector(`#${keyToScrollTo}_tab_bt`);
    }

    if (elementToScrollTo) {
        elementToScrollTo.scrollIntoView({ behavior: 'smooth', block: 'nearest' });
    }
}

export { switchLang, createLangTabs }