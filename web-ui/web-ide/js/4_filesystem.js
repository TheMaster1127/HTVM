// --- Virtual Filesystem Functions ---

// --- DEXIE MIGRATION: Reworked filesystem to use IndexedDB instead of localStorage ---

async function getAllPaths() {
    try {
        const allFiles = await db.files.toArray();
        const paths = allFiles.map(file => file.path);
        return paths.sort((a, b) => a.localeCompare(b, undefined, { numeric: true }));
    } catch (error) {
        console.error("Failed to get all paths from IndexedDB", error);
        return [];
    }
};

async function saveFileContent(filename, content, silent = false) {
    if (!filename) return;

    try {
        // 'put' will add or update the record.
        await db.files.put({
            path: filename,
            content: content,
            isFolder: filename.endsWith('/')
        });

        if (fileSessions.has(filename)) {
            fileSessions.get(filename).getUndoManager().markClean();
            checkDirtyState(filename);
        }
        if (!silent && term) term.writeln(`\x1b[32mFile saved: ${filename}\x1b[0m`);

    } catch (error) {
        console.error(`Failed to save file "${filename}" to IndexedDB`, error);
        if (term) term.writeln(`\x1b[31mError saving file: ${filename}\x1b[0m`);
    }
}

async function deleteItem(path, isFile) {
    if (!confirm(`Are you sure you want to delete the ${isFile ? "file" : "folder"} "${path}"? This cannot be undone.`)) return;

    try {
        // Find all paths to delete (the item itself, and all children if it's a folder)
        const allDbPaths = await getAllPaths();
        const pathsToDelete = isFile ? [path] : allDbPaths.filter(p => p.startsWith(path));
        
        if (pathsToDelete.length > 0) {
            // Perform deletions in bulk
            await db.files.bulkDelete(pathsToDelete);
            
            // Clean up related data from the settings table
            const settingsKeysToDelete = pathsToDelete.map(p => 'state_' + p);
            await db.settings.bulkDelete(settingsKeysToDelete);
        }

        // Clean up in-memory state
        pathsToDelete.forEach(p => {
            fileSessions.delete(p);
            closeTab(p, true);
        });

        term.writeln(`\x1b[31m${isFile ? "File" : "Folder"} deleted: ${path}\x1b[0m`);

        // Update any saved sessions that might contain the deleted files
        const sessionList = await dbGet('session_list') || [];
        for (const sessionName of sessionList) {
            let sessionTabs = await dbGet(`session_data_${sessionName}`);
            if (sessionTabs) {
                const initialLength = sessionTabs.length;
                sessionTabs = sessionTabs.filter(tabPath => !pathsToDelete.includes(tabPath));
                if (sessionTabs.length < initialLength) {
                    await dbSet(`session_data_${sessionName}`, sessionTabs);
                    term.writeln(`\x1b[33mUpdated session "${sessionName}" to remove deleted files.\x1b[0m`);
                }
            }
        }
        await renderFileList();

    } catch (error) {
        console.error(`Failed to delete item "${path}"`, error);
        term.writeln(`\x1b[31mError deleting item: ${path}\x1b[0m`);
    }
}


async function handleNewFile() {
    const name = prompt("File name:");
    if (name?.trim()) {
        const path = currentDirectory === '/' ? name : `${currentDirectory}${name}`;
        const allPaths = await getAllPaths();
        if (allPaths.includes(path)) {
            alert("File exists.");
            return;
        }

        let newFileContent = '';
        if (path.endsWith('.htvm')) {
            const activeSetContent = await getActiveInstructionSetContent();
            const instructions = activeSetContent.split('\n');
            const commentChar = (instructions && instructions.length > 100) ? instructions[100] : ';';
            newFileContent = `${commentChar.trim()} Welcome!`;
        }

        await saveFileContent(path, newFileContent, true);
        await openFileInEditor(path);
    }
}

async function handleNewFolder() {
    const name = prompt("Folder name:");
    if (name?.trim()) {
        const path = (currentDirectory === '/' ? name : `${currentDirectory}${name}`) + '/';
        const allPaths = await getAllPaths();
        if (allPaths.some(p => p.startsWith(path))) {
            alert("Folder exists.");
            return;
        }
        await db.files.put({ path: path, isFolder: true, content: null });
        await renderFileList();
    }
}