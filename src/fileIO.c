//this source file implements the functions declared in io.h
//the file will parse the srs file and output the parsed srs for next use

//includes its respective header file as well as stdio and stdlib
//to perform file operations and string operations in the file
#include "fileIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h> //for regex operations
#include <ctype.h>

void addRecord(DepNode **head, DepNode **tail, const char *id, int line) {
    DepNode *newNode = malloc(sizeof(DepNode));
    newNode->type = NODE_RECORD;
    strncpy(newNode->id, id, 32);
    newNode->line = line;
    newNode->next = NULL;
    if (*tail) {
        (*tail)->next = newNode;
        *tail = newNode;
    } else {
        *head = *tail = newNode;
    }
}

void addDependency(DepNode **head, DepNode **tail, const char *from, const char *to, int line) {
    DepNode *newNode = malloc(sizeof(DepNode));
    newNode->type = NODE_DEPENDENCY;
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

// Helper to trim leading/trailing whitespace in-place
void trim(char *str) {
    // Trim leading
    while (isspace((unsigned char)*str)) str++;
    // If all spaces
    if (*str == 0) return;
    // Trim trailing
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
}

void parseSrs(char *filePath, DepNode **head, DepNode **tail) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        printf("Could not open file: %s\n", filePath);
        return;
    }

    char line[512];
    int lineCount = 0;
    char current_id[32] = "";
    int current_record_line = 0;

    // Print the first 3 lines
    while (fgets(line, sizeof(line), file) != NULL && lineCount < 3) {
        printf("%s", line);
        lineCount++;
    }
    lineCount++; // Increment lineCount for the first 3 lines

    regex_t req_regex;
    const char *pattern = "REQ-[A-Z]{2}-[A-Z]{4}-[0-9]{4}";
    regcomp(&req_regex, pattern, REG_EXTENDED);

    while (fgets(line, sizeof(line), file) != NULL) {
        lineCount++;
        char *trimmed = line;
        while (*trimmed == ' ' || *trimmed == '\t') trimmed++;

        // ID line
        if (strncmp(trimmed, "ID:", 3) == 0) {
            regmatch_t match;
            if (regexec(&req_regex, trimmed, 1, &match, 0) == 0) {
                int len = match.rm_eo - match.rm_so;
                strncpy(current_id, trimmed + match.rm_so, len);
                current_id[len] = '\0';
                current_record_line = lineCount;
                addRecord(head, tail, current_id, current_record_line);
            }
        }
        // Parents/Parent line
        else if (strncmp(trimmed, "Parents:", 8) == 0 || strncmp(trimmed, "Parent:", 7) == 0) {
            char *parent_ptr = strchr(trimmed, ':');
            if (parent_ptr) parent_ptr++;
            // Tokenize and trim each parent
            char *token = strtok(parent_ptr, ",");
            while (token) {
                trim(token);
                regmatch_t match;
                if (regexec(&req_regex, token, 1, &match, 0) == 0) {
                    char parent_id[32];
                    int len = match.rm_eo - match.rm_so;
                    strncpy(parent_id, token + match.rm_so, len);
                    parent_id[len] = '\0';
                    addDependency(head, tail, parent_id, current_id, lineCount);
                }
                token = strtok(NULL, ",");
            }
        }
        // Children/Child line
        else if (strncmp(trimmed, "Children:", 9) == 0 || strncmp(trimmed, "Child:", 6) == 0) {
            char *child_ptr = strchr(trimmed, ':');
            if (child_ptr) child_ptr++;
            // Tokenize and trim each child
            char *token = strtok(child_ptr, ",");
            while (token) {
                trim(token);
                regmatch_t match;
                if (regexec(&req_regex, token, 1, &match, 0) == 0) {
                    char child_id[32];
                    int len = match.rm_eo - match.rm_so;
                    strncpy(child_id, token + match.rm_so, len);
                    child_id[len] = '\0';
                    addDependency(head, tail, current_id, child_id, lineCount);
                }
                token = strtok(NULL, ",");
            }
        }
    }

    regfree(&req_regex);
    fclose(file);

    // Print all records and dependencies
    DepNode *curr = *head;
    while (curr) {
        if (curr->type == NODE_RECORD) {
            printf("Line %d: %s --\n", curr->line, curr->id);
        } else if (curr->type == NODE_DEPENDENCY) {
            printf("Line %d: %s -> %s\n", curr->line, curr->from, curr->to);
        }
        curr = curr->next;
    }

    // Free the list
    while (*head) {
        DepNode *tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}
//eof


