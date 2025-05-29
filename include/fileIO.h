//this header file contains the input and output function of the given srs document
//it defines the prototypes for functions reading the srs as well as outputting the parsed srs

#ifndef FILEIO_H //defines FILEIO_H if not already defined
#define FILEIO_H
#include <stdio.h> //for file operations

//we use an enum to differentiate between record and dependency nodes
//this is so the graph can print either -> or --
typedef enum {
    NODE_RECORD,
    NODE_DEPENDENCY
} NodeType;

//we are going to use a linkedlist to store the dependencies
    //this is because a linkedlist can point to the next node
    //ie tail can point to head. this is good as it shows a linkage
    //and is exactly how we want to represent our dependencies.

typedef struct DepNode { // Structure for a dependency node
    NodeType type;
    int line; // Line number in the SRS file for this node
    union { // Union to hold either dependency or record information
        struct { // For dependency
            char from[32];
            char to[32];
        };
        struct { // For record
            char id[32]; //length of id
        };
    };
    struct DepNode *next;
} DepNode;

void parseSrs(char *filePath, DepNode **head, DepNode **tail); //function to read srs file
//returns a file indicating the noted dependencies

//appending to linkedlist
void addRecord(DepNode **head, DepNode **tail, const char *id, int line);
void addDependency(DepNode **head, DepNode **tail, const char *from, const char *to, int line);
//function to add a dependency to the linked list
#endif  //eof
