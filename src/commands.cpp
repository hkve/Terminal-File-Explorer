/* 
Holds all input commands that can be executed
Each function is held as a class-function pointer: cmdMap
The default command key written before each command definition  
*/

#include "interface.hpp"


// Q
void Interface::quit() {
	// Re-enable cursor before quitting
	cout << SHOW_CURSOR;
    exit(0);
}

// q
void Interface::moveUpDirectory() {
	// Dump folders/files from vector
	clear();

	// Remember previous path
	previous_paths.push_back(path);

	// Set new path
	setPath(path.parent_path());

	// Load and show new folder
	do_load = true;
	do_display = true;
}

// e
void Interface::enterDirectory() {
	if(current_pos < n_folders) {
		previous_paths.push_back(path);
		path = folders[current_pos].getPath();

		clear(); 
		
		setPath(path);
		
		do_load = true;
		do_display = true;
	}	
}

void Interface::movePrevDirectory() {
	int last_path_idx = previous_paths.size() - 1;

	if (previous_paths[last_path_idx] != path) {
		// Dump folders/files from vector
		clear();


		// Set new path
		setPath(previous_paths[last_path_idx]);
		
		// Remember previous path
		previous_paths.pop_back();

		// Load and show new folder
		do_load = true;
		do_display = true;
	}
}


void Interface::toggleMark() {
	int idx = current_pos;

	if(current_pos >= n_folders) {
		idx = current_pos-n_folders;
		markObj<File>(files[idx], marked_files, marked_files_idx, idx);
		//markObj<File>(files, marked_files, marked_files_idx, idx);
	}
	else {
		markObj<Folder>(folders[idx], marked_folders, marked_folders_idx, idx);
		//markObj<Folder>(folders, marked_folders, marked_files_idx, idx);
	}

	do_display = true;
}

template<class T>
void Interface::markObj(T &obj, vector<T> &marked_obj, map<string, vector<int>> &marked_obj_idx, int idx) {
	if(obj.getMarked()) {
		// Remove idx form mark_obj_idx map corresponding to directory
		auto pos_idx = find(marked_obj_idx[path].begin(), marked_obj_idx[path].end(), idx);
		
		// If find has not reached end remove the element
		if(pos_idx != marked_obj_idx[path].end()) {
			marked_obj_idx[path].erase(pos_idx);
		}

		// Remove from marked_obj vector

		// First find the path of the obj to remove
		string to_remove = obj.getPath();

		auto pos = find_if(marked_obj.begin(), marked_obj.end(), [&to_remove](T &_) {return _.getPath() == to_remove;});
		
		if(pos != marked_obj.end()) {
			marked_obj.erase(pos);
		}

		// Unmark it
		obj.setMarked(false);
	}
	else {
		// Mark it
		obj.setMarked(true);

		// Add idx to mark_obj_idx map corresponding to directory
		marked_obj_idx[path].push_back(idx);

		// Add obj to marked_obj vector
		marked_obj.push_back(obj);
		int last_idx = marked_obj.size() - 1;
		marked_obj[last_idx].setHighlight(false);
		marked_obj[last_idx].updateDisplayName();	

	}

}

template<class T>
void Interface::unMarkObj(vector<T> &objs, vector<int> &obj_idx) {
	for(auto it = obj_idx.begin(); it < obj_idx.end(); it++) {
		objs[*it].setMarked(false);
	}
}

void Interface::unMarkAll() {
	unMarkObj<Folder>(folders, marked_folders_idx[path]);
	unMarkObj<File>(files, marked_files_idx[path]);

	vector<Folder>().swap(marked_folders);
	vector<File>().swap(marked_files);

	marked_folders_idx.clear();
	marked_files_idx.clear();

	do_display = true;
}


// P 
void Interface::pasteToHighlightDir() {
	if(current_pos < n_folders) {
		fs::path destination = folders[current_pos].getPath();
		pasteFolders(marked_folders, destination);
		pasteFiles(marked_files, destination);
	}
}

// p
void Interface::pasteToCurrentDir() {
	/*
	Paste all marked files to the current directory. Equal to pressing ctrl+w in file explorer 
	*/

	// Preform the actual copying of files
	pasteFolders(marked_folders, path);
	pasteFiles(marked_files, path);

	do_load = true;
	do_display = true;
}

void Interface::pasteFolders(vector<Folder> &marked_folders, fs::path &destination) {
	for(int i = 0; i < marked_folders.size(); i++) {
		// Make directory that should be copied at current path
		fs::path folderPath = destination;
		folderPath /= marked_folders[i].getName();
		
		// Make that directory
		fs::create_directory(folderPath);

		// Insert into a vecotr
		vector<Folder> temp;
		temp.push_back(marked_folders[i]);

		// Add all folder content to new folder
		pasteObjs<Folder>(temp, folderPath, folderCopyOptions);
	}
}

void Interface::pasteFiles(vector<File> &marked_files, fs::path &destination) {
	pasteObjs<File>(marked_files, destination, fileCopyOptions);
}

template<class T, typename S>
void Interface::pasteObjs(vector<T> &objs, fs::path &destination, S options) {
	for(int i = 0; i < objs.size(); i++) {
		fs::path origin = objs[i].getPath();

		if(origin != destination) {
			fs::copy(objs[i].getPath(), destination, options);
		} 
	}
}

// r
void Interface::deleteFromClipboard() {
	for(int i = 0; i < marked_files.size(); i++) {
		fs::remove(marked_files[i].getPath());
	}
	for(int i = 0; i < marked_folders.size(); i++) {
		fs::remove_all(marked_folders[i].getPath());
	}

	unMarkAll();

	do_load = true;
	do_display = true;
}

// R
void Interface::deleteFromHighlight() {
	int ans = -1;

	if(current_pos < n_folders) {
		displayDeleteConfirmHighligth(folders[current_pos].getDisplayName());
		
		while(ans == -1) {
			ans = yesNoScreen();
			if(ans == 1) {
			fs::remove_all(folders[current_pos].getPath());
			}
		}
	}

	else {
		int current_file_pos = current_pos-n_folders;
		displayDeleteConfirmHighligth(files[current_file_pos].getDisplayName());
		
		while(ans) {
			ans = yesNoScreen();
			if(ans == 1) {
				fs::remove(files[current_file_pos].getPath());
			}
		}
	}

	do_load = true;
	do_display = true;
}

/*
Movement functions (wasd). Handles both folders and files
This should be rewritten
*/

// d
void Interface::moveRight() {

	int next_pos = current_pos+1;
	if(next_pos < n_folders+n_files) {
		current_pos = next_pos;		
	}

	do_display = true;
}

// a
void Interface::moveLeft() {
	int next_pos = current_pos-1;
	if(next_pos >= 0) {
		current_pos = next_pos;
	}

	do_display = true;
}

// Note to self: Rewrite these to something clever
// s
void Interface::moveDown() {
	int next_pos = current_pos + n_cols;

	if(next_pos < n_folders+n_files) {
		if(current_pos < n_folders && next_pos > n_folders) {
			current_pos += n_folders%n_cols;
		}
		else {
			current_pos = next_pos;
		}
	}
	else {
		current_pos += n_folders%n_cols;
	}


	if(current_pos >= n_folders + n_files) {
		current_pos = n_folders+n_files-1;
	}
	do_display = true;
}

// w
void Interface::moveUp() {
	int next_pos = current_pos - n_cols;

	if(next_pos >= 0) {
		if(current_pos > n_folders && next_pos < n_folders) {
			current_pos += n_files%n_cols;
		}
		else {
			current_pos = next_pos;
		}
	}
	else {
		current_pos -= n_folders%n_cols;
	}


	if(current_pos < 0) {
		current_pos = 0;
	}

	do_display = true;
}


/*
Toggle clipboard and directory information line.
*/

// I
void Interface::toggleInfoLine() {
	if(show_info_line) {
		show_info_line = false;
	}
	else {
		show_info_line = true;
	}

	do_display = true;
}

// C
void Interface::toggleClipboard() {
	if(show_clipboard) {
		show_clipboard = false;
	}
	else {
		show_clipboard = true;
	}

	do_display = true;
}