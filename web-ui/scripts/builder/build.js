// --- START: Added for build overlay ---
const buildOverlay = document.getElementById('build-overlay');
const buildStatusTitle = document.getElementById('build-status-title');
const buildStatusSubtitle = document.getElementById('build-status-subtitle');
const buildModal = document.querySelector('.build-modal');
// --- END: Added for build overlay ---


export function getUserConfig(id) {
    let config = localStorage.getItem("htvm_lang_" + id) || '[]';
    config = JSON.parse(config).join("\n")
    return config;
}


export async function getBuiltins() {
    const location = "https://raw.githubusercontent.com/TheMaster1127/HTVM/refs/heads/main/HTVM-instructions.txt";
    const response = await fetch(location);
    const data = await response.text();
    const lines = data.split("\n").slice(162);
    return lines.join("\n");
}

async function generateDocumentation(instructionFileContent) {
    instructionFileData = "";
    DOCS_params = "";
    DOCS_param1 = "";
    DOCS_param2 = "";
    DOCS_checkIfFuncNameExists = 0;
    OUTdocs_HTML = "";
    OUTdocs_MD = "";

    instructionFileData = instructionFileContent;
    return [await genDocs("html"), await genDocs("md")];
}

function getCurrentLangName() {
    const currentLangID = localStorage.getItem("HTVM_LastAccesedTab");
    const langSettings = JSON.parse(localStorage.getItem("langSettings")) || {};
    const langKey = "htvm_lang_" + currentLangID;
    return langSettings[langKey]?.name || `Language ${currentLangID}`;
}

async function generateReadme() {
    const location = "scripts/builder/appending-readme.md";
    const response = await fetch(location);
    const data = await response.text();
    const lang_name = getCurrentLangName()
    const formattedData = data.replace(/<MyCustomLang>/g, lang_name);

    return formattedData
}

export function saveAs(content, filename) {
    const blob = content instanceof Blob ? content : new Blob([content], { type: 'text/plain' });
    const url = URL.createObjectURL(blob);
    const a = document.createElement("a");
    a.href = url;
    a.download = filename;
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
    URL.revokeObjectURL(url);
}

async function zipIt(instructionFileContent, documentationHTML, documentationMarkdown, readmeContent) {
    const zip = new JSZip();

    zip.file("HTVM-instructions.txt", instructionFileContent);
    zip.file("DOCUMENTATION.html", documentationHTML);
    zip.file("DOCUMENTATION.md", documentationMarkdown);
    zip.file("README.md", readmeContent);

    const zippedBlob = await zip.generateAsync({
        type: "blob",
        compression: "DEFLATE",
        compressionOptions: { level: 9 }
    });

    return zippedBlob;
}


export async function buildNDownload() {
    const checkErrors = handleError(getUserConfig(localStorage.getItem("HTVM_LastAccesedTab")))
    if (checkErrors !== "noERROR") {
        throw new Error(checkErrors);
    }

    const instructionFileContent =
        getUserConfig(localStorage.getItem("HTVM_LastAccesedTab")) +
        "\n" +
        await getBuiltins();
    const [documentationHTML, documentationMarkdown] = await generateDocumentation(instructionFileContent);
    const readmeContent = await generateReadme();
    const zipContent = await zipIt(instructionFileContent, documentationHTML, documentationMarkdown, readmeContent);
    const zipFileName = `${getCurrentLangName()}.zip`;
    saveAs(zipContent, zipFileName);
}

export async function downloadInstructionsOnly() {
    const checkErrors = handleError(getUserConfig(localStorage.getItem("HTVM_LastAccesedTab")));
    if (checkErrors !== "noERROR") {
        throw new Error(checkErrors);
    }

    const instructionFileContent =
        getUserConfig(localStorage.getItem("HTVM_LastAccesedTab")) +
        "\n" +
        await getBuiltins();
    
    saveAs(instructionFileContent, `HTVM-instructions.txt`);
}