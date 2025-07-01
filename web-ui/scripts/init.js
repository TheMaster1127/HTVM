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
    if (errorString === "noERROR") {
        clearErrorHighlights(); 
        return true;
    }

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

function init(){
    let src_settingBox = doc.querySelector(".settings-container")
    window.settingOtion = doc.querySelector(".setting").cloneNode(true);
    window.settingBox = src_settingBox.cloneNode(true);
    window.settingBox.querySelector(".settings").innerHTML = ""
    
    // --- START: DRAG AND DROP & MOBILE UPLOAD LOGIC ---
    const dropzone = document.getElementById('dropzone');
    const isMobile = /Mobi|Android|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent);

    function processFile(file) {
        if (file && file.name.endsWith('.txt')) {
            const reader = new FileReader();
            reader.onload = function(event) {
                const content = event.target.result;
                const lines = content.replace(/\r\n/g, '\n').split('\n');
                
                lines.forEach((line, index) => {
                    if (index < 161) {
                        chanegVal(index, line);
                    }
                });
                
                drawSettings();
                notyf.success('Instructions loaded successfully!');
            };
            reader.readAsText(file);
        } else {
            notyf.error('Invalid file type. Please select a .txt instruction file.');
        }
    }

    if (isMobile) {
        // On mobile, change text and make it a click-to-select area.
        const fileInput = document.createElement('input');
        fileInput.type = 'file';
        fileInput.style.display = 'none';
        fileInput.accept = '.txt';
        document.body.appendChild(fileInput);

        dropzone.querySelector('p').textContent = "Click to Select File";
        
        dropzone.addEventListener('click', () => {
            fileInput.click();
        });

        fileInput.addEventListener('change', (e) => {
            if (e.target.files.length) {
                processFile(e.target.files[0]);
            }
        });

    } else {
        // On desktop, add click-to-select to drag and drop functionality.
        const fileInput = document.createElement('input');
        fileInput.type = 'file';
        fileInput.style.display = 'none';
        fileInput.accept = '.txt';
        document.body.appendChild(fileInput);

        dropzone.addEventListener('click', () => {
            fileInput.click();
        });

        fileInput.addEventListener('change', (e) => {
            if (e.target.files.length) {
                processFile(e.target.files[0]);
            }
        });
        
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
                processFile(e.dataTransfer.files[0]);
            }
        });
    }
    // --- END: DRAG AND DROP & MOBILE UPLOAD LOGIC ---
    
    $(window).on('resize', checkPortraitMode);

    $(".title").click(function () {
        $(this).parent().toggleClass("hidden");
    });

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
            switchLang(null, newName);
            createLangModal.style.display = 'none';
            createLangInput.value = '';
        } else {
            notyf.error('Please enter a name for the language.');
        }
    });


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

    function hasIdeFileBeenDownloaded(id) {
        return localStorage.getItem(`htvm_ide_downloaded_${id}`) === 'true';
    }

    function markIdeFileAsDownloaded(id) {
        localStorage.setItem(`htvm_ide_downloaded_${id}`, 'true');
    }

    function hideIdeModal() {
        clearInterval(countdownInterval);
        ideModalOverlay.style.display = 'none';
        ideModalDownloadBtn.disabled = false;
        ideModalDownloadBtn.innerText = 'Download Instruction File';
        ideModalCountdown.innerText = '';
    }

    ideModalCloseBtn.addEventListener('click', hideIdeModal);

    $("#ide-bt").click(function() {
        clearErrorHighlights();
        if (!handleAndDisplayError(handleError(getUserConfig(lang_ID)))) return;
        
        if (hasIdeFileBeenDownloaded(lang_ID)) {
            window.open('web-ide/?id=' + lang_ID, '_blank');
        } else {
            ideModalOverlay.style.display = 'flex';
        }
    });

    ideModalDownloadBtn.addEventListener('click', async function() {
        const userConfig = getUserConfig(lang_ID);
        const builtins = await getBuiltins();
        const fullInstructions = userConfig + "\n" + builtins;

        saveAs(fullInstructions, 'HTVM-instructions.txt');
        markIdeFileAsDownloaded(lang_ID);

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
        clearErrorHighlights();
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
    else switchLang()
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