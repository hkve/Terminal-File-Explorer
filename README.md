# Terminal-File-Explorer
I very simple file explorer for the terminal, can navigate files/folders, delete copy and paste. Written in **C++** with good help from STL A fun project for me, but filled with bugs so wouldn't use it for anything important.

I learned a lot while writing the code and at this point I will probably consider a complete re-write using curse rather than working with the current code base. Anyways
it has some simple functionality that works (with a abundance of bugs). Anyways currently one can:

- (**WASD**) Movement up, left, down, rigth. Pretty self explanatory
- (**Q**) Quit the program
- (**e**) Enter directory at current cursor position
- (**q**) Move up one directory
- (**b**) Move pervious directories. Works all the way back to where you started the program
- (**I**) Show info bar with full path to current working directory
- (**C**) Show current clipboard
- (**m**) Mark a file/folder. It will be added to the clipboard
- (**M**) Unmark every file from clipboard
- (**p**) Pasts files/folders from clipboard to current working directory
- (**P**) Paste files/folders from clipboard to current cursor position (if it is a folder)
- (**r**) Delete file/folder at current posistion
- (**R**) Deletes files/folders from clipboard 
 
To compile the program, go to the main directory and type: 

```console
foo@bar:~$ make all
```

A program called **main.o** will be added to the **compiled** directory (if not already there). You can save this somewhere special and add i bash command to run it from anywhere! 
