#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 120
#define MAX_ARRAY_LEN 1000


int* find_indices(char** arr1, int arr1_size, char** arr2, int arr2_size) {
    int* indices = malloc(arr2_size * sizeof(int));
    if (indices == NULL) {
        printf("Error: failed to allocate memory\n");
        exit(1);
    }

    int index = 0;
    for (int i = 0; i < arr1_size && index < arr2_size; i++) {
        if (strcmp(arr1[i], arr2[index]) == 0) {
            indices[index] = i;
            index++;
        }
    }

    return indices;
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

void print_output(char*** output, int output_size) {
    for (int i = 0; i < output_size; i++) {
        int j = 0;
        while (output[i][j] != NULL) {
            printf("%s, ", output[i][j]);
            j++;
        }
        printf("\n");
    }
}


void print_array(char*** arr, int arr_size) {
    for(int i=0; i<arr_size; i++) {
        printf("{");
        char** sub_arr = arr[i];
        for(int j=0; sub_arr[j] != NULL; j++) {
            printf("\"%s\"", sub_arr[j]);
            if(sub_arr[j+1] != NULL) {
                printf(", ");
            }
        }
        printf("}\n");
    }
}

int main() {
    const char* input[] = {"undershorts:", "pants:", "belt:", "shirt:", "tie:", "jacket:", "socks:", "shoes:", "watch:"};
     const char* prefixes[] = {"pants:", "belt:", "shirt:", "tie:", "jacket:", "socks:", "shoes:", "watch:"};
    int input_size = sizeof(input) / sizeof(input[0]);
    int prefixes_size = sizeof(prefixes) / sizeof(prefixes[0]);
    int output_size;
    char*** output = parse_input(input, input_size, prefixes, prefixes_size, &output_size);
    print_array(output, output_size);
    return 0;
}