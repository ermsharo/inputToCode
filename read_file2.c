#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 120
#define MAX_ARRAY_LEN 1000




char **getWordsEndingWith(char **array, char endChar, int size)
{
    char **result = (char **)malloc(size * sizeof(char *)); // Allocate memory for the result array
    int count = 0;                                          // Counter for the number of words that end with the specified character

    for (int i = 0; i < size; i++)
    {
        int len = strlen(array[i]); // Get the length of the current string

        if (array[i][len - 1] == endChar)
        {                                                             // Check if the last character of the string matches the specified character
            result[count] = (char *)malloc((len + 1) * sizeof(char)); // Allocate memory for the string in the result array
            strcpy(result[count], array[i]);                          // Copy the string from the input array to the result array
            count++;                                                  // Increment the counter
        }
    }

    result = (char **)realloc(result, count * sizeof(char *)); // Shrink the result array to fit the exact number of words that end with the specified character
    return result;
}


char **readWordsFromFile(const char *fileName, int *numWords)
{
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Failed to open file %s\n", fileName);
        return NULL;
    }

    char **words = (char **)malloc(MAX_WORDS * sizeof(char *));
    if (words == NULL)
    {
        printf("Failed to allocate memory\n");
        return NULL;
    }

    int i = 0;
    char line[MAX_WORD_LENGTH * 3];
    while (fgets(line, sizeof(line), fp) != NULL && i < MAX_WORDS)
    {
        char *word = strtok(line, " \t\n\r");
        while (word != NULL && i < MAX_WORDS)
        {
            words[i] = (char *)malloc((strlen(word) + 1) * sizeof(char));
            if (words[i] == NULL)
            {
                printf("Failed to allocate memory\n");
                return NULL;
            }
            strcpy(words[i], word);
            i++;
            word = strtok(NULL, " \t\n\r");
        }
    }

    *numWords = i;

    fclose(fp);
    return words;
}

void generateGraph(char **words, int numWords)
{
}



int *find_indexes(char **arr1, int arr1_size, char **arr2, int arr2_size)
{
    int *idx = (int *)malloc(arr2_size * sizeof(int));
    int idx_index = 0;

    for (int i = 0; i < arr1_size; i++)
    {
        for (int j = 0; j < arr2_size; j++)
        {
            if (strcmp(arr1[i], arr2[j]) == 0)
            {
                idx[idx_index++] = i;
                break;
            }
        }
    }

    return idx;
}

char ***split_array(char **arr, int arr_size, int *idx, int idx_size)
{
    char ***result = (char ***)malloc(idx_size * sizeof(char **));
    for (int i = 0; i < idx_size; i++)
    {
        int start = idx[i] + 1;
        int end = (i == idx_size - 1) ? arr_size : idx[i + 1];
        int len = end - start;

        result[i] = (char **)malloc((len + 1) * sizeof(char *));
        for (int j = 0; j < len; j++)
        {
            result[i][j] = (char *)malloc((strlen(arr[start + j]) + 1) * sizeof(char));
            strncpy(result[i][j], arr[start + j], strlen(arr[start + j]));
            result[i][j][strlen(arr[start + j])] = '\0';
        }
        result[i][len] = NULL;
    }

    return result;
}

char** remove_first_last(char** arr, int size) {
    if (size <= 2) {
        return NULL;
    }

    // Allocate memory for the new array
    char** new_arr = (char**) malloc((size-2) * sizeof(char*));

    // Copy elements from the original array to the new array
    for (int i = 1; i < size-1; i++) {
        new_arr[i-1] = strdup(arr[i]); // strdup() duplicates the string
    }

    // Free memory of the original array
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);

    return new_arr;
}

void remove_last_char(char* str)
{
    int len = strlen(str);
    if (len > 0) {
        str[len - 1] = '\0';
    }
}


int main()
{
    char **originalWords;
    int originalNumWords;

    originalWords = readWordsFromFile("entrada.txt", &originalNumWords);

    if (originalWords == NULL)
    {
        printf("Failed to read words from file\n");
        return 1;
    }

    printf("The words in the file are:\n");
    for (int i = 0; i < originalNumWords; i++)
    {
        printf("%s , ", originalWords[i]);
    }

    char **words = remove_first_last(originalWords,originalNumWords);
    int numWords = originalNumWords-2;


     printf(" \n \n The words in the graph:\n");
    for (int i = 0; i < numWords; i++)
    {
        printf("%s , ", words[i]);
    }


    printf("\n  -> size of main array is %i ", numWords);
    char **output = getWordsEndingWith(words, ':', numWords);
    int size = sizeof(output) + 1;
    printf("\n  -> size of adj array is %i ", size);
    printf("\n\nOutput array:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%s ", output[i]);
    }


    int *idx = find_indexes(words, numWords, output, size - 1);

    char ***result = split_array(words, numWords, idx, size - 1);
    printf("\n \n \nSEPARATED NODES:\n");
    for (int i = 0; i < size - 1; i++) {
        printf("{");
        for (int j = 0; result[i][j] != NULL; j++) {
            if (result[i][j][strlen(result[i][j])-1] != ':') {
                printf("%s", result[i][j]);
                if (result[i][j+1] != NULL) {
                    printf(", ");
                }
            }
        }
        printf("}\n");
    }

    for (int i = 0; i < numWords; i++)
    {
        free(words[i]);
    }
    free(words);

    return 0;
}
