# CBC Encryption Project

#Overview
This project implements **Cipher Block Chaining (CBC) encryption and decryption** using **linked lists** in C. It allows users to securely encrypt text data, store it in a file, and decrypt it back. The program features an **interactive console interface** with a structured workflow.

---

# Features
- **Encrypts and decrypts data using CBC encryption.**
- **Stores and retrieves data from files securely.**
- **Uses linked lists to manage text data efficiently.**
- **Displays a user-friendly console interface with colors and progress indicators.**
- **Handles errors and ensures robust memory management.**

---

# Technologies Used
- **C Language** (for performance and low-level memory management)
- **File Handling** (for reading/writing encrypted and plaintext data)
- **Linked Lists** (to dynamically store text as nodes)
- **Console Styling** (ANSI color codes for a better user experience)
- **Git & GitHub** (for version control and collaboration)

---

#Installation
###  Clone the Repository
```bash
git clone https://github.com/FatimaZahrae-c/CBCEncryption.git
cd CBCEncryption
```

### Compile the Code
Using **GCC (Linux/macOS)**:
```bash
gcc -o cbcproject main.c cbc.c linkedlist.c fileio.c -Wall
```
Using **Code::Blocks (Windows)**:
- Open `CBCProject.cbp` in **Code::Blocks**.
- Click **Build & Run**.

---

# Usage
### Run the Program
```bash
./cbc_project
```
### Program Flow
1. **Reads plaintext from `input.txt`.**
2. **Encrypts the data using CBC encryption.**
3. **Saves the encrypted data into `encrypted.txt`.**
4. **Reads the encrypted data from the file.**
5. **Decrypts it back to the original plaintext.**
6. **Displays each step in a visually clear format.**

---



---

#Project Structure
```
CBC-Encryption/
│-- src/
│   ├── main.c          # Main program execution
│   ├── cbc.c           # Encryption and decryption functions
│   ├── linkedlist.c    # Linked list operations
│   ├── fileio.c        # File handling operations
│-- include/
│   ├── cbc.h
│   ├── linkedlist.h
│   ├── fileio.h
│-- input.txt           # Plaintext input file
│-- encrypted.txt       # Encrypted output file
│-- README.md           # Project documentation
│-- CBC_Project.cbp     # Code::Blocks project file
```

---



---



**Feel free to customize this README with your GitHub username, extra details, or improvements!**
