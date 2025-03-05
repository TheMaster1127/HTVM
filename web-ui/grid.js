fetch("assets/settings.html")
    .then(response => response.text())
    .then(data => {
        // let parser = new DOMParser();
        // let doc = parser.parseFromString(data, "text/html");
        // let src_settingBox = doc.querySelector(".settings-container")
        // let src_setting = doc.querySelector(".setting").cloneNode(true);

        let columns = 1
        let count = 0
        // for(let i = 0; i < columns; i++){
        //     // console.log(columns)
        //     let settingColumn = document.createElement("div")
        //     settingColumn.className = "setting-column"

        //     options =  Math.floor(Math.random() * (5 - 1) + 1)
        //     for(let j = 0; j < options; j++){
        //         let settingBox = src_settingBox.cloneNode(true);
        //         settingBox.querySelector(".title p").innerText = "Sec " + count;
        //         s = Math.floor(Math.random() * (5 - 1) + 1)
        //         for(let k = 0; k < s; k++){
        //             let setting = src_setting.cloneNode(true);
        //             settingBox.querySelector(".settings").appendChild(setting)
        //         }
        //         settingColumn.appendChild(settingBox)
        //         count++
        //     }
        //     document.querySelector(".container").appendChild(settingColumn);
        //     columns = Math.max(1, Math.floor(document.querySelector(".container").clientWidth / (settingColumn.clientWidth + 15)))
        // }


        // $(".settings-container").draggable({
        //     containment: ".container",
        //     handle: ".settings"
        // });


    });



function debounce(func, wait) {
    let timeout;
    return function() {
        clearTimeout(timeout);
        timeout = setTimeout(() => func.apply(this, arguments), wait);
    };
}

const reorganizeBoxes = () => {
    const container = document.querySelector(".container");
    const boxes = Array.from(document.querySelectorAll(".settings-container"));
    if (!container || !boxes.length) return;
    
    // Get widths after ensuring elements exist
    const containerWidth = container.clientWidth;
    const boxWidth = boxes[0].clientWidth;
    console.log(containerWidth)
    console.log(boxWidth)
    
    // Calculate number of columns, ensuring at least 1
    const columns = Math.max(1, Math.floor(containerWidth / (boxWidth +15)));
    
    // Clear existing columns
    container.innerHTML = '';
    
    // Create array of column elements
    const columnElements = Array.from({ length: columns }, () => {
        const column = document.createElement("div");
        column.className = "setting-column";
        return column;
    });
    
    // Distribute boxes among columns more evenly
    boxes.forEach((box, index) => {
        const columnIndex = index % columns;
        columnElements[columnIndex].appendChild(box);
    });
    
    // Append all columns to container
    columnElements.forEach(column => container.appendChild(column));
};
    
    // Add debounced event listener
    window.addEventListener("resize", debounce(reorganizeBoxes, 250));
    