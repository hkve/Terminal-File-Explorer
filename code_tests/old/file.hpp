#ifndef FILE_HPP
#define FILE_HPP

#include "object.hpp"

class File: public Object {
private:

public:
	File(string path);

	string displayName(bool marked=false);
};

#endif