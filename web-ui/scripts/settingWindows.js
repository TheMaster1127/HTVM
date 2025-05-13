import { getConfigFromLocalStorage, chanegVal } from "./storage.js";
import { settings_data } from "./globs.js";
import { reorganizeBoxes } from "./uiActions.js";
import { getSpeed } from "./utils.js";
import { createInfoBoxes } from "./info.js";

function createSettingBox(title, config) {
    let box = window.settingBox.cloneNode(true)
    box.querySelector(".title p").innerText = title;
    const localSettings = getConfigFromLocalStorage()

    config.forEach(s => {
        const settingID = s.id
        let option = settingOtion.cloneNode(true)

        const type = s.type ?? "text"

        option.querySelector(".setting-name").innerText = s.name


        if (type == "toggle") {
            // const settingI = option.querySelector(".setting-i")
            option.querySelector(".text-input").remove()

            option.id = "sw-" + settingID
            // option.querySelector("input").checked = s.default == 'on' ? true : false;
            console.log(localSettings[settingID])
            option.querySelector("input").checked = localSettings[settingID] == 'on' ? true : false;
            option.querySelector("input").addEventListener("change", function () {
                chanegVal(settingID, this.checked ? "on" : "off")
                if (!this.checked) {
                    console.log(`11`)
                    s.onDisable.forEach(dep => {
                        const q = "#sw-" + (dep.id) + " input"
                        document.querySelector(q).checked = dep.action == 'on' ? true : false;
                        document.querySelector(q).dispatchEvent(new Event("change", { bubbles: true }));
                    })
                    return
                }
                if (s.dependencies) {
                    s.dependencies.forEach(dep => {
                        const q = "#sw-" + (dep.id) + " input"
                        document.querySelector(q).checked = dep.action == 'on' ? true : false;
                        document.querySelector(q).dispatchEvent(new Event("change", { bubbles: true }));
                    })
                }
            })

        } else {
            option.querySelector(".toggle-input").remove()
            option.querySelector("textarea").placeholder = s.default
            option.querySelector("textarea").value = localSettings[settingID] == s.default ? "" : localSettings[s.id]
            option.querySelector("textarea").addEventListener("input", function () {
                console.log()
                chanegVal(settingID, this.value == "" ? s.default : this.value)
            })
        }
        createInfoBoxes(option, s)
        option.setAttribute("data-name", s.name)
        option.setAttribute("data-id", settingID)
        box.querySelector(".settings").appendChild(option)
    });
    document.querySelector(".container").appendChild(box)
}

function movingText() {
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
            // el.animate()
            // el.innerHTML = "<marquee>" + el.innerText + "</marquee>"
        }
    });
}

function drawSettings() {
    document.querySelector(".container.fancyScroll").innerHTML = ""
    for (let i = 0; i <= 8; i++) {
        const g = settings_data.groups[i]
        createSettingBox(g.name, g.items)
    }

    $(".title").click(function () {
        $(this).parent().toggleClass("hidden");
    });

    reorganizeBoxes()
    reorganizeBoxes()
    movingText()
    document.querySelector('#preview-iframe').src = "web-ide/preview.html?id=" + lang_ID
}

export { createSettingBox, movingText, drawSettings }