// --- DEXIE DATABASE SETUP ---
// This file initializes the IndexedDB database using Dexie.js.
// Each workspace ID gets its own separate database to ensure complete isolation.

let db;

function setupDatabase(workspaceId) {
    // Create a new Dexie database instance. The name is unique to the workspace.
    db = new Dexie(`HT-IDE-DB-id${workspaceId}`);

    // Define the database schema. Version 1.
    db.version(1).stores({
        // A table for files and folders.
        // 'path' is the primary key (unique identifier for each file/folder).
        files: '&path',

        // A table for HTVM instruction sets.
        // 'id' is the primary key.
        instructionSets: '&id',
        
        // A simple key-value store for all other settings and state.
        // 'key' is the primary key (e.g., 'openTabs', 'fontSize', 'color_ace-command').
        settings: '&key'
    });
}