#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "linkedlist.h"
#include "cbc.h"
#include "fileio.h"

// Function to change text color
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

// Function to display a title screen
void displayTitleScreen() {
    setColor(10); // Green
    printf("\n");
    printf("=========================================\n");
    printf("         Welcome to CBC Encryption       \n");
    printf("=========================================\n");
    setColor(7); // Reset
}

// Function to display a progress message
void showProgress(const char* step) {
    setColor(14); // Yellow
    printf("\n%s in progress", step);
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        Sleep(500);     // Pause for half a second
    }
    printf(" Done!\n");
    setColor(7); // Reset
}

int main() {

    displayTitleScreen();

    // Step 1: Read plaintext from file
    showProgress("Step 1: Reading plaintext from file");
    Node* plaintext = readFile("src/input.txt");
    if (!plaintext) {
        setColor(12); // Red
        printf("Error: Could not read the input file.\n");
        setColor(7); // Reset
        return 1;
    }
    setColor(10); // Green
    printf("Plaintext data read successfully:\n");
    displayList(plaintext);
    setColor(7); // Reset

    // Step 2: Initialize CBC
    showProgress("Step 2: Initializing CBC");
    CBC* cbc = initializeCBC('A', "secret");
    if (!cbc) {
        setColor(12); // Red
        printf("Error: Failed to initialize CBC.\n");
        setColor(7); // Reset
        freeList(plaintext);
        return 1;
    }
    setColor(10); // Green
    printf("CBC initialized successfully!\n");
    setColor(7); // Reset

    // Step 3: Encrypt plaintext
    showProgress("Step 3: Encrypting plaintext");
    Node* ciphertext = encryptCBC(cbc, plaintext);
    if (!ciphertext) {
        setColor(12); // Red
        printf("Error: Encryption failed.\n");
        setColor(7); // Reset
        freeList(plaintext);
        free(cbc);
        return 1;
    }
    setColor(10); // Green
    printf("Ciphertext generated successfully:\n");
    displayList(ciphertext);
    setColor(7); // Reset

    // Step 4: Write ciphertext to file
    showProgress("Step 4: Writing ciphertext to file");
    writeFile("src/encrypted.txt", ciphertext);
    setColor(10); // Green
    printf("Ciphertext written to file 'src/encrypted.txt'.\n");
    setColor(7); // Reset

    // Step 5: Read ciphertext from file
    showProgress("Step 5: Reading ciphertext from file");
    Node* encryptedFromFile = readFile("src/encrypted.txt");
    if (!encryptedFromFile) {
        setColor(12); // Red
        printf("Error: Could not read ciphertext from file.\n");
        setColor(7); // Reset
        freeList(plaintext);
        freeList(ciphertext);
        free(cbc);
        return 1;
    }
    setColor(10); // Green
    printf("Ciphertext read from file successfully:\n");
    displayList(encryptedFromFile);
    setColor(7); // Reset

    // Step 6: Decrypt ciphertext
    showProgress("Step 6: Decrypting ciphertext");
    Node* decryptedText = decryptCBC(cbc, encryptedFromFile);
    if (!decryptedText) {
        setColor(12); // Red
        printf("Error: Decryption failed.\n");
        setColor(7); // Reset
        freeList(plaintext);
        freeList(ciphertext);
        freeList(encryptedFromFile);
        free(cbc);
        return 1;
    }
    setColor(10); // Green
    printf("Decrypted text successfully:\n");
    displayList(decryptedText);
    setColor(7); // Reset

    // Cleanup
    freeList(plaintext);
    freeList(ciphertext);
    freeList(encryptedFromFile);
    freeList(decryptedText);
    free(cbc);

    // Final Message
    setColor(10); // green
    printf("\n=========================================\n");
    printf("Thank you for using CBC Encryption!\n");
    printf("=========================================\n");
    setColor(7); // Reset

    return 0;
}
