#include <iostream>
#include <string>
#include <map>

using namespace std;


class Test
{
public:
	typedef void (Test::*func)();
	Test(string msg_);
	void func1();
	void func2();
	void call(string id);

private:
 	map<string, func> funcMap;
	string msg;
};


Test::Test(string msg_) {
	msg = msg_;
	
	funcMap.insert( std::make_pair("1", &Test::func1 ) );
	funcMap.insert( std::make_pair("2", &Test::func2 ) );
}

void Test::func1() {
	cout << "func 1 " << msg <<endl;
}


void Test::func2() {
	cout << "func 2 " << msg <<endl;
}

void Test::call(string id) {
	if(funcMap.find(id) == funcMap.end()) {
		cout << "not a cmd" <<endl;
	}
	else {
	func fp = funcMap[id];
	(this->*fp)();
	}
}

int main() {
	Test test = Test("heihei");
	test.call("1");
	test.call("4");
	test.call("2");
}