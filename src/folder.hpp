#ifndef FOLDER_HPP
#define FOLDER_HPP

#include "object.hpp"

class Folder: public FEobject {
private:

public:
	Folder();
	Folder(fs::path path);

	void updateDisplayName();
};

#endif