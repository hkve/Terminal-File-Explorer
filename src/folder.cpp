#include "folder.hpp"

Folder::Folder() {

}

Folder::Folder(fs::path path) : FEobject::FEobject(path) {
	
}

void Folder::updateDisplayName() {
	displayName = "\033[0;";
	displayName += (textFormat["bold"] + ";");
	if(marked) {
		displayName += textColor["green"];
	}	
	else {
		displayName += textColor["blue"];
	}

	if(highlight) {
		displayName += (";" + textBackground["gray"]);
	}

	displayName = displayName + "m" + shortendName + RESET;
}

