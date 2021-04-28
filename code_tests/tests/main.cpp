#include<iostream>
#include<unistd.h>
#include<filesystem>
#include<string>
#include<vector>

namespace fs = std::filesystem;
using namespace std;

#define MAXPATH 100

void split_full_path(string full_path, string* path, string* name) {
	size_t slash_pos;
	slash_pos = full_path.find_last_of("/") + 1;

	*path = full_path.substr(0, slash_pos);
	*name = full_path.substr(slash_pos);
}

void get_cwd_files(string cwd, vector<string>* paths, vector<string>* names) {
	/* 
	Goes trough current woking directory and saves paths and filenames 
	Args:
		cwd (string): Path to current working directory
		pahts (vector pointer): Where to paths should be saved
		names (vector pointer): Where the filenames should be saved
	*/

	string full_path;
	string name;
	string path;
	size_t slash_pos;
	
	int i = 0;
	for(const auto & entry : fs::directory_iterator(cwd)) {
		full_path = string(entry.path());
		
		split_full_path(full_path, &path, &name);

		names->push_back(name);
		paths->push_back(path);

		i++;
	}
}


void print_cwd(string cwd_name, vector<string>* names) {
	for(auto name = names->begin(); name != names->end(); name++) {
		cout << *name <<endl;
	}	
	cout << "CWD: " << cwd_name;
}

int main() {
    char c;
  	bool run = true;
	bool load = true;
	bool output = true;
	
	char cwd[MAXPATH];
	string cwd_path;
	string cwd_name;

	string prev_wd;

	vector<string> cwd_paths;
	vector<string> cwd_names;

   	// Set the terminal to raw mode
    while(run) {
	

		if(load) {
			getcwd(cwd, sizeof(cwd)); 
			split_full_path(cwd, &cwd_path, &cwd_name);

			get_cwd_files(cwd, &cwd_paths, &cwd_names);

			load = false;
		}

		if(output) {
			print_cwd(cwd_name, &cwd_names);

			output = false;
		}		

		// terminate when "." is pressed
        system("stty raw");
		c = getchar(); 
        system("stty cooked");
        
		if(c == 'q') {
			system("clear");
      		run = false;
        }
        if(c == 'j') {
        	cout << "\033[2J\033[1;1H";		

        	char* new_wd = &cwd_path[0];
        	chdir(new_wd);

        	prev_wd = cwd_name;

        	cwd_paths.clear();
        	cwd_names.clear();

        	load = true;
        	output = true;
        }

        if(c == 'k') {
			cout << "\033[2J\033[1;1H";
			string new_wd_string = cwd_path + cwd_name + "/" + prev_wd;

			char* new_wd = &new_wd_string[0];
			
			/*
			NOTE TO MYSELF:
			current working dir + prev_wd =  prev_wd_path
			*/

			cout << endl << new_wd <<endl;
			
			chdir(new_wd);

			getcwd(cwd, sizeof(cwd));

			cout << endl << cwd <<endl;
			system("pause");
			cwd_paths.clear();
        	cwd_names.clear();

        	load = true;
        	output = true;
        }
    }

	return 0;
}
