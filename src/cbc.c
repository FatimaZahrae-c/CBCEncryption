#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cbc.h"


CBC* initializeCBC(char IV, const char* key) {
    CBC* cbc = (CBC*)malloc(sizeof(CBC));
    if (!cbc) {
        printf("Erreur alloction de memoire CBC");
        return NULL;
    }
    cbc->IV = IV;
    cbc->key = key;
    return cbc;
}

// Chiffrer une liste cha�n�e avec CBC
Node* encryptCBC(CBC* cbc, Node* plaintext) {
    if (!cbc || !plaintext) {
        printf("Error: CBC or data is invalid\n");
        return NULL;
    }

    Node* ciphertext = NULL;            // Liste pour stocker les donn�es chiffr�es
    Node* temp = plaintext;             // Pointeur pour parcourir les donn�es
    char PreviousCipherBlock = cbc->IV; // Bloc pr�c�dent (IV au d�part)

    while (temp) {
        const char* plainTextData = temp->data;
        char* encryptedData = (char*)malloc(strlen(plainTextData) + 1); // Allouer pour la cha�ne chiffr�e

        // Chiffrer chaque caract�re de la cha�ne
        for (size_t i = 0; i < strlen(plainTextData); ++i) {
        encryptedData[i] = (plainTextData[i] ^ PreviousCipherBlock) ^ cbc->key[i % strlen(cbc->key)];
        PreviousCipherBlock = encryptedData[i];// Mettre � jour le bloc pr�c�dent
        }
        encryptedData[strlen(plainTextData)] = '\0'; // Terminer la cha�ne

        ciphertext = insertNode(ciphertext, encryptedData);
        free(encryptedData); // Lib�rer la m�moire temporaire
        temp = temp->next;
    }

    return ciphertext;
}

// D�chiffrer une liste cha�n�e avec CBC
Node* decryptCBC(CBC* cbc, Node* ciphertext) {
    if (!cbc || !ciphertext) {
        printf("Error: CBC or data is invalid\n");
        return NULL;
    }

    Node* plaintext = NULL;            // Liste pour stocker les donn�es d�chiffr�es
    Node* temp = ciphertext;           // Pointeur pour parcourir les donn�es chiffr�es
    char PreviousCipherBlock = cbc->IV; // Bloc pr�c�dent (IV au d�part)

  while (temp) {
    const char* cipherTextData = temp->data;
    char* decryptedData = (char*)malloc(strlen(cipherTextData) + 1); // Allouer pour la cha�ne d�chiffr�e

    // D�chiffrer chaque caract�re de la cha�ne
    for (size_t i = 0; i < strlen(cipherTextData); ++i) {
        decryptedData[i] = (cipherTextData[i] ^ cbc->key[i % strlen(cbc->key)]) ^ PreviousCipherBlock;
        PreviousCipherBlock = cipherTextData[i]; // Mettre � jour le bloc pr�c�dent
    }
    decryptedData[strlen(cipherTextData)] = '\0'; // Terminer la cha�ne

    plaintext = insertNode(plaintext, decryptedData);
    free(decryptedData); // Lib�rer la m�moire temporaire
    temp = temp->next;
}
    return plaintext;
}
