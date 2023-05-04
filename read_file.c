#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_LENGTH 1000
#define vertex int



char** getItems(char (*lines)[MAX_LENGTH], int line_count)
{
    char** items = malloc(line_count * sizeof(char*));
    int item_count = 0;

    for (int i = 0; i < line_count; i++)
    {
        char *item = strtok(lines[i], ":");
        if (item != NULL)
        {
            items[item_count] = malloc((strlen(item) + 1) * sizeof(char));
            strcpy(items[item_count], item);
            item_count++;
        }
    }

    return items;
}

char*** groupDependencies(char** inputArray, int length){
    char*** outputArray = (char***) malloc(length * sizeof(char**)); // allocate memory for output array
    int i, j;
    for(i=0; i<length; i++){
        char* str = inputArray[i]; // get the string from the input array
        int colonIndex = -1;
        for(j=0; j<strlen(str); j++){
            if(str[j] == ':'){ // find the index of the colon
                colonIndex = j;
                break;
            }
        }
        if(colonIndex != -1){ // if colon is found
            char* key = (char*) malloc(colonIndex * sizeof(char)); // allocate memory for the key string
            strncpy(key, str, colonIndex); // copy the characters before the colon into the key string
            int valuesCount = 0;
            char** values = (char**) malloc(length * sizeof(char*)); // allocate memory for the values array
            char* ptr = str + colonIndex + 2; // skip the colon and space
            char* token = strtok(ptr, ";"); // split the remaining string by semicolon
            while(token != NULL){
                int len = strlen(token);
                if(token[len-1] == ';'){ // if last character is semicolon
                    token[len-1] = '\0'; // replace it with null character
                }
                char* value = (char*) malloc((len+1) * sizeof(char)); // allocate memory for the value string
                strcpy(value, token); // copy the token into the value string
                values[valuesCount++] = value; // add the value string to the values array
                token = strtok(NULL, ";"); // get the next token
            }
            values = (char**) realloc(values, valuesCount * sizeof(char*)); // resize the values array to the actual number of values
            char** keyValueArray = (char**) malloc((valuesCount+1) * sizeof(char*)); // allocate memory for the key-value pair array
            keyValueArray[0] = key; // add the key to the key-value pair array
            for(j=0; j<valuesCount; j++){
                keyValueArray[j+1] = values[j]; // add the values to the key-value pair array
            }
            outputArray[i] = keyValueArray; // add the key-value pair array to the output array
        }
    }
    return outputArray;
}



int read_file_lines(const char *filename, char lines[][MAX_LENGTH])
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        return -1;
    }

    int line_count = 0;
    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, file))
    {
        // remove newline character from buffer
        buffer[strcspn(buffer, "\n")] = '\0';

        // copy buffer to current line in lines array
        strcpy(lines[line_count], buffer);
        line_count++;

        // break out of loop if blank line is encountered
        if (buffer[0] == '\0')
        {
            break;
        }
    }

    fclose(file);

    return line_count;
}


void readInputFile(const char *filename)
{


    //Numero de vertices
    int nv; 
    //Opcao do algoritmo


    char lines[1000][MAX_LENGTH];
    int line_count = read_file_lines(filename, lines);



    if (line_count == -1)
    {
        printf("Unable to open file.\n");
 
    }

    int size = atoi(lines[0]);

    char** items = getItems(lines, line_count);

    for(int i = 0; i < 11 ; i++){
        printf(" (%s) ", items[i]);
    }

}

int main(){
readInputFile("entrada.txt");

    return 0;
}