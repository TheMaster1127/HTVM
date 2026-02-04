import { getConfig, changeConfig, deleteLang } from './storage.js'
import { debounce } from './utils.js';
import { switchLang } from './multiLang.js';


function reorganizeBoxes() {
    const container = document.querySelector(".container");
    const boxes = Array.from(document.querySelectorAll(".settings-container"));
    if (!container || !boxes.length) return;
    
    const containerWidth = container.clientWidth;
    const boxWidth = boxes[0]?.clientWidth ?? 320; 
    
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
    document.getElementById("sw-5")?.remove();
    document.getElementById("sw-8")?.remove();
    document.getElementById("sw-155")?.remove();
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
        langMenu.style.display = "none";
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
        const menuRect = langMenu.getBoundingClientRect();
        
        emojiPickerContainer.style.display = "flex"
        emojiPickerContainer.style.top = `${menuRect.top}px`;
        emojiPickerContainer.style.left = `${menuRect.right + 5}px`;

        const pickerRect = emojiPickerContainer.getBoundingClientRect();
        if (pickerRect.bottom > window.innerHeight) {
            emojiPickerContainer.style.top = `${window.innerHeight - pickerRect.height - 5}px`
        }


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

    });

    // --- START: CORRECT DELETE CONFIRMATION LOGIC ---
    const deleteModal = document.getElementById('delete-lang-modal-overlay');
    const deleteConfirmBtn = document.getElementById('delete-lang-confirm-btn');
    const deleteCancelBtn = document.getElementById('delete-lang-cancel-btn');

    // This listener shows the modal
    langMenu.querySelector("#delete-bt").addEventListener("click", () => {
        const langToDelete = langMenu.getAttribute("data-target-lang");
        deleteModal.setAttribute('data-lang-to-delete', langToDelete);
        langMenu.style.display = "none";
        deleteModal.style.display = 'flex';
    });

    // This listener handles the "Cancel" button inside the modal
    deleteCancelBtn.addEventListener('click', () => {
        deleteModal.style.display = 'none';
        deleteModal.removeAttribute('data-lang-to-delete');
    });

    // This listener handles the final "Delete" action
    deleteConfirmBtn.addEventListener('click', () => {
        const langToDelete = deleteModal.getAttribute('data-lang-to-delete');
        if (langToDelete) {
            deleteLang(langToDelete); // Call the new delete function from storage
            deleteModal.style.display = 'none';
            switchLang(null); // Re-initialize the view, will switch to highest available ID or create new one
            deleteModal.removeAttribute('data-lang-to-delete');
        }
    });
    // --- END: CORRECT DELETE CONFIRMATION LOGIC ---
}

function applyConfig(){
    const langConfigs = getConfig()
    const langElms = document.querySelectorAll(".lang-item:not(.display-none)")
    langElms.forEach((elm)=>{
        const elmConfig = langConfigs[elm.getAttribute("data-lang-key")]
        elm.style.backgroundColor  = elmConfig.color
        elm.querySelector(".lang-icon").innerText = elmConfig.icon
        elm.querySelector(".lang-title").innerText = elmConfig.name

    })
}


export {applyConfig, registerMenu, reorganizeBoxes}
