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

    // Print the first 3 lines
    while (fgets(line, sizeof(line), file) != NULL && lineCount < 3) {
        printf("%s", line);
        lineCount++;
    }

    // Prepare regex for requirement pattern
    regex_t regex;
    const char *pattern = "REQ-[A-Z]{2}-[A-Z]{4}-[0-9]{4}";
    regcomp(&regex, pattern, REG_EXTENDED);

    // Continue scanning the rest of the file
    while (fgets(line, sizeof(line), file) != NULL) {
        lineCount++;
        regmatch_t match;
        char *cursor = line;
        int offset = 0;
        while (regexec(&regex, cursor, 1, &match, 0) == 0) {
            int len = match.rm_eo - match.rm_so;
            char req_id[32];
            strncpy(req_id, cursor + match.rm_so, len);
            req_id[len] = '\0';
            printf("%04d: %s\n", lineCount, req_id);
            cursor += match.rm_eo;
            offset += match.rm_eo;
        }
    }

    regfree(&regex);
    fclose(file);
}
//eof


