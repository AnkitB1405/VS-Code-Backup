#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // For the 'bool' type

// --- 1. DATA STRUCTURES ---

#define FILENAME "library.csv" // Define the database file
#define MAX_LINE_LEN 256        // Max length for a line in the CSV

/**
 * @brief Structure for the book data
 */
typedef struct Book {
    char isbn[20];
    char title[100];
    char author[100];
    bool isAvailable;
} Book;

/**
 * @brief Structure for the Binary Search Tree node
 */
typedef struct TreeNode {
    Book data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// --- 2. CORE BST & UTILITY FUNCTIONS ---
// (These are the same as before)

TreeNode* createNode(Book newBook);
TreeNode* addBook(TreeNode* root, Book newBook);
void printBookDetails(Book book);
TreeNode* searchByISBN(TreeNode* root, const char* isbn);

// --- 3. CSV DATA MANAGEMENT FUNCTIONS (NEW) ---

/**
 * @brief (Helper for saving) Recursively traverses the tree and writes to the file
 */
void saveTreeRecursive(FILE* file, TreeNode* node) {
    if (node == NULL) {
        return;
    }
    
    // Write current node's data in CSV format
    fprintf(file, "%s,%s,%s,%d\n",
            node->data.isbn,
            node->data.title,
            node->data.author,
            node->data.isAvailable ? 1 : 0); // Write 1 for true, 0 for false
            
    // Recurse on children
    saveTreeRecursive(file, node->left);
    saveTreeRecursive(file, node->right);
}

/**
 * @brief Saves the entire BST to the CSV file (overwrites existing file)
 */
void saveDataToFile(TreeNode* root, const char* filename) {
    FILE* file = fopen(filename, "w"); // "w" = write mode (creates or overwrites)
    if (file == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return;
    }

    printf("Saving data to %s...\n", filename);
    saveTreeRecursive(file, root); // Call the recursive helper
    
    fclose(file);
    printf("Data saved successfully.\n");
}

/**
 * @brief Loads data from the CSV file and builds the BST
 * @return The root of the newly created BST
 */
TreeNode* loadDataFromFile(const char* filename) {
    FILE* file = fopen(filename, "r"); // "r" = read mode
    if (file == NULL) {
        printf("Info: No existing '%s' found. Starting a new library.\n", filename);
        return NULL; // Return an empty tree
    }

    printf("Loading data from %s...\n", filename);
    TreeNode* root = NULL;
    char line[MAX_LINE_LEN];

    while (fgets(line, sizeof(line), file)) {
        Book newBook;
        char* token;

        // Strip newline character if present
        line[strcspn(line, "\n")] = 0;

        // 1. Get ISBN
        token = strtok(line, ",");
        if (token == NULL) continue; // Skip empty/malformed line
        strcpy(newBook.isbn, token);

        // 2. Get Title
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strcpy(newBook.title, token);

        // 3. Get Author
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strcpy(newBook.author, token);

        // 4. Get Availability
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newBook.isAvailable = (atoi(token) == 1); // Convert "1" or "0" string to bool

        // Add the loaded book to the tree
        root = addBook(root, newBook);
    }

    fclose(file);
    printf("Data loaded successfully.\n");
    return root;
}


// --- 4. LIBRARY FUNCTIONALITIES ---
// (These are the same as before)

void borrowBook(TreeNode* root, const char* isbn);
void returnBook(TreeNode* root, const char* isbn);
void searchByTitle(TreeNode* root, const char* titleQuery);
void searchByAuthor(TreeNode* root, const char* authorQuery);
void displayAllBooks(TreeNode* root);
void freeTree(TreeNode* root);


// --- 5. MAIN FUNCTION (MODIFIED) ---

int main() {
    TreeNode* root = NULL; // Start with an empty tree
    int choice;
    char isbn[20], title[100], author[100];

    // --- Load data from CSV file ---
    root = loadDataFromFile(FILENAME);

    do {
        printf("\n--- Library Management System ---\n");
        printf("1. Add New Book\n");
        printf("2. Borrow Book\n");
        printf("3. Return Book\n");
        printf("4. Search by Title\n");
        printf("5. Search by Author\n");
        printf("6. Display All Books (by ISBN)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n');
            continue;
        }
        while(getchar() != '\n'); 

        switch (choice) {
            case 1:
                printf("Enter ISBN: ");
                fgets(isbn, 20, stdin); isbn[strcspn(isbn, "\n")] = 0;
                printf("Enter Title: ");
                fgets(title, 100, stdin); title[strcspn(title, "\n")] = 0;
                printf("Enter Author: ");
                fgets(author, 100, stdin); author[strcspn(author, "\n")] = 0;

                Book newBook;
                strcpy(newBook.isbn, isbn);
                strcpy(newBook.title, title);
                strcpy(newBook.author, author);
                newBook.isAvailable = true;
                
                root = addBook(root, newBook);
                printf("Book added!\n");
                break;
            case 2:
                printf("Enter ISBN to borrow: ");
                fgets(isbn, 20, stdin); isbn[strcspn(isbn, "\n")] = 0;
                borrowBook(root, isbn);
                break;
            case 3:
                printf("Enter ISBN to return: ");
                fgets(isbn, 20, stdin); isbn[strcspn(isbn, "\n")] = 0;
                returnBook(root, isbn);
                break;
            case 4:
                printf("Enter Title to search: ");
                fgets(title, 100, stdin); title[strcspn(title, "\n")] = 0;
                searchByTitle(root, title);
                break;
            case 5:
                printf("Enter Author to search: ");
                fgets(author, 100, stdin); author[strcspn(author, "\n")] = 0;
                searchByAuthor(root, author);
                break;
            case 6:
                printf("\n--- Displaying All Books (sorted by ISBN) ---\n");
                if (root == NULL) {
                    printf("The library is empty.\n");
                } else {
                    displayAllBooks(root);
                }
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    // --- Save data back to CSV file before exiting ---
    saveDataToFile(root, FILENAME);

    // Clean up allocated memory
    freeTree(root);
    
    return 0;
}


// --- FUNCTION IMPLEMENTATIONS (UNCHANGED) ---
// (Paste all the helper functions from the previous answer here)

TreeNode* createNode(Book newBook) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("FATAL: Memory allocation failed!\n");
        exit(1); 
    }
    newNode->data = newBook;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void printBookDetails(Book book) {
    printf("----------------------------------------\n");
    printf("  Title:    %s\n", book.title);
    printf("  Author:   %s\n", book.author);
    printf("  ISBN:     %s\n", book.isbn);
    printf("  Status:   %s\n", book.isAvailable ? "Available" : "Borrowed");
    printf("----------------------------------------\n");
}

TreeNode* addBook(TreeNode* root, Book newBook) {
    if (root == NULL) {
        return createNode(newBook);
    }
    int cmp = strcmp(newBook.isbn, root->data.isbn);
    if (cmp < 0) {
        root->left = addBook(root->left, newBook);
    } else if (cmp > 0) {
        root->right = addBook(root->right, newBook);
    } else {
        // No error print here, as it's noisy when loading from file
        // If you want to see duplicates on *manual* add, move the
        // printf("Error: Book... exists") to the 'case 1' in main.
    }
    return root;
}

TreeNode* searchByISBN(TreeNode* root, const char* isbn) {
    if (root == NULL || strcmp(root->data.isbn, isbn) == 0) {
        return root;
    }
    if (strcmp(isbn, root->data.isbn) > 0) {
        return searchByISBN(root->right, isbn);
    }
    return searchByISBN(root->left, isbn);
}

void borrowBook(TreeNode* root, const char* isbn) {
    TreeNode* bookNode = searchByISBN(root, isbn);
    if (bookNode == NULL) {
        printf("Error: Book with ISBN %s not found.\n", isbn);
    } else if (!bookNode->data.isAvailable) {
        printf("Info: Book '%s' is already borrowed.\n", bookNode->data.title);
    } else {
        bookNode->data.isAvailable = false;
        printf("Success: You have borrowed '%s'.\n", bookNode->data.title);
    }
}

void returnBook(TreeNode* root, const char* isbn) {
    TreeNode* bookNode = searchByISBN(root, isbn);
    if (bookNode == NULL) {
        printf("Error: Book with ISBN %s not found in library system.\n", isbn);
    } else if (bookNode->data.isAvailable) {
        printf("Info: Book '%s' is already in the library.\n", bookNode->data.title);
    } else {
        bookNode->data.isAvailable = true;
        printf("Success: You have returned '%s'.\n", bookNode->data.title);
    }
}

void searchByTitle(TreeNode* root, const char* titleQuery) {
    if (root == NULL) return;
    if (strstr(root->data.title, titleQuery) != NULL) {
        printBookDetails(root->data);
    }
    searchByTitle(root->left, titleQuery);
    searchByTitle(root->right, titleQuery);
}

void searchByAuthor(TreeNode* root, const char* authorQuery) {
    if (root == NULL) return;
    if (strstr(root->data.author, authorQuery) != NULL) {
        printBookDetails(root->data);
    }
    searchByAuthor(root->left, authorQuery);
    searchByAuthor(root->right, authorQuery);
}

void displayAllBooks(TreeNode* root) {
    if (root != NULL) {
        displayAllBooks(root->left);
        printBookDetails(root->data);
        displayAllBooks(root->right);
    }
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}