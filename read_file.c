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

    int nv; 
    char lines[1000][MAX_LENGTH];
    int line_count = read_file_lines(filename, lines);



    if (line_count == -1)
    {
        printf("Unable to open file.\n");
 
    }

    int size = atoi(lines[0]);

    char** items = getItems(lines, line_count);

    for(int i = 1; i < 10 ; i++){
        printf(" (%s) ", items[i]);
    }

}

int main(){
readInputFile("entrada.txt");

    return 0;
}