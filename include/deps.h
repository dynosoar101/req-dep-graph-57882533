//this header file will define the prototypes for generating the graphs and reports
//of the srs parsed dependencies

ifndef DEPS_H //defines DEPS_H if not already defined
#define DEPS_H
#include "fileIO.h" //this module is dependent on fileIO module

void generateGraph(File *file); //function to generate the graph of the dependencies
//takes in parsed file from fileIO parseSrs function
//prints ascii graph to console

File *generateReport(File *file); //function to generate the report of the dependencies
//returns a report detailing all of the dependencies

endif //eof 