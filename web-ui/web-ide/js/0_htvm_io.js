// --- HTVM Compiler I/O ---
// This file provides the necessary I/O functions for the HTVM compiler,
// specifically for handling file imports/includes from within a script.

/**
 * @type {string}
 * A global variable holding the directory path of the HTVM file currently being executed.
 * This is used as the base for resolving relative import paths.
 * It is set in 6_htvm.js before the compiler is invoked.
 * It MUST end with a trailing slash, e.g., "/src/modules/" or "/".
 */
window.currentHtvmFileDirectory = '/';

/**
 * A utility function to resolve a potentially relative file path into an absolute one.
 * This handles './', '../', and absolute paths correctly.
 * @param {string} filePath - The file path from the include statement.
 * @param {string} basePath - The directory of the file containing the include, e.g., "/src/".
 * @returns {string} The resolved absolute path.
 */
window.resolveHtvmPath = function(filePath, basePath) {
    // Normalize Windows-style backslashes to Unix-style slashes
    const normalizedPath = filePath.replace(/\\/g, '/');

    // If path is already absolute, start from root. Otherwise, start from the base path.
    const startingPath = normalizedPath.startsWith('/') ? '' : basePath;
    const combinedPath = startingPath + normalizedPath;

    // --- Path Resolution Logic (handles '.' and '..') ---
    const parts = combinedPath.split('/');
    const resolvedParts = [];
    for (const part of parts) {
        if (part === '' || part === '.') {
            continue; // Ignore empty parts and current directory references
        }
        if (part === '..') {
            if (resolvedParts.length > 0) {
                resolvedParts.pop(); // Go up one level
            }
        } else {
            resolvedParts.push(part);
        }
    }

    // Reconstruct the final path. It must always start with a slash.
    return '/' + resolvedParts.join('/');
}


/**
 * Reads the content of a file from the virtual file system asynchronously.
 * This function is the "master" async reader that communicates with the database.
 * @param {string} filePath The absolute path to the file to read.
 * @returns {Promise<string|null>} A promise that resolves with the file content, or null if the file is not found.
 */
window.FileRead = async function FileRead(filePath) {
    if (!filePath) {
        console.error("FileRead called with an empty path.");
        return null;
    }

    // Use the global resolver to get the canonical path
    const finalResolvedPath = window.resolveHtvmPath(filePath, window.currentHtvmFileDirectory);

    try {
        // Fetch the file record from the IndexedDB database
        let fileRecord = await db.files.get(finalResolvedPath);

        // *** RESILIENCY FIX ***
        // If not found, and it's a root path, try again without the leading slash.
        // This handles legacy data where root files were stored as "file.ext" instead of "/file.ext".
        if (!fileRecord && finalResolvedPath.startsWith('/') && finalResolvedPath.indexOf('/', 1) === -1) {
            const legacyPath = finalResolvedPath.substring(1);
            fileRecord = await db.files.get(legacyPath);
        }

        if (fileRecord && !fileRecord.isFolder) {
            return fileRecord.content;
        } else {
            console.warn(`FileRead: File not found or is a directory at resolved path "${finalResolvedPath}"`);
            return null;
        }
    } catch (error) {
        console.error(`FileRead: Error accessing IndexedDB for path "${finalResolvedPath}"`, error);
        return null;
    }
}