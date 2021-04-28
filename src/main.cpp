#include "interface.hpp"
using namespace std;

int main(int argc, char const *argv[])
{

	Interface currentDir(fs::current_path());
	currentDir.run();
	
	return 0;
}




	/*
	folder1.updateDisplayName();
	cout << folder1.getDisplayName() <<endl;
	folder1.setHighlight(true);
	
	folder1.updateDisplayName();
	cout << folder1.getDisplayName() <<endl;
	
	folder1.setMarked(true);
	folder1.updateDisplayName();
	cout << folder1.getDisplayName() <<endl;
	
	folder1.setHighlight(false);
	folder1.updateDisplayName();
	cout << folder1.getDisplayName() <<endl;
	*/