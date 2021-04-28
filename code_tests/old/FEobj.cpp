#include "FEobj.hpp"

FEobj::FEobj (string path) {
	obj = path;
	name = obj.filename();

	if (not fs::exists(obj)) {
		cerr << obj <<endl;
		cerr << "Does not exist" <<endl;
		exit(1);
	}
	else if(fs::is_regular_file(obj)) {
		type = "file";
	}
	else if(fs::is_directory(obj)) {
		type = "dir";
	} 

	setDisplayName();
}


void FEobj::setDisplayName() {
	string format = "\033[0;";
	if(type=="file") {
		format += textColor["red"];
	}
	else if(type=="dir") {
		format += textColor["blue"];
	}

	if(marked) {
		format += ";";
	}

	format += "m";
	displayName = format + name + RESET;
}

bool FEobj::getMarked() {
	return marked;
}

void FEobj::setMarked(bool marked_) {
	marked = marked_;
}

string FEobj::getDisplayName() {
	return displayName;
}

string FEobj::getType() {
	return type;
}

map<string, string> FEobj::textColor = {
  {"gray", "30"},
  {"red", "31"},
  {"green", "32"},
  {"yellow", "33"},
  {"blue", "34"},
  {"purple", "35"},
  {"cyan", "36"},
  {"white", "37"}
};

map<string, string> FEobj::textBackground = {
  {"gray", "40"},
  {"red", "41"},
  {"green", "42"},
  {"yellow", "43"},
  {"blue", "44"},
  {"purple", "45"},
  {"cyan", "46"},
  {"white", "47"}
};

map<string, string> FEobj::textFormat = {
  {"bold", "1"},
  {"underline", "4"}
};