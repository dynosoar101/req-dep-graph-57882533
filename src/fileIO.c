//this source file implements the functions declared in io.h
//the file will parse the srs file and output the parsed srs for next use

//includes its respective header file as well as stdio and stdlib
//to perform file operations and string operations in the file
#include "fileIO.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <regex.h> //for regex operations

void parseSrs(char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        printf("Could not open file: %s\n", filePath);
        return;
    }

    char line[256];
    int lineCount = 0;
    char current_id[32] = "";

    // Print the first 3 lines
    while (fgets(line, sizeof(line), file) != NULL && lineCount < 3) {
        printf("%s", line);
        lineCount++;
    }

    regex_t req_regex;
    const char *pattern = "REQ-[A-Z]{2}-[A-Z]{4}-[0-9]{4}";
    regcomp(&req_regex, pattern, REG_EXTENDED);

    // Continue scanning the rest of the file
    while (fgets(line, sizeof(line), file) != NULL) {
        lineCount++;

        // Check for ID line (record)
        if (strncmp(line, "ID:", 3) == 0) {
            regmatch_t match;
            if (regexec(&req_regex, line, 1, &match, 0) == 0) {
                int len = match.rm_eo - match.rm_so;
                strncpy(current_id, line + match.rm_so, len);
                current_id[len] = '\0';
                printf("%04d: %s --\n", lineCount, current_id); // record
            }
        }
        // Check for Parents line
        else if (strncmp(line, "Parents:", 8) == 0) {
            char *parent_ptr = line + 8;
            char *token = strtok(parent_ptr, ",");
            while (token) {
                // Remove leading/trailing whitespace
                while (*token == ' ' || *token == '\t') token++;
                regmatch_t match;
                if (regexec(&req_regex, token, 1, &match, 0) == 0) {
                    char parent_id[32];
                    int len = match.rm_eo - match.rm_so;
                    strncpy(parent_id, token + match.rm_so, len);
                    parent_id[len] = '\0';
                    printf("%04d: %s -> %s\n", lineCount, parent_id, current_id); // parent
                }
                token = strtok(NULL, ",");
            }
        }
        // Check for Children line
        else if (strncmp(line, "Children:", 9) == 0) {
            char *child_ptr = line + 9;
            char *token = strtok(child_ptr, ",");
            while (token) {
                // Remove leading/trailing whitespace
                while (*token == ' ' || *token == '\t') token++;
                regmatch_t match;
                if (regexec(&req_regex, token, 1, &match, 0) == 0) {
                    char child_id[32];
                    int len = match.rm_eo - match.rm_so;
                    strncpy(child_id, token + match.rm_so, len);
                    child_id[len] = '\0';
                    printf("%04d: %s -> %s\n", lineCount, current_id, child_id); // child
                }
                token = strtok(NULL, ",");
            }
        }
    }

    regfree(&req_regex);
    fclose(file);
}
//eof


