#include "interface.hpp"

Interface::Interface(fs::path path_) {
	path = path_;	
	previous_paths.push_back(path);

	// Set cmd map
	cmdMap.insert( make_pair("Q", &Interface::quit) );
	cmdMap.insert( make_pair("q", &Interface::moveUpDirectory) );
	cmdMap.insert( make_pair("b", &Interface::movePrevDirectory) );
	cmdMap.insert( make_pair("d", &Interface::moveRight) );
	cmdMap.insert( make_pair("a", &Interface::moveLeft) );
	cmdMap.insert( make_pair("s", &Interface::moveDown) );
	cmdMap.insert( make_pair("w", &Interface::moveUp) );
	cmdMap.insert( make_pair("e", &Interface::enterDirectory) );
	cmdMap.insert( make_pair("I", &Interface::toggleInfoLine) );
	cmdMap.insert( make_pair("C", &Interface::toggleClipboard) );
	cmdMap.insert( make_pair("m", &Interface::toggleMark) );
	cmdMap.insert( make_pair("M", &Interface::unMarkAll) );
	cmdMap.insert( make_pair("p", &Interface::pasteToCurrentDir) );
	cmdMap.insert( make_pair("P", &Interface::pasteToHighlightDir) );
	cmdMap.insert( make_pair("r", &Interface::deleteFromHighlight) );
	cmdMap.insert( make_pair("R", &Interface::deleteFromClipboard) );
}

void Interface::run() {
	// Hide cursor
	cout << HIDE_CURSOR;
	
	while(do_run) {

		if(do_load) {
			load();
		}

		if(do_display) {
			display();
			do_load = false;
			do_display = false;
		}

	system("stty raw");
	cmd = getchar(); 
    system("stty cooked");

    // Has to pass as string to make c++ happy
    callCmd(string(1, cmd));
    cout << "\x8";
	}
}


void Interface::clear() {
	vector<File>().swap(files);
	vector<Folder>().swap(folders);
}



void Interface::callCmd(string cmd) {
	// Preform carrige return
	cout << "\r";

	if(cmdMap.find(cmd) == cmdMap.end()) {
		cout << "\x8";
	}
	else {
		cmdFunc tempFunc = cmdMap[cmd];
		(this->*tempFunc)();
	}
}

// Setters
void Interface::setPath(fs::path new_path) {
	if(fs::exists(new_path)) {
		path = new_path;
	}
	else {
		cerr << "Error, " << new_path << " does not exist" <<endl;
	}
}



// Getters
fs::path Interface::getPath() {
	return path;
}

void Interface::getTermDims(int* width, int* height) {
	*width = termWidth;
	*height = termHeight;
}

int Interface::getNcols() {
	return n_cols;
}



