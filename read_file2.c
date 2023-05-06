#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 120
#define MAX_ARRAY_LEN 1000

char*** parse_input(const char** input, int input_size, const char** prefixes, int prefixes_size, int* output_size) {
    char*** output = malloc(sizeof(char**) * prefixes_size);
    int output_index = 0;

    for (int i = 0; i < prefixes_size; i++) {
        output[i] = malloc(sizeof(char*) * input_size);
    }

    int input_index = 0;

    while (input_index < input_size) {
        int prefix_index = -1;

        for (int i = 0; i < prefixes_size; i++) {
            if (strncmp(input[input_index], prefixes[i], strlen(prefixes[i])) == 0) {
                prefix_index = i;
                break;
            }
        }

        if (prefix_index >= 0) {
            output[prefix_index][output_index] = (char*) input[input_index];
            output_index++;
        }

        input_index++;
    }

    for (int i = 0; i < prefixes_size; i++) {
        output[i] = realloc(output[i], sizeof(char*) * output_index);
    }

    *output_size = output_index;

    return output;
}

char** getWordsEndingWith(char** array, char endChar, int size) {
    char** result = (char**)malloc(size * sizeof(char*));  // Allocate memory for the result array
    int count = 0;  // Counter for the number of words that end with the specified character
    
    for (int i = 0; i < size; i++) {
        int len = strlen(array[i]);  // Get the length of the current string
        
        if (array[i][len - 1] == endChar) {  // Check if the last character of the string matches the specified character
            result[count] = (char*)malloc((len + 1) * sizeof(char));  // Allocate memory for the string in the result array
            strcpy(result[count], array[i]);  // Copy the string from the input array to the result array
            count++;  // Increment the counter
        }
    }
    
    result = (char**)realloc(result, count * sizeof(char*));  // Shrink the result array to fit the exact number of words that end with the specified character
    return result;
}



char** getAdjList(char** arr, int len, int* outLen)
{
    // Allocate memory for the output array
    char** outArr = (char**) malloc(MAX_ARRAY_LEN * sizeof(char*));
    if (!outArr) {
        printf("Error: Failed to allocate memory for output array.\n");
        return NULL;
    }

    // Create a hash table to keep track of which strings have been seen
    int* seenTable = (int*) calloc(len, sizeof(int));
    if (!seenTable) {
        printf("Error: Failed to allocate memory for seen table.\n");
        free(outArr);
        return NULL;
    }

    int outIdx = 0;
    for (int i = 0; i < len; i++)
    {
        char* str = arr[i];

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



char** readWordsFromFile(const char* fileName, int* numWords)
{
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Failed to open file %s\n", fileName);
        return NULL;
    }

    char** words = (char**)malloc(MAX_WORDS * sizeof(char*));
    if (words == NULL)
    {
        printf("Failed to allocate memory\n");
        return NULL;
    }

    int i = 0;
    char line[MAX_WORD_LENGTH * 3];
    while (fgets(line, sizeof(line), fp) != NULL && i < MAX_WORDS)
    {
        char* word = strtok(line, " \t\n\r");
        while (word != NULL && i < MAX_WORDS)
        {
            words[i] = (char*)malloc((strlen(word) + 1) * sizeof(char));
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


void generateGraph(char** words, int numWords){


}

void print_array(char*** arr, int arr_size) {
    if (arr_size == 0) {
        printf("{}");
        return;
    }

    printf("{\n");
    for (int i = 0; i < arr_size; i++) {
        printf("\t{");
        if (arr[i] != NULL) {
            int j = 0;
            while (arr[i][j] != NULL) {
                printf("%s", arr[i][j]);
                if (arr[i][j+1] != NULL) {
                    printf(", ");
                }
                j++;
            }
        }
        printf("}");
        if (i < arr_size-1) {
            printf(",");
        }
        printf("\n");
    }
    printf("}");
}

int main()
{
    char** words;
    int numWords;

    words = readWordsFromFile("entrada.txt", &numWords);

    if (words == NULL)
    {
        printf("Failed to read words from file\n");
        return 1;
    }

    printf("The words in the file are:\n");
    for (int i = 0; i < numWords; i++)
    {
        printf("%s , ", words[i]);
    }

   
   

    printf("\n  -> size of main array is %i ",numWords);
    char** output = getWordsEndingWith(words, ':', numWords);
    int size = sizeof(output)  +1;
    printf("\n  -> size of adj array is %i ",size);
    printf("\n\nOutput array:\n");
    for (int i = 0; i < size; i++) {
        printf("%s ", output[i]);
    }
    printf("\n");


 int output_nodes_size = 0;
    char*** outputNodes = parse_input((const char**)words, numWords, (const char**)output, size, &output_nodes_size);


print_array( outputNodes, 5);



    for (int i = 0; i < numWords; i++)
    {
        free(words[i]);
    }
    free(words);

    return 0;
}
