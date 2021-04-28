all: compile run


cppFiles = main.cpp \
		   object.cpp \
		   file.cpp \
		   folder.cpp \
		   interface.cpp \
		   commands.cpp \
		   display.cpp \
		   load.cpp \


cppFiles := src/$(cppFiles)$
compile:
	g++ $(cppFiles) -o main.o -std=c++17 -ltermcap 

run:
	./main.o
