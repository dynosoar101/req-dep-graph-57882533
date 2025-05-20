//this header file contains the input and output functions of the given srs document
//it defines the prototypes for functions reading the srs as well as outputting the parsed srs

#ifndef IO_H //defines IO_H if not already defined
#define IO_H


void read_srs(char *filename, struct srs *srs);

void write_srs(char *filename, struct srs *srs);

#endif  //eof
