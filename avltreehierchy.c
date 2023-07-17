#include <stdio.h>
#include <stdlib.h>

// Structure for AVL tree node
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// Function to calculate the height of a node
int height(struct Node *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to calculate the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new AVL tree node
struct Node *newNode(int key) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to perform right rotation
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Function to perform left rotation
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Function to get the balance factor of a node
int getBalance(struct Node *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to insert a node into the AVL tree
struct Node *insertNode(struct Node *node, int key) {
    // Perform the normal BST insertion
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else // Duplicate keys are not allowed
        return node;

    // Update the height of the ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Check the balance factor and rebalance if necessary
    int balance = getBalance(node);

    // Left Left case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // No rotation is needed
    return node;
}

// Function to write AVL tree nodes to a file in inorder traversal with hierarchy
void writeNodesToFile(struct Node *node, FILE *file, int level) {
    if (node != NULL) {
        writeNodesToFile(node->right, file, level + 1);
        fprintf(file, "%*s%d\n", 4 * level, "", node->key);
        writeNodesToFile(node->left, file, level + 1);
    }
}

// Function to insert a node into the AVL tree and write the updated tree to a file
void insertNodeAndWriteToFile(const char *filename, int key) {
    // Read existing tree from file
    FILE *file = fopen(filename, "r");
    struct Node *root = NULL;
    if (file != NULL) {
        int num;
        while (fscanf(file, "%d", &num) != EOF) {
            root = insertNode(root, num);
        }
        fclose(file);
    }

    // Insert the new node into the tree
    root = insertNode(root, key);

    // Write the updated tree to the file
    file = fopen(filename, "w");
    if (file != NULL) {
        writeNodesToFile(root, file, 0);
        fclose(file);
    }
}

int main() {
    const char *filename = "avl_tree.txt";

    // Insert nodes into the AVL tree and write to file
    insertNodeAndWriteToFile(filename, 10);
    insertNodeAndWriteToFile(filename, 20);
    insertNodeAndWriteToFile(filename, 30);
    insertNodeAndWriteToFile(filename, 40);
    insertNodeAndWriteToFile(filename, 50);
    insertNodeAndWriteToFile(filename, 25);

    printf("Nodes inserted and AVL tree written to file successfully.\n");

    return 0;
}
