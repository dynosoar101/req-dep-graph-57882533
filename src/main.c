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
    //we are going to use a linkedlist to store the dependencies
    //this is because a linkedlist can point to the next node
    //ie tail can point to head. this is good as it shows a linkage
    //and is exactly how we want to represent our dependencies.
    DepNode *head = NULL, *tail = NULL; // <-- define head and tail

    //opens the file and does basic checking
    parseSrs(filePath, &head, &tail); //reas srs and updates deps linkedlist
    generateReport(head, "rdgg-report-57882533.md", filePath); //generates md file
    generateGraph(head, filePath); //prints contents of md file to terminal
    
    // Free the list
    while (head) {
        DepNode *tmp = head;
        head = head->next;
        free(tmp);
    }

    return 0;


} //eof

