import { settings_data } from "./globs.js";

function createDefault(localStorageKey=window.lang_ID_str){
    let settingsArray = new Array(161).fill(null);
    for(let i = 0; i <= 8; i++){
        const g = settings_data.groups[i]
        g.items.forEach(s => {
            settingsArray[s.id] = s.default
        })
    }
    localStorage.setItem(localStorageKey, JSON.stringify(settingsArray));
    changeConfig(localStorageKey, {})
}

const chanegVal = function (id, value){
    if (!localStorage.getItem(window.lang_ID_str)) {
        createDefault()
    }
    // console.log(window.lang_ID_str)
    let storedArray = getConfigFromLocalStorage();
    // console.log(`changing ${id}  ${storedArray[id]}  ->   ${value}`)
    storedArray[id] = typeof value === 'string' ? value.trim() : value;
    localStorage.setItem(window.lang_ID_str, JSON.stringify(storedArray));
    // notyf.success('succefuly saved (:');
}

function getConfigFromLocalStorage(langIDString=window.lang_ID_str){
    return JSON.parse(localStorage.getItem(langIDString));
}

function getLangList(){
    return Object.keys(localStorage).filter(key => key.match(/^htvm_lang_\d+$/))
        .sort( (a, b) => parseInt(a.match(/\d+$/)[0]) - parseInt(b.match(/\d+$/)[0]) )
}

function getLangIDList(){
    return Object.keys(localStorage).filter(key => key.match(/^htvm_lang_\d+$/))
        .map(key => parseInt(key.match(/\d+$/)[0]))
}

function getConfig(){
    return JSON.parse(localStorage.getItem("langSettings"));
}

function changeConfig(lang, conf = {}) {
    let langConfigs = getConfig();
    if (!langConfigs) {
        localStorage.setItem("langSettings", JSON.stringify({}));
        langConfigs = getConfig();
    }
    if (!(lang in langConfigs)) {
        langConfigs[lang] = {
            color: "#fafafa",
            name: lang,
            icon: "🧾"
        };
    }
    Object.assign(langConfigs[lang], conf);
    localStorage.setItem("langSettings", JSON.stringify(langConfigs));
}

// --- NEW FUNCTION TO DELETE A LANGUAGE ---
function deleteLang(langKey) {
    const langID = parseInt(langKey.match(/\d+$/)[0]);

    // 1. Remove the main language settings
    localStorage.removeItem(langKey);

    // 2. Remove the config from langSettings
    let langConfigs = getConfig();
    if (langConfigs && langConfigs[langKey]) {
        delete langConfigs[langKey];
        localStorage.setItem("langSettings", JSON.stringify(langConfigs));
    }

    // 3. Remove the IDE downloaded flag
    localStorage.removeItem(`htvm_ide_downloaded_${langID}`);

    // 4. If this was the last accessed tab, clear that too
    if (getLastOpenedTab() == langID) {
        localStorage.removeItem("HTVM_LastAccesedTab");
    }
}
// ---

function setLastOpenedTab(langID){
    localStorage.setItem("HTVM_LastAccesedTab", langID);
}
function getLastOpenedTab(){
    return localStorage.getItem("HTVM_LastAccesedTab");
}

export {createDefault, chanegVal, getConfigFromLocalStorage, getLangIDList, getLangList, getConfig, changeConfig, deleteLang, setLastOpenedTab, getLastOpenedTab}