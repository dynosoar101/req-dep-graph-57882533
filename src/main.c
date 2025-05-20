#include "fileIO.h"
#include "deps.h"

//to be implemented
int main(void){
    //this is the main function
    //it will call the parseSrs function to parse the srs file
    //and then call the generateGraph and generateReport functions to generate the graph and report
    //it will also handle any errors that may occur
    //and return 0 if successful, or 1 if an error occurs

    //opens the file and does basic checking
    File *file = parseSrs("srs.txt");
    if (file == NULL) {
        printf("Error: Could not parse srs file\n");
        return 1;
    }

    generateGraph(file); //generates graph of the dependencies
    generateReport(file); //generates report of the dependencies

    return 0;


} //eof

