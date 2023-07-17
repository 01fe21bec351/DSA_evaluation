#include <stdio.h>
#include <stdlib.h>

// Structure for AVL tree node
struct AVLNode {
    int data;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
};

// Function to calculate the height of a node
int height(struct AVLNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new AVL node
struct AVLNode *newNode(int data) {
    struct AVLNode *node = (struct AVLNode *)malloc(sizeof(struct AVLNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to right rotate subtree rooted with y
struct AVLNode *rightRotate(struct AVLNode *y) {
    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Function to left rotate subtree rooted with x
struct AVLNode *leftRotate(struct AVLNode *x) {
    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get the balance factor of a node
int getBalance(struct AVLNode *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to insert a node into AVL tree
struct AVLNode *insert(struct AVLNode *node, int data) {
    // Perform the normal BST insertion
    if (node == NULL)
        return newNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Duplicate keys are not allowed
        return node;

    // Update the height of the ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Check the balance factor and perform necessary rotations
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the unchanged node pointer
    return node;
}

// Function to save the AVL tree into a file
void saveAVLTree(struct AVLNode *root, FILE *file) {
    if (root == NULL)
        return;

    // Save the node data
    fprintf(file, "%d\n", root->data);

    // Save the left subtree
    saveAVLTree(root->left, file);

    // Save the right subtree
    saveAVLTree(root->right, file);
}

// Function to load the AVL tree from a file
struct AVLNode *loadAVLTree(FILE *file) {
    int data;
    if (fscanf(file, "%d\n", &data) != 1)
        return NULL;

    struct AVLNode *root = newNode(data);

    // Load the left subtree
    root->left = loadAVLTree(file);

    // Load the right subtree
    root->right = loadAVLTree(file);

    // Update the height of the node
    root->height = 1 + max(height(root->left), height(root->right));

    return root;
}

// Function to free the memory allocated for AVL tree nodes
void freeAVLTree(struct AVLNode *root) {
    if (root == NULL)
        return;

    freeAVLTree(root->left);
    freeAVLTree(root->right);
    free(root);
}

// Driver code
int main() {
    struct AVLNode *root = NULL;
    FILE *file;

    // Insert nodes into AVL tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Save AVL tree to a file
    file = fopen("avltree.txt", "w");
    saveAVLTree(root, file);
    fclose(file);

    // Load AVL tree from the file
    file = fopen("avltree.txt", "r");
    struct AVLNode *loadedRoot = loadAVLTree(file);
    fclose(file);

    // Perform operations on the loaded AVL tree
    // ...

    // Free memory allocated for AVL trees
    freeAVLTree(root);
    freeAVLTree(loadedRoot);

    return 0;
}
