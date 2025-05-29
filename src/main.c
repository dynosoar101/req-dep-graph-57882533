#include "fileIO.h"
#include "deps.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//main takes in argc and argv to allow for command line arguments
int main(int argc, char *argv[]) { 
    if (argc < 2) { //if no command line argument is provided
        printf("Usage: %s <srs-file>\n", argv[0]); //prints usage message
        return 1; //returns error code
    }
    char *filePath = argv[1]; //assigns the first command line argument to fileName
    DepNode *head = NULL, *tail = NULL; // <-- define head and tail

    //opens the file and does basic checking
    parseSrs(filePath, &head, &tail);
    generateReport(head, "rdgg-report-57882533.md", filePath);

    // Free the list
    while (head) {
        DepNode *tmp = head;
        head = head->next;
        free(tmp);
    }

    return 0;


} //eof

