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

    // Linked list for dependencies
    DepNode *head = NULL, *tail = NULL;

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

        // Trim leading spaces
        char *trimmed = line;
        while (*trimmed == ' ' || *trimmed == '\t') trimmed++;

        // Check for ID line (record)
        if (strncmp(trimmed, "ID:", 3) == 0) {
            regmatch_t match;
            if (regexec(&req_regex, trimmed, 1, &match, 0) == 0) {
                int len = match.rm_eo - match.rm_so;
                strncpy(current_id, trimmed + match.rm_so, len);
                current_id[len] = '\0';
                printf("%04d: %s --\n", lineCount, current_id); // record
            }
        }
        // Check for Parents/Parent line
        else if (strncmp(trimmed, "Parents:", 8) == 0 || strncmp(trimmed, "Parent:", 7) == 0) {
            char *parent_ptr = strchr(trimmed, ':');
            if (parent_ptr) parent_ptr++; // move past ':'
            char *token = strtok(parent_ptr, ",");
            while (token) {
                while (*token == ' ' || *token == '\t') token++;
                regmatch_t match;
                if (regexec(&req_regex, token, 1, &match, 0) == 0) {
                    char parent_id[32];
                    int len = match.rm_eo - match.rm_so;
                    strncpy(parent_id, token + match.rm_so, len);
                    parent_id[len] = '\0';
                    printf("%04d: %s -> %s\n", lineCount, parent_id, current_id); // parent
                    addDependency(&head, &tail, parent_id, current_id, lineCount);
                }
                token = strtok(NULL, ",");
            }
        }
        // Check for Children/Child line
        else if (strncmp(trimmed, "Children:", 9) == 0 || strncmp(trimmed, "Child:", 6) == 0) {
            char *child_ptr = strchr(trimmed, ':');
            if (child_ptr) child_ptr++; // move past ':'
            char *token = strtok(child_ptr, ",");
            while (token) {
                while (*token == ' ' || *token == '\t') token++;
                regmatch_t match;
                if (regexec(&req_regex, token, 1, &match, 0) == 0) {
                    char child_id[32];
                    int len = match.rm_eo - match.rm_so;
                    strncpy(child_id, token + match.rm_so, len);
                    child_id[len] = '\0';
                    printf("%04d: %s -> %s\n", lineCount, current_id, child_id); // child
                    addDependency(&head, &tail, current_id, child_id, lineCount);
                }
                token = strtok(NULL, ",");
            }
        }
    }

    regfree(&req_regex);
    fclose(file);

    // Print all dependencies from the linked list
    printf("\nDependencies stored in linked list:\n");
    DepNode *curr = head;
    while (curr) {
        printf("%04d: %s -> %s\n", curr->line, curr->from, curr->to);
        curr = curr->next;
    }

    // Free the linked list
    while (head) {
        DepNode *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void addDependency(DepNode **head, DepNode **tail, const char *from, const char *to, int line) {
    DepNode *newNode = malloc(sizeof(DepNode));
    strncpy(newNode->from, from, 32);
    strncpy(newNode->to, to, 32);
    newNode->line = line;
    newNode->next = NULL;
    if (*tail) {
        (*tail)->next = newNode;
        *tail = newNode;
    } else {
        *head = *tail = newNode;
    }
}
//eof


