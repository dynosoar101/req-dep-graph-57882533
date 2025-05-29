//this source file implements the functions declared in io.h
//the file will parse the srs file and output the parsed srs for next use

//includes its respective header file as well as stdio and stdlib
//to perform file operations and string operations in the file
#include "fileIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h> //library for trim()

//appends to the linkedlist
//we have both addRecord and addDependency functions
//to differentiate between record and dependency nodes
//this is so the graph can print either -> or --
void addRecord(DepNode **head, DepNode **tail, const char *id, int line) {
    DepNode *newNode = malloc(sizeof(DepNode)); //mem allocate
    newNode->type = NODE_RECORD; //sets type to record by default
    strncpy(newNode->id, id, 32); //copies id
    newNode->line = line; //sets the line number value to store
    newNode->next = NULL; //sets the next
    if (*tail) { //if tail is not null, append to the end
        (*tail)->next = newNode; 
        *tail = newNode;
    } else { //if tail is null, set head and tail to new node
        *head = *tail = newNode;
    }
}
//appends a dependency to the linked list
//same logic as previous function
void addDependency(DepNode **head, DepNode **tail, const char *from, const char *to, int line) {
    DepNode *newNode = malloc(sizeof(DepNode));
    newNode->type = NODE_DEPENDENCY; 
    strncpy(newNode->from, from, 32);
    strncpy(newNode->to, to, 32);
    newNode->line = line; 
    newNode->next = NULL;
    if (*tail) { //if tail is not null, append to the end
        (*tail)->next = newNode;
        *tail = newNode;
    } else { //if tail is null, set head and tail to new node
        *head = *tail = newNode;
    }
}

//formats comma separated values to be read by parseSrs()
void trim(char *str) {
    // Trim leading
    char *start = str; //start of the string pointer
    while (isspace((unsigned char)*start)) start++; //skip leading whitespace
    if (start != str) memmove(str, start, strlen(start) + 1);
    // Trim trailing
    char *end = str + strlen(str) - 1; //end of the string pointer
    while (end >= str && isspace((unsigned char)*end)) *end-- = '\0'; 
    // Trim leading and trailing quotes
}
//parses srs and updates linkedlist with dependencies
void parseSrs(char *filePath, DepNode **head, DepNode **tail) {
    FILE *file = fopen(filePath, "r"); //reads and opens file from path
    if (!file) {
        printf("Could not open file: %s\n", filePath);
        return;
    }


    char line[512]; //for line reading
    int lineCount = 0; //for line number
    char current_id[32] = ""; //for id storing
    int current_record_line = 0; //for current line

    regex_t req_regex; //uses regex to match the REQ pattern
    //REQ pattern is defined as REQ-[A-Z]{2}-[A-Z]{4}-[0-9]{4}
    const char *pattern = "REQ-[A-Z]{2}-[A-Z]{4}-[0-9]{4}";
    regcomp(&req_regex, pattern, REG_EXTENDED); //compiles regex pattern
    // Loop through each line in the file
    while (fgets(line, sizeof(line), file) != NULL) {
        //trims leading whitespace
        lineCount++;
        char *trimmed = line;
        while (*trimmed == ' ' || *trimmed == '\t') trimmed++;
        
        // ID line
        // checks if the line starts with "ID:" and matches the REQ pattern
        if (strncmp(trimmed, "ID:", 3) == 0) {
            regmatch_t match;
            if (regexec(&req_regex, trimmed, 1, &match, 0) == 0) {
                int len = match.rm_eo - match.rm_so; //get the length of the match
                strncpy(current_id, trimmed + match.rm_so, len);
                current_id[len] = '\0'; //null terminator 
                current_record_line = lineCount; //store the line number of the current record
                addRecord(head, tail, current_id, current_record_line);
            }
        }
        // Parents/Parent line
        // checks if the line starts with "Parents:" or "Parent:" and matches the REQ pattern
        else if (strncmp(trimmed, "Parents:", 8) == 0 || strncmp(trimmed, "Parent:", 7) == 0) {
            char *parent_ptr = strchr(trimmed, ':');
            if (parent_ptr) parent_ptr++;
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
        // checks if the line starts with "Children:" or "Child:" and matches the REQ pattern
        else if (strncmp(trimmed, "Children:", 9) == 0 || strncmp(trimmed, "Child:", 6) == 0) {
            char *child_ptr = strchr(trimmed, ':');
            if (child_ptr) child_ptr++;
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

    regfree(&req_regex); //kills the regex
    fclose(file); //closes
}
//eof


