function parseDocumentationTemplatesInJS(templateString) {
    const sections = [];
    // Match content between ***n*** and &&&n&&&
    const regex = /============\*\*\*\d+\*\*\*============\n([\s\S]*?)\n?============&&&\d+&&&============/g;
    let match;

    while ((match = regex.exec(templateString)) !== null) {
        // Trim leading/trailing empty lines
        const content = match[1].replace(/^\s+|\s+$/g, '');
        sections.push(content);
    }

    return sections;
}

// Example usage:
const input = `
============***1***============
docs text1

docs text1
============&&&1&&&============
============***2***============
docs text2

docs text2
============&&&2&&&============
`;

const mdFilesArray = parseDocumentationTemplates(input);
console.log(mdFilesArray);
// Output: [ 'docs text1\n\ndocs text1', 'docs text2\n\ndocs text2' ]
