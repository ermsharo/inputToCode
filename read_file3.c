#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRUIT_NAME_LENGTH 20

struct Node {
    char** strings;
    int numStrings;
    int index;
    struct Node* next;
};

void push(struct Node** top, char** strings, int numStrings, int index) {
    // Alocar memória para o novo nó
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    // Definir as strings, o número de strings e o índice do novo nó
    newNode->strings = strings;
    newNode->numStrings = numStrings;
    newNode->index = index;

    // Inserir o novo nó no topo da pilha
    newNode->next = *top;
    *top = newNode;
}



int splitFruits(char originalArray[][MAX_FRUIT_NAME_LENGTH], char ***splitArrays, int size);

int main() {
    char originalArray[][MAX_FRUIT_NAME_LENGTH] = {"apple", "banana", "split", "orange", "split", "pear", "grape"};
    char **splitArrays;
    int numSplits = splitFruits(originalArray, &splitArrays, sizeof(originalArray) / sizeof(originalArray[0]));

    // Print the split arrays
    for (int i = 0; i <= numSplits; i++) {
        printf("[");
        for (int j = 0; j < strlen(splitArrays[i][0]); j++) {
            printf("'%s'", splitArrays[i][j]);
            if (j < strlen(splitArrays[i][0]) - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }

    // Free memory allocated for splitArrays
    for (int i = 0; i <= numSplits; i++) {
        for (int j = 0; j < strlen(splitArrays[i][0]); j++) {
            free(splitArrays[i][j]);
        }
        free(splitArrays[i]);
    }
    free(splitArrays);

    return 0;
}

int splitFruits(char originalArray[][MAX_FRUIT_NAME_LENGTH], char ***splitArrays, int size) {
    int numSplits = 0;
    int numFruits = 0;
    int currentSplitArray = 0;
    int currentFruit = 0;
    *splitArrays = malloc(sizeof(char*) * size);
    (*splitArrays)[0] = malloc(sizeof(char) * MAX_FRUIT_NAME_LENGTH);
    for (int i = 0; i < size; i++) {
        if (strcmp(originalArray[i], "split") == 0) {
            (*splitArrays)[currentSplitArray][numFruits] = '\0';
            currentSplitArray++;
            currentFruit = 0;
            (*splitArrays)[currentSplitArray] = malloc(sizeof(char) * MAX_FRUIT_NAME_LENGTH);
            numSplits++;
        } else {
            (*splitArrays)[currentSplitArray][currentFruit] = malloc(sizeof(char) * MAX_FRUIT_NAME_LENGTH);
            strcpy((*splitArrays)[currentSplitArray][currentFruit], originalArray[i]);
            currentFruit++;
            numFruits = currentFruit;
        }
    }
    (*splitArrays)[currentSplitArray][numFruits] = '\0';
    return numSplits;
}
