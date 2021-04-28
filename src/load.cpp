#include "interface.hpp"

void Interface::load() {
	clear();

	current_pos = 0;
	fs::path loadingObj;

	int file_counter = 0;
	int folder_counter = 0;

	for(const auto & entry : fs::directory_iterator(path)) {
		loadingObj = entry;

		try {
			
			if(fs::is_regular_file(loadingObj)) {
				files.push_back(File(loadingObj));
				files[file_counter].updateDisplayName();
				file_counter++;
			}
			else if(fs::is_directory(loadingObj)) {
				folders.push_back(Folder(loadingObj));
				folders[folder_counter].updateDisplayName();
				folder_counter++;
			}

		}

		catch(fs::filesystem_error & entry) {
			continue;
		}
	}	

	n_folders = folders.size();
	n_files = files.size();

	if(n_folders != 0) {
		checkMarked<Folder>(folders, marked_folders_idx[path]);
	}
	if(n_files != 0) {
		checkMarked<File>(files, marked_files_idx[path]);
	}

	updateTermDims();
	updateNcols();
	updateBorderLines();
}

void Interface::updateNcols() {
	/*
	Calculates the amount of rows needed (allows for rezing of terminal).
	Also finds the longest folder/file name and use this +1 as maximum spacing
	*/

	// nameLength: temp variable to hold the number of characters for each obj name
	// maxSpacing: class variable to track longest obj name
	int nameLength;
	maxSpacing = 0; 
	
	// Find longest folder name
	for(int i = 0; i < n_folders; i++) {
		nameLength = folders[i].getName().length();
		if(nameLength > maxSpacing) {
			maxSpacing = nameLength;
		}
	}	

	// Find longest file name
	for(int i = 0; i < n_files; i++) {
		nameLength = files[i].getName().length();
		if(nameLength > maxSpacing) {
			maxSpacing = nameLength;
		}
	}

	maxSpacing += 1;
	n_cols = termWidth/maxSpacing;
}

void Interface::updateTermDims() {
	/*
	Uses termcap to find width/height of current terminal window.
	*/
	static char termbuf[2048];
	char *termtype = getenv("TERM");
	
    if (tgetent	(termbuf, termtype) < 0) {
        error(EXIT_FAILURE, 0, "Could not access the termcap data base.\n");
    }
	
    termWidth = tgetnum("co");
    termHeight = tgetnum("li");
}

void Interface::updateBorderLines() {
	if(n_folders%n_cols == 0) {
		last_folder_line = n_cols;
	}
	else {
		last_folder_line = n_folders%n_cols;
	}

	if(n_files >= n_cols) {
		last_file_line = n_cols;
	}
	else {
		last_file_line = n_files;
	}
}

template<class T>
void Interface::checkMarked(vector<T> &objs, vector<int> &marked_objs) {
	auto it = marked_objs.begin();
	for(; it < marked_objs.end(); it++) {
		objs[*it].setMarked(true);
	}
}