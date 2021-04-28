#ifndef FEobj_HPP
#define FEobj_HPP

#ifndef RESET
#define RESET "\033[0m"
#endif

#include <iostream>
#include <filesystem>
#include <string>
#include <map>

using namespace std;
namespace fs = std::filesystem;


class FEobj {
private:
	fs::path obj;	

	string name;
	string displayName;
	string type;

	bool marked = false;

	static map<string, string> textColor;
	static map<string, string> textBackground;
	static map<string, string> textFormat;

public:
	FEobj(string path);

	// Setters
	void setDisplayName();
	void setMarked(bool);

	// Getters
	string getDisplayName();
	string getType();
	bool getMarked();
};
#endif