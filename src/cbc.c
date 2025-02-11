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

// Chiffrer une liste chaînée avec CBC
Node* encryptCBC(CBC* cbc, Node* plaintext) {
    if (!cbc || !plaintext) {
        printf("Error: CBC or data is invalid\n");
        return NULL;
    }

    Node* ciphertext = NULL;            // Liste pour stocker les données chiffrées
    Node* temp = plaintext;             // Pointeur pour parcourir les données
    char PreviousCipherBlock = cbc->IV; // Bloc précédent (IV au départ)

    while (temp) {
        const char* plainTextData = temp->data;
        char* encryptedData = (char*)malloc(strlen(plainTextData) + 1); // Allouer pour la chaîne chiffrée

        // Chiffrer chaque caractère de la chaîne
        for (size_t i = 0; i < strlen(plainTextData); ++i) {
        encryptedData[i] = (plainTextData[i] ^ PreviousCipherBlock) ^ cbc->key[i % strlen(cbc->key)];
        PreviousCipherBlock = encryptedData[i];// Mettre à jour le bloc précédent
        }
        encryptedData[strlen(plainTextData)] = '\0'; // Terminer la chaîne

        ciphertext = insertNode(ciphertext, encryptedData);
        free(encryptedData); // Libérer la mémoire temporaire
        temp = temp->next;
    }

    return ciphertext;
}

// Déchiffrer une liste chaînée avec CBC
Node* decryptCBC(CBC* cbc, Node* ciphertext) {
    if (!cbc || !ciphertext) {
        printf("Error: CBC or data is invalid\n");
        return NULL;
    }

    Node* plaintext = NULL;            // Liste pour stocker les données déchiffrées
    Node* temp = ciphertext;           // Pointeur pour parcourir les données chiffrées
    char PreviousCipherBlock = cbc->IV; // Bloc précédent (IV au départ)

  while (temp) {
    const char* cipherTextData = temp->data;
    char* decryptedData = (char*)malloc(strlen(cipherTextData) + 1); // Allouer pour la chaîne déchiffrée

    // Déchiffrer chaque caractère de la chaîne
    for (size_t i = 0; i < strlen(cipherTextData); ++i) {
        decryptedData[i] = (cipherTextData[i] ^ cbc->key[i % strlen(cbc->key)]) ^ PreviousCipherBlock;
        PreviousCipherBlock = cipherTextData[i]; // Mettre à jour le bloc précédent
    }
    decryptedData[strlen(cipherTextData)] = '\0'; // Terminer la chaîne

    plaintext = insertNode(plaintext, decryptedData);
    free(decryptedData); // Libérer la mémoire temporaire
    temp = temp->next;
}
    return plaintext;
}
