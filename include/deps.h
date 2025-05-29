//this header file will define the prototypes for generating the graphs and reports
//of the srs parsed dependencies

#ifndef DEPS_H //defines DEPS_H if not already defined
#define DEPS_H
#include "fileIO.h" //this module is dependent on fileIO module
#include <stdio.h> //for file operations

void generateGraph(DepNode *head, const char *filename); //function to generate the graph of the dependencies
//takes in parsed linkedlist form parsed srs file and prints it
//prints ascii graph to console

void generateReport(DepNode *head, const char *filename, const char *srsFile); //function to generate the report of the dependencies
//returns a report detailing all of the dependencies as an md

#endif //eof