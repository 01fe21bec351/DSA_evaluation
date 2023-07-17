#include <stdio.h>

#define MAX_VERTICES 10

int graph[MAX_VERTICES][MAX_VERTICES];
int numVertices;

void initGraph(int vertices) {
    numVertices = vertices;
    int i, j;
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            graph[i][j] = 0;
        }
    }
}

void addEdge(int source, int destination) {
    if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
        graph[source][destination] = 1;
        graph[destination][source] = 1;
    }
}

void printGraph(FILE* outputFile) {
    int i, j;
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            fprintf(outputFile, "%d ", graph[i][j]);
        }
        fprintf(outputFile, "\n");
    }
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Failed to open files.");
        return 1;
    }

    int vertices;
    fscanf(inputFile, "%d", &vertices);

    initGraph(vertices);

    int source, destination;
    while (fscanf(inputFile, "%d %d", &source, &destination) == 2) {
        addEdge(source, destination);
    }

    printGraph(outputFile);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
