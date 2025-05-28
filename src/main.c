#include "fileIO.h"
#include "deps.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//main takes in argc and argv to allow for command line arguments
int main(int argc, char *argv[]) { 
    char *fileName = NULL; //holds file to be parsed
    if (argc < 2) { //if no command line argument is provided
        printf("Usage: %s <srs-file>\n", argv[0]); //prints usage message
        return 1; //returns error code
    }
    fileName = argv[1]; //assigns the first command line argument to fileName
    //opens the file and does basic checking
    File *file = parseSrs(fileName);
    if (file == NULL) {
        printf("Error: Could not parse srs file\n");
        return 1;
    }

    generateGraph(file); //generates graph of the dependencies
    generateReport(file); //generates report of the dependencies

    return 0;


} //eof

