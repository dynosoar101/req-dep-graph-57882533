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

//to be implemented
void generateGraph(DepNode *head, const char *filename) {
    FILE *out = fopen(filename, "w");
    if (!out) {
        printf("Could not open graph file for writing.\n");
        return;
    }

    DepNode *curr = head;
    while (curr) {
        if (curr->type == NODE_RECORD) {
            fprintf(out, "Line %d: %s --\n", curr->line, curr->id);
        } else if (curr->type == NODE_DEPENDENCY) {
            fprintf(out, "Line %d: %s -> %s\n", curr->line, curr->from, curr->to);
        }
        curr = curr->next;
    }

    fclose(out);
}

void generateReport(DepNode *head, const char *filename, const char *srsFile) {
    FILE *out = fopen(filename, "w");
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

    DepNode *curr = head;
    while (curr) {
        if (curr->type == NODE_RECORD) {
            fprintf(out, "Line %d: %s --\n", curr->line, curr->id);
        } else if (curr->type == NODE_DEPENDENCY) {
            fprintf(out, "Line %d: %s -> %s\n", curr->line, curr->from, curr->to);
        }
        curr = curr->next;
    }

    fclose(out);
}

//eof