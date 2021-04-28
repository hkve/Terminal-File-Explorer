#include <iostream>
#include <filesystem>
#include <string>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char const *argv[])
{
	fs::path file("/home/haakon/Documents/programmering/cpp/fileExplorer/tests");

	cout << file.filename() <<endl;
	cout << file.relative_path() <<endl;

	for(auto it=file.begin(); it!=file.end(); it++) {
		cout << *it <<endl;
	}

	// file /= "dump.dat"; Adds "/dump.dat"
	// file += "dump.dat"; Adds "dump.dat"
	
	cout << fs::is_regular_file(file) <<endl;
	cout << fs::is_directory(file) <<endl;
	return 0;
}
