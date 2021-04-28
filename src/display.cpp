/*
Contains class function for Interface connected to the display
*/

#include "interface.hpp"

void Interface::display() {
	/*
	Main display function. Update all highligths/marks, clear prev output and display 
	folders/files. 
	*/
	updateDisplay();

	// Set output to top of terminal
	cout << CLEAR;

	displayBlock<Folder>(folders);
	displayBlock<File>(files);

	if(show_info_line) {
		displayInfoLine();
	}

	if(show_clipboard) {
		displayClipboard();
	}
}

template<class T> // Template for instances of Folder or File
void Interface::displayBlock(std::vector<T> &obj) {
	/*
	Displays a block of either Folder or File (obj). 

		Args: 
			obj (adress of vector): A vector containing the folders/files to display  
	*/

	// Get the amount of obj, calculate how many full rows can be displayed
	int n_obj = obj.size();
	int obj_rows = n_obj/n_cols;

	// spacing: Number of characters to use for each obj 
	// idx: Mapping the 2d grid to the 1d vector of obj 
	int spacing, idx;

	// Display all full rows
	for(int i = 0; i < obj_rows; i++) {
		for(int j = 0; j < n_cols; j++) {
			
			// Map idx
			idx = i*n_cols + j;
			
			// Get spacing for for display name and add the maximum spacing
			spacing = obj[idx].getFormatLength() + maxSpacing;

			// Center output at left and display the obj
			cout << left << setw(spacing) << obj[idx].getDisplayName();
		}

		// Next row
		cout << endl;
	}
	
	// Display last row (not full)
	for(int i = 0; i < n_obj%n_cols; i++) {
		
		// Map idx
		idx = obj_rows*n_cols + i;

		// Get spacing fr display name and add the maximum spacing
		spacing = obj[idx].getFormatLength() + maxSpacing;

		// Center output at left and display obj
		cout << left << setw(spacing) << obj[idx].getDisplayName();
	}

	if(n_obj != 0) {
		// New line for next block of obj
		cout << endl;
	}
}

template<class T>
void Interface::updateDisplayBlock(std::vector<T> &obj, int pos_idx) {
	int n_obj = obj.size();
	for(int i = 0; i < n_obj; i++) {
		if(pos_idx == i) {
			obj[i].setHighlight(true);
		}
		else {
			obj[i].setHighlight(false);
		}

		obj[i].updateDisplayName();
	}
}

template<class T>
void Interface::updateDisplayBlockLine(std::vector<T> &obj, int start, int stop) {
	/*
	Updates a chunck of files/folders. Used for updating last folder line and first file line
	Goes from start to stop.
	*/
	
	for(int i = start; i < stop; i++) {
		obj[i].setHighlight(false);
		obj[i].updateDisplayName();
	}
}

void Interface::updateDisplay() {
	/*
	Updates highligths/marks
	*/

	// Always update last folder line and first file line in case of changing between the two of them
	if(n_folders != 0) {
		updateDisplayBlockLine<Folder>(folders, n_folders-last_folder_line, n_folders);
	}
	if(n_files != 0) {
		updateDisplayBlockLine<File>(files, 0, last_file_line);
	}


	// If in folders, update folder highligths
	if(current_pos < n_folders) {
		updateDisplayBlock<Folder>(folders, current_pos);
	} 
	// Else update file highligths
	else {
		updateDisplayBlock<File>(files, current_pos-n_folders);
	}
}

void Interface::displayInfoLine() {
	cout << endl;
	cout << "Current working directory" <<endl;
	cout << getPath();
	cout << endl;
}

void Interface::displayClipboard() {
	cout << endl;
	cout << "Current clipboard:" <<endl;


	displayBlock(marked_folders);
	displayBlock(marked_files);

	cout <<endl;
}

int Interface::yesNoScreen() {
	char ans;

	system("stty raw");
	ans = getchar(); 
    system("stty cooked");
    
    if(ans == 'Y' || ans == 'y') {
    	return 1;
    }
    else if(ans == 'N' || ans == 'n') {
    	return 0;
    }
    else {
    	cout << "\r";
    	return -1;
    }
}

void Interface::displayDeleteConfirmHighligth(string displayName) {
	cout << "Are you sure you want to delete " << displayName << "? [Y/n]" <<endl; 
}