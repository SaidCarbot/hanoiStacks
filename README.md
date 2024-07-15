# hanoiStacks
An implementation of dynamic stacks using the algorithm to solve the Tower of Hanoi with structures in C and the visual part in Python


The code is described in Spanish,
The code is the final project for the subject “Algorithms and Data Structures” at the Escuela Superior de Cómputo (ESCOM),
It was the joint work of three students, two of whom prefer not to give their names.
The code is limited to 8 disks, but only 7 lines need to be modified between the .c and the .py files to use more disks, this line have the the comment “MODIFICABLE PARA AUMENTAR” 

About the implementation:
There are three files:
1) gui.py; which is the Graphic User Interface
2) hanoi.c; which is the creation of the data structures and the algorithm to solve the Tower of Hanoi
3) movi.txt; which is the file where the movements emitted by hanoi.c are printed so that gui.py can read them later

Steps to run the program:

	1) Download the three files, gui.py, hanoi.c, and movi.txt into the same folder;
 
	2) Compile hanoi.c; run hanoi.c with the command "./hanoi > movi.txt"; the program will then wait to receive a number between 1 and 8 (the number of disks), so enter [1-8] and press enter. This will update the list of movements printed in movi.txt
 
	3) Run the GUI with the command "python gui.py", a window will open with two sections where you can enter the number of disks for which you want to solve the game (they may or may not be the same as those entered in hanoi.c) and the name of the file from which gui.py will read the movements (in this case "movi.txt")
 
	4) Press the START button and the tower with the selected number of disks will be displayed, solving the tower by moving it from one peg to another.

