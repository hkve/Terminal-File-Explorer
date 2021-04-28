#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;	
namespace fs = std::filesystem;

void getContent(fs::path path, vector<fs::path> &content) {
	for(const auto & entry : fs::directory_iterator(path)) {
		content.push_back(entry);
	}
}


void findObj(string filename, vector<fs::path> &content, fs::path &obj) {
	for(int i = 0; i < content.size(); i++) {
		if(content[i].filename() == filename) {
			obj = content[i];
		}
	}	
}


int main() {
	fs::path mainDir = fs::current_path();
	fs::path subDir;
	fs::path moveFile;

	fs::path toDir;

	vector<fs::path> mainContent;
	vector<fs::path> subContent;

	getContent(mainDir, mainContent);
	findObj("from", mainContent, subDir);
	findObj("to", mainContent, toDir);


	getContent(subDir, subContent);
	findObj("moveMe.txt", subContent, moveFile);
	
	fs::copy(moveFile, toDir);
	return 0;
}
