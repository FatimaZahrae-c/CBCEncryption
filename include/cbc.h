#ifndef CBC_H
#define CBC_H

#include "linkedlist.h"

typedef struct CBC {
    char IV;        // Vecteur d'initialisation (un caractère)
    const char* key; // Clé de chiffrement chaine
} CBC;

// Prototypes des fonctions CBC
CBC* initializeCBC(char IV, const char* key);
Node* encryptCBC(CBC* cbc, Node* plaintext);
Node* decryptCBC(CBC* cbc, Node* ciphertext);

#endif
