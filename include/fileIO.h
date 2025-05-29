//this header file contains the input and output function of the given srs document
//it defines the prototypes for functions reading the srs as well as outputting the parsed srs

#ifndef FILEIO_H //defines FILEIO_H if not already defined
#define FILEIO_H
#include <stdio.h> //for file operations

typedef enum {
    NODE_RECORD,
    NODE_DEPENDENCY
} NodeType;

typedef struct DepNode {
    NodeType type;
    int line;
    union {
        struct { // For dependency
            char from[32];
            char to[32];
        };
        struct { // For record
            char id[32];
        };
    };
    struct DepNode *next;
} DepNode;

void parseSrs(char *filePath); //function to read srs file
//returns a file indicating the noted dependencies

void addRecord(DepNode **head, DepNode **tail, const char *id, int line);
void addDependency(DepNode **head, DepNode **tail, const char *from, const char *to, int line);
//function to add a dependency to the linked list
#endif  //eof
