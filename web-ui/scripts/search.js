import { debounce } from "./utils.js"

let searched_items = []
let search_index = -1

function clear(){
    searched_items = []
    search_index = -1

    document.querySelectorAll(".search-sel").forEach((e)=>{
        e.classList.remove("search-sel")
    })
}

const search = debounce(function (term){
    clear()
    if(!term.target.value) return
    const sterm = CSS.escape( term.target.value.trim());
    const matches = document.querySelectorAll(`[data-name*="${sterm}" i]`);
    if(matches.length <= 0) return
    searched_items = matches
    search_index = -1
    matches[0].scrollIntoView({ behavior: "smooth", block: "center" })
    matches.forEach((match)=>{
       match.classList.add("search-sel")
    })
}, 500)

function handle_keys(keyEvent){
    console.log(keyEvent.code)
    if(searched_items.length <= 0) return

    if(keyEvent.code == "Tab"){
        if(keyEvent.shiftKey) search_index--
        else search_index++
    }
  
    if (search_index == searched_items.length) search_index = 0
    if (search_index == -1) search_index = searched_items.length -1
    console.log(search_index)

    switch (keyEvent.code){
        case 'Enter': {
            keyEvent.preventDefault();
            keyEvent.stopPropagation();
            
            if(keyEvent.target.id != "search"){
                search_index = 0
                searched_items = []
                const e = document.querySelector("#search")
                e.value = ""
                e.focus()
                clear()
            }

            searched_items[search_index].scrollIntoView({ behavior: "smooth", block: "center" })
            searched_items[search_index].querySelector("textarea, input").focus()
            break
        }

        case 'Tab': {
            keyEvent.preventDefault();
            keyEvent.stopPropagation();
            searched_items[search_index].scrollIntoView({ behavior: "smooth", block: "center" })
            searched_items[search_index].querySelector("textarea, input").focus()
            break
        }
    }

}

document.querySelector("#search").addEventListener("input", search)
document.querySelector("#search").addEventListener("keydown", handle_keys)

export {search, handle_keys}