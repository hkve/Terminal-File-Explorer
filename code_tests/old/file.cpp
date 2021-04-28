#include "file.hpp"

File::File(string path) {
	object = path;
}

string File::displayName(bool marked) {
	string displayName;

	if(marked) {

	}

	return RED + filename + RESET;
}