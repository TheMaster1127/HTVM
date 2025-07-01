import { settings_data } from './globs.js'
import { reorganizeBoxes, registerMenu } from './uiActions.js'
import { createLangTabs, switchLang } from './multiLang.js'
import { checkPortraitMode } from './utils.js'
import { search } from './search.js'
import { getLastOpenedTab, chanegVal, changeConfig } from './storage.js'
import { getUserConfig, getBuiltins, saveAs } from './builder/build.js';
import { drawSettings } from './settingWindows.js';

let doc
window.lang_ID_str = "htvm_lang_1"
window.lang_ID = 1

// --- START: ERROR HANDLING AND NOTIFICATION SETUP ---
const notyf = new Notyf({
    duration: 5000,
    position: { x: 'right', y: 'top' },
    types: [
        { type: 'error', background: '#ff4d4d', icon: false }
    ]
});

function clearErrorHighlights() {
    document.querySelectorAll('.error-highlight').forEach(el => {
        el.classList.remove('error-highlight');
    });
}

function handleAndDisplayError(errorString) {
    if (errorString === "noERROR") return true;

    clearErrorHighlights();

    const [id, message] = errorString.split('|');
    const errorElement = document.querySelector(`.setting[data-id="${id}"]`);

    if (errorElement) {
        errorElement.classList.add('error-highlight');
        errorElement.scrollIntoView({ behavior: 'smooth', block: 'center' });
    }

    notyf.error(`Error in setting ID ${id}: ${message}`);
    return false;
}
// --- END: ERROR HANDLING AND NOTIFICATION SETUP ---

function init(){
    let src_settingBox = doc.querySelector(".settings-container")
    window.settingOtion = doc.querySelector(".setting").cloneNode(true);
    window.settingBox = src_settingBox.cloneNode(true);
    window.settingBox.querySelector(".settings").innerHTML = ""
    
    // --- START: DRAG AND DROP LOGIC ---
    const dropzone = document.getElementById('dropzone');

    dropzone.addEventListener('dragover', (e) => {
        e.preventDefault();
        dropzone.style.borderColor = '#fe621b';
    });

    dropzone.addEventListener('dragleave', () => {
        dropzone.style.borderColor = 'rgb(151, 145, 145)';
    });

    dropzone.addEventListener('drop', (e) => {
        e.preventDefault();
        dropzone.style.borderColor = 'rgb(151, 145, 145)';

        if (e.dataTransfer.files.length) {
            const file = e.dataTransfer.files[0];
            if (file.name === 'HTVM-instructions.txt') {
                const reader = new FileReader();
                reader.onload = function(event) {
                    const content = event.target.result;
                    const lines = content.split('\n');
                    lines.forEach((line, index) => {
                        // Assuming line format is "value" and index is the ID
                        if (index < 161) { // Only process valid setting lines
                            chanegVal(index, line);
                        }
                    });
                    // Refresh UI with loaded settings
                    drawSettings();
                    notyf.success('Instructions loaded successfully!');
                };
                reader.readAsText(file);
            } else {
                notyf.error('Invalid file. Please drop HTVM-instructions.txt');
            }
        }
    });
    // --- END: DRAG AND DROP LOGIC ---
    
    if (/Mobi|Android|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent)) {
        $("#dropzone").text("Select HTVM instructions.txt")
    }
    
    $(window).on('resize', checkPortraitMode);

    $(".title").click(function () {
        $(this).parent().toggleClass("hidden");
    });

    // --- START: "CREATE LANGUAGE" MODAL LOGIC ---
    const createLangModal = document.getElementById('create-lang-modal-overlay');
    const createLangInput = document.getElementById('create-lang-input');
    const createLangConfirmBtn = document.getElementById('create-lang-confirm-btn');
    const createLangCancelBtn = document.getElementById('create-lang-cancel-btn');

    $("#createLang").click(()=>{
        createLangModal.style.display = 'flex';
        createLangInput.focus();
    });

    createLangCancelBtn.addEventListener('click', () => {
        createLangModal.style.display = 'none';
        createLangInput.value = '';
    });

    createLangConfirmBtn.addEventListener('click', () => {
        const newName = createLangInput.value.trim();
        if (newName) {
            switchLang(null, newName); // Pass name to be set on creation
            createLangModal.style.display = 'none';
            createLangInput.value = '';
        } else {
            notyf.error('Please enter a name for the language.');
        }
    });
    // --- END: "CREATE LANGUAGE" MODAL LOGIC ---


    $(document).on('keydown', function(e) {
        if (e.key === '/' && !$('textarea').is(':focus')) {
            e.preventDefault()
            $('#search').focus(); 
        }
    });
    
    const ideModalOverlay = document.getElementById('ide-modal-overlay');
    const ideModalCloseBtn = document.getElementById('ide-modal-close-btn');
    const ideModalDownloadBtn = document.getElementById('ide-modal-download-btn');
    const ideModalCountdown = document.getElementById('ide-modal-countdown');
    let countdownInterval;

    function hideIdeModal() {
        clearInterval(countdownInterval);
        ideModalOverlay.style.display = 'none';
        ideModalDownloadBtn.disabled = false;
        ideModalDownloadBtn.innerText = 'Download Instruction File';
        ideModalCountdown.innerText = '';
    }

    ideModalCloseBtn.addEventListener('click', hideIdeModal);

    $("#ide-bt").click(function() {
        if (!handleAndDisplayError(handleError(getUserConfig(lang_ID)))) return;
        
        ideModalOverlay.style.display = 'flex';
    });

    ideModalDownloadBtn.addEventListener('click', async function() {
        const userConfig = getUserConfig(lang_ID);
        const builtins = await getBuiltins();
        const fullInstructions = userConfig + "\n" + builtins;

        saveAs(fullInstructions, 'HTVM-instructions.txt');

        this.disabled = true;
        this.innerText = 'Downloaded!';
        
        let countdown = 3;
        ideModalCountdown.innerText = `Redirecting in ${countdown}...`;

        countdownInterval = setInterval(() => {
            countdown--;
            if (countdown > 0) {
                ideModalCountdown.innerText = `Redirecting in ${countdown}...`;
            } else {
                ideModalCountdown.innerText = 'Redirecting...';
                clearInterval(countdownInterval);
                window.open('web-ide/?id=' + lang_ID, '_blank');
                hideIdeModal();
            }
        }, 1000);
    });

    $("#preview-modal, #modal-preview-close-bt").click(function(){
        document.querySelector('#preview-iframe').src = "about:blank"
        document.querySelector('#preview-modal').close()
        $(".prewiew-loading-bg").removeClass("loading")
    })

    $("#preview-bt").click(function(){
        if (!handleAndDisplayError(handleError(getUserConfig(lang_ID)))) return;

        document.querySelector('#preview-modal').showModal()
        document.querySelector('#preview-iframe').src = "web-ide/preview.html?id=" + lang_ID
    })

    $(".preview-title-bar,.prewiew-loading-bg").click(function(event) {
        event.stopPropagation();
    });

    $("iframe").on("load", function() {
        var iframe = $(this)[0];
        if (iframe.contentWindow.document.readyState === "complete") {
            $(".prewiew-loading-bg").addClass("loading")
        } else {
            $(iframe.contentWindow).on("load", function() {
                $(".prewiew-loading-bg").addClass("loading")
            });
        }
    });


    checkPortraitMode()
    reorganizeBoxes()
    reorganizeBoxes()
    createLangTabs()
    registerMenu()
    if(getLastOpenedTab()) switchLang(getLastOpenedTab())
}

fetch('assets/settings.json') 
  .then(response => response.json())
  .then(jsonData => {
        Object.assign(settings_data, jsonData)
        fetch("assets/settings.html")
            .then(response => response.text())
            .then(data => {
                let parser = new DOMParser();
                doc = parser.parseFromString(data, "text/html");
                init()

            });
  })
  .catch(error => console.error('Error fetching JSON:', error));