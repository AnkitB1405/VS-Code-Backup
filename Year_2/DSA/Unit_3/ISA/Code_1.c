#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}Node;

Node* insertelement(Node *root, int value){
    if(root==NULL){
        root = (Node*)malloc(sizeof(Node));
        root->data = value;
        root->left = root->right = NULL;
    }
    else if(value < root->data){
        root->left = insertelement(root->left, value);
    }
    else{
        root->right = insertelement(root->right, value);
    }
    return root;
}

Node* searchElement(Node *root, int val){
    if(root==NULL){
        return NULL;
    }
    else if(root->data == val){
        return root;
    }
    else if(val < root->data){
        return searchElement(root->left, val);
    }
    else{
        return searchElement(root->right, val);
    }
}