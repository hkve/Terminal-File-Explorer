all: compile run
sandbox: compile_sandbox run_sandbox


cppFiles = src/object.cpp \
		   src/file.cpp \
		   src/folder.cpp \
		   src/interface.cpp \
		   src/commands.cpp \
		   src/display.cpp \
		   src/load.cpp \


compile:
	g++ $(cppFiles) src/main.cpp -o compiled/main.o -std=c++17 -ltermcap 

run:
	./compiled/main.o

compile_sandbox:
	g++ $(cppFiles) src/sandbox.cpp -o compiled/sandbox.o -std=c++17 -ltermcap

run_sandbox: 
	./compiled/sandbox.o