#include "object.hpp"

FEobject::FEobject() {
	fs_obj = "path/to/file";

	name = fs_obj.filename();
}

FEobject::FEobject(fs::path path) {
	fs_obj = path;
	name = fs_obj.filename();

	if(name.length() < MAX_NAME_LENGTH) {
		shortendName = name;
	}
	else {
		shortendName = name.substr(0, MAX_NAME_LENGTH) + "...";
	}
}


void FEobject::updateDisplayName() {
	displayName = "\033[0;";
	if(marked) {
		displayName += textColor["green"];
	}
	else {
		displayName += textColor["white"];
	}

	if(highlight) {
		displayName += (";" + textBackground["gray"]);
	}

	displayName = displayName + "m" + shortendName + RESET;
}

// Getters
fs::path FEobject::getPath() {
	return fs_obj;
}


int FEobject::getFormatLength() {
	return displayName.length() - shortendName.length();
}

string FEobject::getDisplayName() {
	return displayName;
}

string FEobject::getName() {
	return name;
}

bool FEobject::getHighlight() {
	return highlight;
}

bool FEobject::getMarked() {
	return marked;
}

// Setters
void FEobject::setHighlight(bool highlight_) {
	highlight = highlight_;
}

void FEobject::setMarked(bool marked_) {
	marked = marked_;
}

// Display name formatting, static
map<string, string> FEobject::textColor = {
  {"gray", "30"},
  {"red", "31"},
  {"green", "32"},
  {"yellow", "33"},
  {"blue", "34"},
  {"purple", "35"},
  {"cyan", "36"},
  {"white", "37"}
};

map<string, string> FEobject::textBackground = {
  {"gray", "40"},
  {"red", "41"},
  {"green", "42"},
  {"yellow", "43"},
  {"blue", "44"},
  {"purple", "45"},
  {"cyan", "46"},
  {"white", "47"}
};

map<string, string> FEobject::textFormat = {
  {"bold", "1"},
  {"underline", "4"}
};