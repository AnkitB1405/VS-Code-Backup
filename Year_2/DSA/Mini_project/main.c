#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 



#define FILENAME "library.csv" 
#define MAX_LINE_LEN 256       


typedef struct Book {
    char isbn[20];
    char title[100];
    char author[100];
    bool isAvailable;
} Book;


typedef struct TreeNode {
    Book data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;



TreeNode* createNode(Book newBook);
TreeNode* addBook(TreeNode* root, Book newBook);
void printBookDetails(Book book);
TreeNode* searchByISBN(TreeNode* root, const char* isbn);




void saveTreeRecursive(FILE* file, TreeNode* node) {
    if (node == NULL) {
        return;
    }
    

    fprintf(file, "%s,%s,%s,%d\n",
            node->data.isbn,
            node->data.title,
            node->data.author,
            node->data.isAvailable ? 1 : 0);
            
  
    saveTreeRecursive(file, node->left);
    saveTreeRecursive(file, node->right);
}


void saveDataToFile(TreeNode* root, const char* filename) {
    FILE* file = fopen(filename, "w"); 
    if (file == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return;
    }

    printf("Saving data to %s...\n", filename);
    saveTreeRecursive(file, root);
    
    fclose(file);
    printf("Data saved successfully.\n");
}


TreeNode* loadDataFromFile(const char* filename) {
    FILE* file = fopen(filename, "r"); 
    if (file == NULL) {
        printf("Info: No existing '%s' found. Starting a new library.\n", filename);
        return NULL;
    }

    printf("Loading data from %s...\n", filename);
    TreeNode* root = NULL;
    char line[MAX_LINE_LEN];

    while (fgets(line, sizeof(line), file)) {
        Book newBook;
        char* token;

        
        line[strcspn(line, "\n")] = 0;

        
        token = strtok(line, ",");
        if (token == NULL) continue; 
        strcpy(newBook.isbn, token);

    
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strcpy(newBook.title, token);

       
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strcpy(newBook.author, token);

       
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        newBook.isAvailable = (atoi(token) == 1); 

        
        root = addBook(root, newBook);
    }

    fclose(file);
    printf("Data loaded successfully.\n");
    return root;
}




void borrowBook(TreeNode* root, const char* isbn);
void returnBook(TreeNode* root, const char* isbn);
void searchByTitle(TreeNode* root, const char* titleQuery);
void searchByAuthor(TreeNode* root, const char* authorQuery);
void displayAllBooks(TreeNode* root);
void freeTree(TreeNode* root);



int main() {
    TreeNode* root = NULL;
    int choice;
    char isbn[20], title[100], author[100];

 
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
                saveDataToFile(root, FILENAME);
                printf("Book added!\n");
                break;
            case 2:
                printf("Enter ISBN to borrow: ");
                fgets(isbn, 20, stdin); isbn[strcspn(isbn, "\n")] = 0;
                borrowBook(root, isbn);
                saveDataToFile(root, FILENAME);
                break;
            case 3:
                printf("Enter ISBN to return: ");
                fgets(isbn, 20, stdin); isbn[strcspn(isbn, "\n")] = 0;
                returnBook(root, isbn);
                saveDataToFile(root, FILENAME);
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

    saveDataToFile(root, FILENAME);

    freeTree(root);
    
    return 0;
}





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

        strcpy(root->data.title, newBook.title);

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