import { settings_data } from './globs.js'
import { reorganizeBoxes, registerMenu } from './uiActions.js'
import { createLangTabs, switchLang } from './multiLang.js'
import { checkPortraitMode } from './utils.js'
import { search } from './search.js'

let doc
window.lang_ID_str = "htvm_lang_1"
window.lang_ID = 1

function init(){
    let src_settingBox = doc.querySelector(".settings-container")
    window.settingOtion = doc.querySelector(".setting").cloneNode(true);
    window.settingBox = src_settingBox.cloneNode(true);
    window.settingBox.querySelector(".settings").innerHTML = ""
    
    // document.querySelector("#search").addEventListener("input", search)
    
    if (/Mobi|Android|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent)) {
        $("#dropzone").text("Select HTVM instructions.txt")
    }
    
    $(window).on('resize', checkPortraitMode);

    $(".title").click(function () {
        $(this).parent().toggleClass("hidden");
    });

    $("#createLang").click(()=>{
        switchLang()
    })

    $(document).on('keydown', function(e) {
        if (e.key === '/' && !$('textarea').is(':focus')) {
            e.preventDefault()
            $('#search').focus(); 
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


    checkPortraitMode()
    reorganizeBoxes()
    reorganizeBoxes()
    createLangTabs()
    registerMenu()
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

