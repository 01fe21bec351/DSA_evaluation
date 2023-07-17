#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* buildTree(int* preOrder, int* postOrder, int* inOrder, int start, int end) {
    static int preIndex = 0;
    if (start > end) {
        return NULL;
    }

    Node* newNode = createNode(preOrder[preIndex++]);

    if (start == end) {
        return newNode;
    }

    int inIndex;
    for (inIndex = start; inIndex <= end; inIndex++) {
        if (inOrder[inIndex] == newNode->data) {
            break;
        }
    }

    newNode->left = buildTree(preOrder, postOrder, inOrder, start, inIndex - 1);
    newNode->right = buildTree(preOrder, postOrder, inOrder, inIndex + 1, end);

    return newNode;
}

void preOrderTraversal(Node* root, FILE* file) {
    if (root == NULL) {
        return;
    }

    fprintf(file, "%d ", root->data);
    preOrderTraversal(root->left, file);
    preOrderTraversal(root->right, file);
}

void postOrderTraversal(Node* root, FILE* file) {
    if (root == NULL) {
        return;
    }

    postOrderTraversal(root->left, file);
    postOrderTraversal(root->right, file);
    fprintf(file, "%d ", root->data);
}

void inOrderTraversal(Node* root, FILE* file) {
    if (root == NULL) {
        return;
    }

    inOrderTraversal(root->left, file);
    fprintf(file, "%d ", root->data);
    inOrderTraversal(root->right, file);
}

int main() {
    srand(time(0));

    int size = 10; // Number of elements in the tree

    int* preOrder = (int*)malloc(size * sizeof(int));
    int* postOrder = (int*)malloc(size * sizeof(int));
    int* inOrder = (int*)malloc(size * sizeof(int));

    FILE* preFile = fopen("preorder.txt", "w");
    FILE* postFile = fopen("postorder.txt", "w");
    FILE* inOrderFile = fopen("inorder.txt", "w");

    if (preFile == NULL || postFile == NULL || inOrderFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    // Generate random numbers for the traversals
    for (int i = 0; i < size; i++) {
        int num = rand() % 100; // Generate a random number between 0 and 99
        preOrder[i] = num;
        postOrder[i] = num;
        inOrder[i] = num;
    }

    Node* root = buildTree(preOrder, postOrder, inOrder, 0, size - 1);

    preOrderTraversal(root, preFile);
    postOrderTraversal(root, postFile);
    inOrderTraversal(root, inOrderFile);

    fclose(preFile);
    fclose(postFile);
    fclose(inOrderFile);

    printf("Traversal data written to files successfully.\n");

    free(preOrder);
    free(postOrder);
    free(inOrder);

    return 0;
}
