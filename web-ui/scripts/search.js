import { debounce } from "./utils.js"

const search = debounce(function (term){
    document.querySelectorAll(".search-sel").forEach((e)=>{
        e.classList.remove("search-sel")
    })

    if(!term.target.value) return
    const sterm = CSS.escape( term.target.value.trim());
    const matches = document.querySelectorAll(`[data-name*="${sterm}" i]`);
    if(matches.length <= 0) return
    matches[0].scrollIntoView({ behavior: "smooth", block: "center" })
    matches.forEach((match)=>{
       match.classList.add("search-sel")
    })
}, 500)
document.querySelector("#search").addEventListener("input", search)

export {search}