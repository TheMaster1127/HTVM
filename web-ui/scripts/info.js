import { marked } from "https://cdn.jsdelivr.net/npm/marked/lib/marked.esm.js";

const infoBoxHTML = new DOMParser().parseFromString(
    await (await fetch('assets/infobox.html')).text(),
    'text/html'
);

function createInfoBoxes(setting, config) {
    const wrapper = document.createElement("div")
    const infoBox = wrapper.attachShadow({ mode: 'open' })
    infoBox.innerHTML = infoBoxHTML.body.innerHTML;
    const infoButton = setting.querySelector('.info-button');
    wrapper.style.zIndex = 1000;

    infoBox.querySelector('.head').innerText = config?.description?.header ?? "To be defined"
    infoBox.querySelector('.body').innerHTML = marked.parse(config?.description?.body ?? "**To be defined**")


    infoButton.addEventListener('mouseenter', () => {
        const rect = infoButton.getBoundingClientRect();
        const windowWidth = window.innerWidth;
        const wrapperWidth = wrapper.offsetWidth || 200;
        const rightSpace = windowWidth - rect.right;
        const hasEnoughRightSpace = rightSpace >= wrapperWidth;
        wrapper.classList.add('info-box-temp')
        wrapper.style.position = 'absolute';
        wrapper.style.top = `${rect.top}px`;

        document.querySelectorAll('.info-box-temp').forEach((el) => {
            el.remove();
        })

        if (hasEnoughRightSpace) {
            wrapper.style.left = `${rect.left}px`;
            wrapper.style.right = 'auto';
        } else {
            wrapper.style.left = 'auto';
            wrapper.style.right = `${windowWidth - rect.right}px`;
        }

        document.body.appendChild(wrapper);
    });
    wrapper.addEventListener('mouseleave', () => {
        document.body.removeChild(wrapper);
    });
}


export { createInfoBoxes }