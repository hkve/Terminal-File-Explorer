#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream> 
#include <string> 
#include <filesystem> 
#include <vector>
#include <map>
#include <algorithm>
#include <unistd.h>
#include <error.h>
#include <termcap.h>

#include "file.hpp"
#include "folder.hpp"

#define CLEAR "\033[2J\033[1;1H"
#define HIDE_CURSOR "\e[?25l"
#define SHOW_CURSOR "\e[?25h"

using namespace std;
namespace fs = std::filesystem;

class Interface {
public:
	// Typedef function map for commnands
	typedef void (Interface::*cmdFunc)();

	// Constructor
	Interface(fs::path path_);

	void run();

	// Mother functions
	void load(); // Conatins all logic for loading
	void display(); // Contains all logic for display
	void clear(); // Clears current directory content

	/* 
	Loading functions
	*/
	void updateTermDims(); // If resize find the next terminal dismensions
 	void updateNcols(); // Finds how many cols/rows
	void updateBorderLines(); // Finds how many folder/files for last row

	template<class T>
	void checkMarked(vector<T> &objs, vector<int> &marked_objs);

	/*
	Display functions
	*/
	void updateDisplay();
	void displayClipboard();

	template<class T>
	void displayBlock(std::vector<T> &obj);
	
	template<class T>
	void updateDisplayBlock(std::vector<T> &obj, int pos_idx);

	template<class T>
	void updateDisplayBlockLine(std::vector<T> &obj, int start, int stop);
	
	void displayInfoLine();

	/*
	File operation functions
	*/
	// Used by toggleMark function
	template<class T> 
	void markObj(T &obj, vector<T> &marked_obj, map<string, vector<int>> &marked_obj_idx, int idx); // Marks a folder/file

	// Used by unMarkAll function
	template<class T> 
	void unMarkObj(vector<T> &objs, vector<int> &obj_idx); // Unmarks a vector of folders/files

	void pasteFolders(vector<Folder> &marked_folders, fs::path &destination);
	void pasteFiles(vector<File> &marked_files, fs::path &destination);
	template<class T, typename S> 
	void pasteObjs(vector<T> &objs, fs::path &destination, S options);
	
	/*
	Command functions
	*/
	void callCmd(string cmd); // Calls a command
	
	// List of commands and defaults
	void quit(); // Q
	void moveUpDirectory(); // q
	void movePrevDirectory(); // b
	void enterDirectory(); // e
	void toggleInfoLine(); // I
	void toggleClipboard(); // C
	void toggleMark(); // m
	void unMarkAll(); // M
	void pasteToCurrentDir(); // p
	void pasteToHighlightDir(); // P
	void deleteFromClipboard(); // r
	void deleteFromHighlight(); // R

	// Movement (wasd)
	void moveRight(); // d
	void moveLeft(); // a
	void moveDown(); // s
	void moveUp(); // w

	/*
	Extra menus and such
	*/
	int yesNoScreen();

	void displayDeleteConfirmHighligth(string displayName);

	// Getters
	fs::path getPath();
	void getTermDims(int*, int*);
	int getNcols();

	// Setters
	void setPath(fs::path new_path);

private:
	// Current directory path
	fs::path path;

	// Vector containing the previous paths
	vector<fs::path> previous_paths; 

	// Folders/files in current directory
	vector<Folder> folders;
	vector<File> files;

	// Folders/fiels marked across all directories
	vector<Folder> marked_folders;
	vector<File> marked_files;

	// Map holding the indexes of marked folders/files across all directories
	// Idxes correspond to where they should be when loaded 
	map<string, vector<int>> marked_folders_idx;
	map<string, vector<int>> marked_files_idx;

	// The number of folders/files in current directory
	int n_folders;
	int n_files;

	// How many folders/files display on last lines in current directory
	int last_folder_line;
	int last_file_line;

	static constexpr auto folderCopyOptions = fs::copy_options::update_existing | fs::copy_options::recursive;
	static constexpr auto fileCopyOptions = fs::copy_options::update_existing;

	// Terminal and display 
	int termWidth;
	int termHeight;
	int maxSpacing; // Finds the largest display name and set this as spacing for display names
	int n_cols = 1;

	// Operational
	bool do_run = true;
	bool do_load = true;
	bool do_display = true;

	bool show_info_line = false;
	bool show_clipboard = false;
	
	// Taking commands from keyboard
	char cmd;

	// Current pos in display, runs from 0 to n_folders+n_files-1
	int current_pos;

	// Mapping the command (cmd) to its respective function
	map<string, cmdFunc> cmdMap;
};

#endif