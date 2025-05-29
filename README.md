# eecs22l-assignment4 
This assignment is a continuation of assignment 3 and is to implement the stubs that were created. in this assignment however, I divered from what I originally stubbed after realizing that some functions could be implemented better to save for ease of creating. For instance, in the original fileIO.c, parseSrs() was meant to return a file of the parsed srs however I realized how having a function create a new file is the whole point of the assignment. Aside from being a lot of extra work, I wanted the modular programming to be modular and thus had parseSrs() instead parse and save the parsed values to then be printed into a report and graph in deps.c file.

I also edited the Makefile to actually compile as the last one was missing Main.c. I had copilot help with remaking the Makefile as I did not understand why calling make wouldn't work in the folder in MINGW.

This assignment will take the srs, parse it into a data structure and print it into the terminal as either -- or -> for a record or dependency. It will also make an md file report of these dependencies. 

CoPilot was the biggest resource I used for this program as I used it to consult the current code I had and let me know how to go about the process from there. It would automatically write my stubs from the beginning when I start with file opening and using pattern recognition in parsing the srs. CoPilot would help fill in the blanks where I got stuck and also propose reworks to my code to make it easier such as adding a new library to trim whitespace and extra quote marks. 

I use a linkedlist in the program to store the dependencies as a linkedlist consists of nodes that point to other nodes. This is a helpful and simple way of understanding dependencies as we can label a requirement node as either a record or a dependency from another requirement and have them point towards it. A lot of inspiration from Assignment 5 of EECS 22.

USE Case:
to run this program, simply run make in the terminal and enter the name of the executable file along with the filepath of your srs file. In this case, it would be ./rdgg.exe /c/Users/vince/Downloads/A04_Example_SRS.md


In gist of edits and additions to the code:
main.c uses argc and argv to take in arguments in the executable such as the filepath. It will use a linkedlist and pass it through the functions to store the dependencies for the rest of the program. It will then call parseSrs to edit this linkedlist, generateReport to create the md file of these dependencies, and generateGraph to print the report.

fileIO.c got a major rework with two new librarys: regex for req pattern recognition following the format in the assignment manual and ctype to trim whitespace, commas, and quotation marks for the function read better. The function in an essence takes in the linkedlist head and tails as arguments, parses through the whole srs file line by line and searching for patterns such as REQ-XX-DDDD-YYYY, Parent:, or Child: and save them. Using a linkedlist helps as we can label a node (a requirement) as either a dependency or record. With this, we can have the nodes point to the node they are dependent on. In parsing, the program will also print the first 3 lines of the given srs file.

deps.c orginally planned for generateGraph to create a graph from the parsed srs, instead it prints line by line of the linkedlist markdown file from generateReport. generateReport takes the linked list and creates an md file with the dependencies. 