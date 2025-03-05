settings_data = {}
let settingOtion
let settingBox 
let doc
let lang_ID_str = "htvm_lang_1"
let lang_ID = 1

const notyf = new Notyf();

function createSettingBox(title, config, loading){
    box = settingBox.cloneNode(true)
    box.querySelector(".title p").innerText = title;
    const localSettings = getConfigFromLocalStorage()

    config.forEach(s => {
        const settingID = s.id - 1
        let option = settingOtion.cloneNode(true)

        type = s.type ?? "text"

        option.querySelector(".setting-name").innerText = s.name
        if(type == "toggle"){
            settingI = option.querySelector(".setting-i")
            option.querySelector(".text-input").remove()

            option.id = "sw-" + settingID
            // option.querySelector("input").checked = s.default == 'on' ? true : false;
            console.log(localSettings[settingID])
            option.querySelector("input").checked = localSettings[settingID] == 'on' ? true : false;
            option.querySelector("input").addEventListener("change", function (){
                chanegVal(settingID, this.checked ? "on" : "off")
                if (!this.checked) return
                if(s.dependencies){
                    s.dependencies.forEach(dep =>{
                        q = "#sw-"+ (dep.id - 1) + " input"
                        document.querySelector(q).checked = dep.action == 'on' ? true : false;
                        document.querySelector(q).dispatchEvent(new Event("change", { bubbles: true }));
                    })
                }
            })

        }else{
            option.querySelector(".toggle-input").remove()
            option.querySelector("textarea").placeholder = s.default
            option.querySelector("textarea").value = localSettings[settingID] == s.default ? "" : localSettings[s.id]
            option.querySelector("textarea").addEventListener("input",function (){
                console.log()
                chanegVal(settingID, this.value == "" ? s.default : this.value)
            })
        }
        option.setAttribute("data-name", s.name)
        option.setAttribute("data-id", settingID)
        box.querySelector(".settings").appendChild(option)
    });
    document.querySelector(".container").appendChild(box)
}

function createDefault(localStorageKey=lang_ID_str){
    settingsArray = new Array(162).fill(null);
    for(let i = 0; i <= 8; i++){
        g = settings_data.groups[i]
        g.items.forEach(s => {
            settingsArray[s.id - 1] = s.default
        })
    }
    localStorage.setItem(localStorageKey, JSON.stringify(settingsArray));
}


function init(){
    let src_settingBox = doc.querySelector(".settings-container")
    console.log(src_settingBox)

    
    settingOtion = doc.querySelector(".setting").cloneNode(true);
    settingBox = src_settingBox.cloneNode(true);
    settingBox.querySelector(".settings").innerHTML = ""


    // for(let i = 0; i <= 8; i++){
    //     g = settings_data.groups[i]
    //     createSettingBox(g.name, g.items)
    // }
    // switchLang(1)

    if (/Mobi|Android|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent)) {
        $("#dropzone").text("Select HTVM instructions.txt")
    }

    $(".title").click(function () {
        $(this).parent().toggleClass("hidden");
    });
    $("#createLang").click(()=>{
        $(".lang-item").clone().appendTo(".lang-container");
    })

    $(document).on('keydown', function(e) {
        if (e.key === '/' && !$('textarea').is(':focus')) {
            e.preventDefault()
            $('#search').focus(); // Focus on the search box
        }
    });

    $("#ide-bt").click(function  (){
        window.open('web-ide/?id=' + lang_ID, '_blank');
    })

    $("#preview-modal, #modal-preview-close-bt").click(function(){
        document.querySelector('#preview-iframe').src = "about:blank"
        document.querySelector('#preview-modal').close()
        $(".prewiew-loading-bg").removeClass("loading")
    })

    $("#preview-bt").click(function(){
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



    reorganizeBoxes()
    reorganizeBoxes()
    
}

function movingText(){
    document.querySelectorAll(".setting-name").forEach(el => {
        // const parent = el.parentElement;
        if (el.scrollWidth > el.clientWidth) {
            el.classList.add("overflowed");
            // el.setAttribute('data-content', el.textContent);
            // el.textContent = '_';

            const fontSize = parseFloat(getComputedStyle(el).fontSize);
            const text = el.textContent + " ";
            // const textWidth = text.length * fontSize * 0.4;
            const textWidth = el.scrollWidth + 5;
            el.style.setProperty('--text-width', textWidth + 'px');
            el.style.setProperty('--container-width', el.clientWidth + 'px');
            el.style.setProperty('--animation-speed', getSpeed(textWidth) + "s");
            // el.innerHTML = "<marquee>" + el.innerText + "</marquee>"
        } 
    });
}

function debounce(fn, delay) {
    let timer;
    return function (...args) {
        clearTimeout(timer);
        timer = setTimeout(() => fn(...args), delay);
    };
}

function getSpeed(max) {
    const duration = 190; // 5 seconds in milliseconds
    return max / duration;
}
  

const chanegVal = function (id, value){
    if (!localStorage.getItem(lang_ID_str)) {
        createDefault()
    }
    let storedArray = getConfigFromLocalStorage();
    console.log(`changing ${id}  ${storedArray[id]}  ->   ${value}`)
    storedArray[id] = value;
    localStorage.setItem(lang_ID_str, JSON.stringify(storedArray));
    // notyf.success('succefuly saved (:');
}

function getConfigFromLocalStorage(langIDString=lang_ID_str){
    return JSON.parse(localStorage.getItem(langIDString));
}

const search = debounce(function (term){
    document.querySelectorAll(".search-sel").forEach((e)=>{
        e.classList.remove("search-sel")
    })

    if(!term.target.value) return
    const sterm = CSS.escape( term.target.value.trim());
    matches = document.querySelectorAll(`[data-name*="${sterm}" i]`);
    if(matches.length <= 0) return
    matches[matches.length - 1].scrollIntoView({ behavior: "smooth", block: "center" })
    matches.forEach((match)=>{
       match.classList.add("search-sel")
    })
}, 500)
document.querySelector("#search").addEventListener("input", search)



function switchLang(langID){
    let localStorageKey = "htvm_lang_" + langID
    if (!localStorage.getItem(localStorageKey)) createDefault(localStorageKey)
    lang_ID = langID
    lang_ID_str = localStorageKey
    drawSettings(true)
}

function drawSettings(){
    document.querySelector(".container.fancyScroll").innerHTML = ""
    localSettings = getConfigFromLocalStorage()
    for(let i = 0; i <= 8; i++){
        g = settings_data.groups[i]
        createSettingBox(g.name, g.items, true)
    }
    
    // for(let i = 0; i <= 8; i++){
    //     g = settings_data.groups[i]
    //     createSettingBox(g.name, g.items)
    // }

    $(".title").click(function () {
        $(this).parent().toggleClass("hidden");
    });

    reorganizeBoxes()
    reorganizeBoxes()
    movingText()
    document.querySelector('#preview-iframe').src = "web-ide/preview.html?id=" + lang_ID
}



fetch('assets/settings.json') 
  .then(response => response.json())
  .then(jsonData => {
        settings_data = jsonData
        fetch("assets/settings.html")
            .then(response => response.text())
            .then(data => {
                let parser = new DOMParser();
                doc = parser.parseFromString(data, "text/html");
                init()

            });
  })
  .catch(error => console.error('Error fetching JSON:', error));

