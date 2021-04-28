#include <string>
#include <iostream>
#include <filesystem>
#include <unistd.h> 
namespace fs = std::filesystem;
using namespace std;

void test(string a) {
	cout << typeid(a).name();
}

int main()
{
	char cwd[100]; 
	char* new_wd;

	string cwd_string;
	string new_wd_string;

	getcwd(cwd, sizeof(cwd));
	
	cwd_string = string(cwd);

	cout << cwd_string <<endl; 

	new_wd_string = cwd_string + "/data";

	cout << new_wd_string <<endl;
	new_wd = &new_wd_string[0]; // Char pointer to address of string

	/*
	for(int i = 0; i < new_wd_string.length(); i++) {
		new_wd[i] = new_wd_string[i];
	}
	*/
	chdir(new_wd);

	getcwd(cwd, sizeof(cwd));
	cout << cwd;

	return 0;
}
