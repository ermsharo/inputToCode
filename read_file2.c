#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 120
#define MAX_ARRAY_LEN 1000

int *find_indices(char **arr1, int arr1_size, char **arr2, int arr2_size)
{
    int *indices = malloc(arr2_size * sizeof(int));
    if (indices == NULL)
    {
        printf("Error: failed to allocate memory\n");
        exit(1);
    }

    int index = 0;
    for (int i = 0; i < arr1_size && index < arr2_size; i++)
    {
        if (strcmp(arr1[i], arr2[index]) == 0)
        {
            indices[index] = i;
            index++;
        }
    }

    return indices;
}

char ***parse_input(const char **input, int input_size, const char **prefixes, int prefixes_size, int *output_size)
{
    char ***output = malloc(prefixes_size * sizeof(char **));
    int output_index = 0;

    for (int i = 0; i < prefixes_size; i++)
    {
        output[output_index] = malloc(input_size * sizeof(char *));
        int output_subindex = 0;

        for (int j = 0; j < input_size; j++)
        {
            if (strncmp(input[j], prefixes[i], strlen(prefixes[i])) == 0)
            {
                output[output_index][output_subindex] = (char *)input[j];
                output_subindex++;
            }
        }

        if (output_subindex > 0)
        {
            output[output_index][output_subindex] = NULL;
            output_index++;
        }
        else
        {
            free(output[output_index]);
        }
    }

    *output_size = output_index;
    return output;
}

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

char **getAdjList(char **arr, int len, int *outLen)
{
    // Allocate memory for the output array
    char **outArr = (char **)malloc(MAX_ARRAY_LEN * sizeof(char *));
    if (!outArr)
    {
        printf("Error: Failed to allocate memory for output array.\n");
        return NULL;
    }

    // Create a hash table to keep track of which strings have been seen
    int *seenTable = (int *)calloc(len, sizeof(int));
    if (!seenTable)
    {
        printf("Error: Failed to allocate memory for seen table.\n");
        free(outArr);
        return NULL;
    }

    int outIdx = 0;
    for (int i = 0; i < len; i++)
    {
        char *str = arr[i];

        // Check if the string has been seen before
        int seen = 0;
        for (int j = 0; j < i; j++)
        {
            if (seenTable[j] && strcmp(str, arr[j]) == 0)
            {
                seen = 1;
                break;
            }
        }

        // If the string has not been seen, add it to the output array
        if (!seen)
        {
            outArr[outIdx] = str;
            outIdx++;
            seenTable[i] = 1;
        }
    }

    // Update the output length
    *outLen = outIdx;

    // Free the seen table memory
    free(seenTable);

    // Return the output array
    return outArr;
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

void print_output(char ***output, int output_size)
{
    for (int i = 0; i < output_size; i++)
    {
        int j = 0;
        while (output[i][j] != NULL)
        {
            printf("%s, ", output[i][j]);
            j++;
        }
        printf("\n");
    }
}

void print_array(char ***arr, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        printf("{");
        char **sub_arr = arr[i];
        for (int j = 0; sub_arr[j] != NULL; j++)
        {
            printf("\"%s\"", sub_arr[j]);
            if (sub_arr[j + 1] != NULL)
            {
                printf(", ");
            }
        }
        printf("}\n");
    }
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

    int *indices = find_indices(words, numWords, output, size - 1);
    printf("\n");

    printf("Indices: [ ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ,", indices[i]);
    }
    printf("]");

    int *idx = find_indexes(words, numWords, output, size - 1);

    char ***result = split_array(words, numWords, idx, size - 1);
    printf("\n \n \n SEPARATED NODES");
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
