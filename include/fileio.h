#ifndef FILEIO_H
#define FILEIO_H

#include "linkedlist.h"

// Prototypes
Node* readFile(const char* filename);
void writeFile(const char* filename, Node* liste);
void encodePrintable(const char* input, char* output);
void decodePrintable(const char* input, char* output);

#endif
