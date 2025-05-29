//this source file implements the functions declared in io.h
//the file will parse the srs file and output the parsed srs for next use

//includes its respective header file as well as stdio and stdlib
//to perform file operations and string operations in the file
#include "fileIO.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <regex.h> //for regex operations

//the user provides a file path to the srs file
FILE *parseSrs(char *filename) {//this function parses the srs file and returns a file containing the required dependencies
    FILE *file = fopen(filename, "r"); //opens the file in read mode
    //print the first 3 lines of the file
    int lineCount = 0; //initialize line count
    char line[256]; //buffer to hold each line

    //this function checks the file's first 3 lines and prints them
    while(fgets(line, sizeof(line), file) != NULL && lineCount < 3) {
        printf("%s", line); //prints the line
        lineCount++; //increments the line count
    }

    /*find and extract the requirement tags from each line
    Using regex library to find tag of format REQ-XX-YYYY-DDDD*/
    regex_t regex; //defines regex for pattern reconigiton
    char *pattern = "REQ-[0-9]{2}-[0-9]{4}-[0-9]{4}"; //the pattern to match 
    regcomp(&regex, pattern, REG_EXTENDED); //compiles the regex pattern

    while (fgets(line, sizeof(line), file) != NULL) { //reads the rest of the file
        lineCount++; //increments the line count
        regmatch_t match; 
        char *cursor = line;
        while (regex(&regex, cursor, 1, &match, 0) == 0){
            int start = match.rm_so; //start of the match
            int end = match.rm_eo; //end of the match
            char tag[256]; //buffer to hold the tag
            strncpy(tag, cursor + start, end - start); //copies the tag from the line
            tag[end - start] = '\0'; //null-terminates the tag string
            printf("%04d: %s\n",lineCount, tag); //prints the line of tag and tag

            cursor += end; //moves the cursor to the end of the match
            offset += end; //updates the offset to the end of the match
        }
        
    }

    
    

    return;
}

//eof


