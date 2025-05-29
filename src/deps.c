//this source file contains the implementation of the functions for dependency graph generation
//and report generation
//it depends on its respective header file and fileIO.h
//as well as stdio, stdlib, and string.h to perform file operations
//and string operations
#include "deps.h"
#include "fileIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//prints the graph of dependencies to the terminal using the linked list
//it prints the first 3 lines of the SRS file to the terminal
void generateGraph(DepNode *head, const char *srsFile) {
    // Print the first 3 lines of the SRS file to the terminal
    FILE *in = fopen(srsFile, "r"); //opens srs file
    if (in) {
        char buf[512];
        int count = 0;
        while (fgets(buf, sizeof(buf), in) && count < 3) {
            fputs(buf, stdout); //prints the line to stdout
            count++;
        }
        fputs("\n", stdout); // Add a blank line after the header
        fclose(in);
    }

    DepNode *curr = head; //starts at the head of the linked list
    while (curr) {
        if (curr->type == NODE_RECORD) { 
            // Print record nodes with -- for dependencies
            printf("Line %d: %s --\n", curr->line, curr->id);
        } else if (curr->type == NODE_DEPENDENCY) {
            // Print dependency nodes with -> for dependencies
            printf("Line %d: %s -> %s\n", curr->line, curr->from, curr->to);
        }
        curr = curr->next; //increment
    }
}
//generates the md report of the dependencies
void generateReport(DepNode *head, const char *filename, const char *srsFile) {
    FILE *out = fopen(filename, "w"); //opens the report file for writing
    if (!out) {
        printf("Could not open report file for writing.\n");
        return;
    }

    // Print the first 3 lines of the SRS file
    FILE *in = fopen(srsFile, "r");
    if (in) {
        char buf[512];
        int count = 0;
        while (fgets(buf, sizeof(buf), in) && count < 3) {
            fputs(buf, out);
            count++;
        }
        fputs("\n", out); // Add a blank line after the header
        fclose(in);
    }
    //writes report header
    DepNode *curr = head;
    while (curr) {
        // Write each node to the report file
        if (curr->type == NODE_RECORD) {
            fprintf(out, "Line %d: %s --\n", curr->line, curr->id);
            // Add a note for record nodes
        } else if (curr->type == NODE_DEPENDENCY) {
            fprintf(out, "Line %d: %s -> %s\n", curr->line, curr->from, curr->to);
        }
        curr = curr->next;
    }

    fclose(out);
}

//eof