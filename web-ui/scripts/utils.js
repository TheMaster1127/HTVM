function debounce(fn, delay) {
    let timer;
    return function (...args) {
        clearTimeout(timer);
        timer = setTimeout(() => fn(...args), delay);
    };
}

function getSpeed(max) {
    const duration = 190;
    return max / duration;
}

const isOutOfView = el => {
    const { top, bottom, left, right } = el.getBoundingClientRect();
    return top < 0 || bottom > window.innerHeight || left < 0 || right > window.innerWidth;
};

function noNewLines(){
    document.addEventListener("keydown", (event) => {
        if (event.key === "Enter") {
            event.preventDefault(); 
        }
    });
}

function checkPortraitMode() {
    if ($(window).height() > $(window).width()) {
        if (!/Mobi|Android|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent)) return

        $('body').hide()
        if ($("#portraitDiv").length === 0) {
            $('<div id="portraitDiv"></div>')
                .css({
                    'position': 'fixed',
                    'top': '0',
                    'left': '0',
                    'width': '100dvw',
                    'height': '100dvh',
                    'background-color': 'black',
                    'z-index': '9999'
                })
                .appendTo('html');
        }
    } else {
        $("#portraitDiv").remove();
        $('body').show()
    }
}

export {debounce, getSpeed, noNewLines, isOutOfView, checkPortraitMode}