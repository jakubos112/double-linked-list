#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef bool (*Comparator)(int, int);

bool comparator(int a, int b){
    if(a < b){
        return true;
    }
    return false;
}

typedef struct Node{
    int data;
    Node* parent;
    Node *left;
    Node *right;
}Node;

typedef struct{
    Node* root;
    int size;
    Comparator comparator;
}BST;

BST* createBST(Comparator comp){
    BST* tree = (BST*)malloc(sizeof(BST));
    tree->root = NULL;
    tree->size = 0;
    tree->comparator = comp;
    return tree;
}

void addNode(BST* tree, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    if (tree->root == NULL) {
        tree->root = newNode;
        tree->size++;
        return;
    }
    Node* current = tree->root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (tree->comparator(val, current->data)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent;
    if (tree->comparator(val, parent->data)) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    
    tree->size++;
}

Node* findNode(BST* tree, int val) {
    Node* current = tree->root;
    
    while (current != NULL) {
        if (current->data == val) {
            return current;
        } 
        if (tree->comparator(val, current->data)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

void deleteNode(BST* tree, int val) {
    Node* node = findNode(tree, val);
    if (node == NULL) return;

    if (node->left == NULL && node->right == NULL) {
        if (node == tree->root) {
            tree->root = NULL;
        } else {
            if (node->parent->left == node) {
                node->parent->left = NULL;
            } else {
                node->parent->right = NULL;
            }
        }
        free(node);
    }
    else if (node->left == NULL) {
        if (node == tree->root) {
            tree->root = node->right;
            node->right->parent = NULL;
        } else {
            node->right->parent = node->parent;
            if (node->parent->left == node) {
                node->parent->left = node->right;
            } else {
                node->parent->right = node->right;
            }
        }
        free(node);
    }
    else if (node->right == NULL) {
        if (node == tree->root) {
            tree->root = node->left;
            node->left->parent = NULL;
        } else {
            node->left->parent = node->parent;
            if (node->parent->left == node) {
                node->parent->left = node->left;
            } else {
                node->parent->right = node->left;
            }
        }
        free(node);
    }
    else {
        Node* successor = node->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }

        node->data = successor->data;

        if (successor->parent->left == successor) {
            successor->parent->left = successor->right;
        } else {
            successor->parent->right = successor->right;
        }
        if (successor->right != NULL) {
            successor->right->parent = successor->parent;
        }
        free(successor);
    }
    
    tree->size--;
}

void preOrder(Node* node, int* array, int* index) {
    if (node == NULL) return;
    array[*index] = node->data;
    (*index)++;
    preOrder(node->left, array, index);
    preOrder(node->right, array, index);
}

void inOrder(Node* node, int* array, int* index) {
    if (node == NULL) return;
    inOrder(node->left, array, index);
    array[*index] = node->data;
    (*index)++;
    inOrder(node->right, array, index);
}

void clearTree(Node* node) {
    if (node == NULL) return;
    clearTree(node->left);
    clearTree(node->right);
    free(node);
}

int getHeight(Node* node) {
    if (node == NULL) return -1;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void toString(Node* node, char* str, int* index) {
    if (node == NULL) return;
    *index += sprintf(str + *index, "Node %d (", node->data);
    if (node->parent) {
        *index += sprintf(str + *index, "parent: %d, ", node->parent->data);
    }
    if (node->left) {
        *index += sprintf(str + *index, "left: %d, ", node->left->data);
    }
    if (node->right) {
        *index += sprintf(str + *index, "right: %d", node->right->data);
    }
    *index += sprintf(str + *index, ")\n");
    toString(node->left, str, index);
    toString(node->right, str, index);
}

void getPreOrder(BST* tree, int* array) {
    int index = 0;
    preOrder(tree->root, array, &index);
}

void getInOrder(BST* tree, int* array) {
    int index = 0;
    inOrder(tree->root, array, &index);
}

void destroyTree(BST* tree) {
    clearTree(tree->root);
    tree->root = NULL;
    tree->size = 0;
}

int getTreeHeight(BST* tree) {
    return getHeight(tree->root);
}

char* treeToString(BST* tree) {
    char* str = (char*)malloc(1000 * sizeof(char));
    int index = 0;
    toString(tree->root, str, &index);
    return str;
}

int main(){

    printf("\nBST tree structure\n");
    return 0;
}