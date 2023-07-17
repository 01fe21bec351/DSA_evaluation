#include <stdio.h>
#include <stdlib.h>

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
    int preOrder[] = { 4, 2, 1, 3, 6, 5, 7 };
    int postOrder[] = { 1, 3, 2, 5, 7, 6, 4 };
    int inOrder[] = { 1, 2, 3, 4, 5, 6, 7 };

    int size = sizeof(preOrder) / sizeof(preOrder[0]);

    Node* root = buildTree(preOrder, postOrder, inOrder, 0, size - 1);

    FILE* preFile = fopen("preorder.txt", "w");
    FILE* postFile = fopen("postorder.txt", "w");
    FILE* inOrderFile = fopen("inorder.txt", "w");

    if (preFile == NULL || postFile == NULL || inOrderFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    preOrderTraversal(root, preFile);
    postOrderTraversal(root, postFile);
    inOrderTraversal(root, inOrderFile);

    fclose(preFile);
    fclose(postFile);
    fclose(inOrderFile);

    printf("Traversal data written to files successfully.\n");

    return 0;
}
