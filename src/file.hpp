#ifndef FILE_HPP
#define FILE_HPP

#include "object.hpp"

class File: public FEobject {
private:

public:
	File();
	File(fs::path path);

};

#endif