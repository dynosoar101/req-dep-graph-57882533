# eecs22l-assignment3
this assignment is the start to a series of assignments dedicated to making a program that takes in an srs and generates a report and graph of the dependecies of a program

for this assignment, I structured the examples very similarly to a project we did in 
EECS 22 where our program to make image processing functions was broken down into a modular base of headers and source files. In such fashion, this assignment only hosts 2 header files, one called fileIO.h for reading a file and outputting a parsed file, and one called deps.h for taking in the read file and generating both a graph and report of the dependencies. 

The dependencies in this program are that main.c depends on deps.c which in turn depends on fileIO.c. We also use stdio, stdlib, and string.h for parsing and file commands. My thought process was in fileIO.h and fileIO.c, we take in a struct known as File, which has data items for author, date, and most importantly description. In reading this srs, we generate a file with the dependencies.

This fileIO.c and fileIO.h is then used by deps.c and deps.h to generate a graph and report file of the dependencies. The graph is a simple ascii dependency diagram printed to the terminal and the report is another file struct detailing the dependencies we need.

The final file main.c simply puts these together. No openai was used for this assignment as the base was inspired from another assignment. Only copilot was used to autofill blanks in the code or explain the thought process for how to read a file and make one.