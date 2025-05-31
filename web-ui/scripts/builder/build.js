function getUserConfig(id) {
    let config = localStorage.getItem("htvm_lang_" + id);
    config = JSON.parse(config).join("\n")
    return config;
}


async function getBuiltins() {
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
    return JSON.parse(localStorage.getItem("langSettings"))["htvm_lang_" + currentLangID].name;
}

async function generateReadme() {
    const location = "scripts/builder/appending-readme.md";
    const response = await fetch(location);
    const data = await response.text();
    const lang_name = getCurrentLangName()
    const formattedData = data.replace(/<MyCustomLang>/g, lang_name);

    return formattedData
}

function saveAs(content, filename) {
    const blob = new Blob([content], { type: "application/zip" });
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

    // Calculate pre-zip total size in bytes
    const totalOriginalSize =
        new TextEncoder().encode(instructionFileContent).length +
        new TextEncoder().encode(documentationHTML).length +
        new TextEncoder().encode(documentationMarkdown).length +
        new TextEncoder().encode(readmeContent).length;

    console.log(`Original total size: ${(totalOriginalSize / 1024).toFixed(2)} KB`);

    // Generate the zip file
    const zippedBlob = await zip.generateAsync({
        type: "blob",
        compression: "DEFLATE",
        compressionOptions: { level: 9 }
    });

    console.log(`Zipped size: ${(zippedBlob.size / 1024).toFixed(2)} KB`);

    return zippedBlob;
}


async function buildNDownload() {
    const checkErrors = handleError(getUserConfig(localStorage.getItem("HTVM_LastAccesedTab")))
    if (checkErrors !== "noERROR") {
        console.log("failed")
        throw new Error(checkErrors);
    }

    const instructionFileContent =
        getUserConfig(localStorage.getItem("HTVM_LastAccesedTab")) +
        "\n" +
        await getBuiltins()
    const [documentationHTML, documentationMarkdown] = awiat generateDocumentation(instructionFileContent);
    const readmeContent = await generateReadme()
    const zipContent = await zipIt(instructionFileContent, documentationHTML, documentationMarkdown, readmeContent);
    const zipFileName = `${getCurrentLangName()}.zip`;
    saveAs(zipContent, zipFileName);
}




document.querySelector("#buildButton").addEventListener("click", () => { await buildNDownload() })