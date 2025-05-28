//this header file contains the input and output function of the given srs document
//it defines the prototypes for functions reading the srs as well as outputting the parsed srs

#ifndef FILEIO_H //defines FILEIO_H if not already defined
#define FILEIO_H

typedef struct {
    char *id; //unique identifier for the srs
    char *title; //name of the srs
    char *parent; //description of the srs
    char *child; //author of the srs
} File; //structure to hold the srs information

File *parseSrs(char *filename); //function to read srs file
//returns a file indicating the noted dependencies

#endif  //eof
