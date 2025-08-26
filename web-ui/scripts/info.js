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
    wrapper.style.position = 'fixed'; // Use fixed positioning for viewport-relative calcs

    infoBox.querySelector('.head').innerText = config?.description?.header ?? "To be defined"
    infoBox.querySelector('.body').innerHTML = marked.parse(config?.description?.body ?? "**To be defined**")


    infoButton.addEventListener('mouseenter', () => {
        // Remove any other temporary info boxes first
        document.querySelectorAll('.info-box-temp').forEach((el) => {
            el.remove();
        });

        wrapper.classList.add('info-box-temp');
        document.body.appendChild(wrapper);

        const rect = infoButton.getBoundingClientRect();
        const boxRect = wrapper.getBoundingClientRect();
        const windowWidth = window.innerWidth;
        const windowHeight = window.innerHeight;

        let top = rect.bottom + 5;
        let left = rect.left;

        // Check horizontal overflow
        if (left + boxRect.width > windowWidth) {
            left = rect.right - boxRect.width;
        }

        // Check vertical overflow
        if (top + boxRect.height > windowHeight) {
            top = rect.top - boxRect.height - 5;
        }
        
        // Ensure it doesn't go off-screen top/left either
        if (top < 0) top = 5;
        if (left < 0) left = 5;

        wrapper.style.top = `${top}px`;
        wrapper.style.left = `${left}px`;
    });
    
    // Use mouseleave on both the button and the box itself for a smoother experience
    infoButton.addEventListener('mouseleave', () => {
        // Set a small delay to allow the mouse to move into the infobox
        setTimeout(() => {
            if (!wrapper.matches(':hover')) {
                if (wrapper.parentElement) {
                    document.body.removeChild(wrapper);
                }
            }
        }, 100);
    });

    wrapper.addEventListener('mouseleave', () => {
        if (wrapper.parentElement) {
            document.body.removeChild(wrapper);
        }
    });
}


export { createInfoBoxes }