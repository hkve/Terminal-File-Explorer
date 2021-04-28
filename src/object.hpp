#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <filesystem>
#include <string>
#include <map>

using namespace std;
namespace fs = std::filesystem;

#ifndef RESET
#define RESET "\033[0m"
#define MAX_NAME_LENGTH 20
#endif


class FEobject {
protected:
	fs::path fs_obj;

	string name;
	string shortendName;
	string displayName;

	bool highlight = false;
	bool marked = false;

	
	static map<string, string> textColor;
	static map<string, string> textBackground;
	static map<string, string> textFormat;

public:
	FEobject();
	FEobject(fs::path path);

	// Visual
	void updateDisplayName();

	// Getters
	int getFormatLength();
	fs::path getPath();

	string getName();
	string getDisplayName();
	bool getHighlight();
	bool getMarked();

	// Setters 
	void setHighlight(bool highlight_);
	void setMarked(bool marked_);
};

#endif