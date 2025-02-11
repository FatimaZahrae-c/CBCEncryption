#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileio.h"
#include "linkedlist.h"

void encodePrintable(const char* input, char* output) {
    size_t j = 0;
    for (size_t i = 0; i < strlen(input); ++i) {
        if (input[i] < 32 || input[i] > 126) { // Si le caract�re est non imprimable
            j += sprintf(output + j, "\\x%02X", (unsigned char)input[i]); // Convertir en hexad�cimal
        } else {
            output[j++] = input[i]; // Sinon, garder le caract�re tel quel
        }
    }
    output[j] = '\0'; // Terminer la cha�ne
}
void decodePrintable(const char* input, char* output) {
    size_t i = 0, j = 0;
    while (input[i] != '\0') {
        if (input[i] == '\\' && input[i + 1] == 'x') { // Si c'est une s�quence hexad�cimale
            unsigned int value;
            sscanf(input + i + 2, "%2X", &value); // Convertir en entier
            output[j++] = (char)value;
            i += 4;
        } else {
            output[j++] = input[i++]; // Sinon, copier le caract�re
        }
    }
    output[j] = '\0'; // Terminer la cha�ne
}


// Lire un fichier et stocker les donn�es (cha�nes) dans une liste cha�n�e
Node* readFile(const char* filename) {
    FILE* file = fopen(filename, "r"); // Ouvrir le fichier en mode lecture
    if (!file) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }

    Node* list = NULL;
    char buffer[512]; // Tampon pour lire chaque ligne

    while (fgets(buffer, sizeof(buffer), file)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0'; // Supprimer le caract�re de nouvelle ligne
        }

        // Diviser la ligne en mots � l'aide de strtok
        char* token = strtok(buffer, " "); // Diviser par espaces
        while (token != NULL) {
            list = insertNode(list, token); // Ins�rer chaque mot dans un n�ud
            token = strtok(NULL, " "); // Passer au mot suivant
        }
    }

    fclose(file); // Fermer le fichier apr�s lecture
    return list;
}






// �crire les donn�es de la liste cha�n� dans un fichier
void writeFile(const char* filename, Node* list) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        return;
    }

    Node* temp = list;
    char encodedBuffer[1024]; // Tampon pour stocker les donn�es encod�es
    while (temp) {
        encodePrintable(temp->data, encodedBuffer); // Encoder les donn�es
        fprintf(file, "%s\n", encodedBuffer); // �crire les donn�es encod�es
        temp = temp->next;
    }

    fclose(file);
}




