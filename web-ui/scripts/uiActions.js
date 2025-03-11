import { getConfig, changeConfig } from './storage.js'
import { debounce } from './utils.js';


function reorganizeBoxes() {
    const container = document.querySelector(".container");
    const boxes = Array.from(document.querySelectorAll(".settings-container"));
    if (!container || !boxes.length) return;
    
    const containerWidth = container.clientWidth;
    const boxWidth = boxes[0].clientWidth;
    console.log(containerWidth)
    console.log(boxWidth)
    
    const columns = Math.max(1, Math.floor(containerWidth / (boxWidth +15)));
    container.innerHTML = '';
    
    const columnElements = Array.from({ length: columns }, () => {
        const column = document.createElement("div");
        column.className = "setting-column";
        return column;
    });
    
    boxes.forEach((box, index) => {
        const columnIndex = index % columns;
        columnElements[columnIndex].appendChild(box);
    });
    
    columnElements.forEach(column => container.appendChild(column));
};

function registerMenu(){
    const  langMenu = document.querySelector("#lang-menu")
    if (document.hideMenuListener) return
    document.addEventListener("click", (event) => {
        if (!langMenu.contains(event.target) && !event.target.classList.contains("menu-button")) {
            langMenu.style.display = "none";
        }
    });
    document.hideMenuListener = true;


    const emojiPicker = document.querySelector("emoji-picker")
    emojiPicker.addEventListener('emoji-click', event => {
        const targetLang = langMenu.getAttribute("data-target-lang")
        const targetElement = document.querySelector("#" + targetLang + "_tab_bt" + " .lang-icon")
        targetElement.innerText = event.detail.unicode
        changeConfig(targetLang, {icon: event.detail.unicode})

      });

    langMenu.querySelector("#rename-bt").addEventListener("click", ()=>{
        const targetLang = langMenu.getAttribute("data-target-lang")
        const targetElement = document.querySelector("#" + targetLang + "_tab_bt")
        const targetNameElement = targetElement.querySelector(".lang-title")
        targetNameElement.contentEditable = true


        const range = document.createRange();
        const selection = window.getSelection();
        selection.removeAllRanges();
        range.selectNodeContents(targetNameElement);
        selection.addRange(range);


        targetNameElement.focus()
        langMenu.style.display = "none";
        console.log(targetElement)

        targetNameElement.addEventListener("focusout", ()=>{
            targetNameElement.contentEditable = false
            changeConfig(targetLang, {name: targetNameElement.innerText.replace(/[\r\n]+/g, ' ')})

        })

    })

    langMenu.querySelector("#set-icon-bt").addEventListener("click", ()=>{
        const emojiPickerContainer = document.querySelector(".emoji-picker")
        emojiPickerContainer.style.display = "flex"

        document.querySelector(".color-picker").style.display = "none"
    })

    langMenu.querySelector("#set-color-bt").addEventListener("click", ()=>{
        document.querySelector(".color-picker").style.display = "block"
        document.querySelector(".emoji-picker").style.display = "none"
        const colorInput = document.querySelector("#color-picker")
        setTimeout(()=>colorInput.click(), 100)
        
    })

    const setColor = debounce((lang, color)=>{
        changeConfig(lang, {color: color})
    }, 1000)
    
    document.querySelector("#color-picker").addEventListener("input", (event)=>{
        const targetLang = langMenu.getAttribute("data-target-lang")
        document.querySelector("#" + targetLang + "_tab_bt").style.backgroundColor = event.target.value
        setColor(targetLang, event.target.value)

    })
}

function applyConfig(){
    const langConfigs = getConfig()
    const langElms = document.querySelectorAll(".lang-item:not(.display-none)")
    langElms.forEach((elm)=>{
        const elmConfig = langConfigs[elm.getAttribute("data-lang-key")]
        elm.style.backgroundColor  = elmConfig.color
        // console.log(elm)
        elm.querySelector(".lang-icon").innerText = elmConfig.icon
        elm.querySelector(".lang-title").innerText = elmConfig.name

    })
}

export {applyConfig, registerMenu, reorganizeBoxes}