#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 120
#define MAX_ARRAY_LEN 1000
#define MAX_SIZE 100000
struct listNode
{
    char *data;
    int index;
    struct listNode *next;
};

void insert_at_end(struct listNode **head, char *value)
{
    struct listNode *new_listNode = (struct listNode *)malloc(sizeof(struct listNode));
    new_listNode->data = value;
    new_listNode->next = NULL;

    if (*head == NULL)
    {
        *head = new_listNode;
    }
    else
    {
        struct listNode *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_listNode;
    }
}

void print_list(struct listNode *head)
{
    struct listNode *temp = head;
    while (temp != NULL)
    {
        printf("%s ", temp->data);
        temp = temp->next;
    }
}

void free_list(struct listNode *head)
{
    while (head != NULL)
    {
        struct listNode *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

void print_string_array(char **arr)
{
    int size = 0;

    // Loop through the array until a NULL pointer is encountered
    while (arr[size] != NULL)
    {
        size++;
    }

    // Loop through the array again and print each string
    for (int i = 0; i < size; i++)
    {
        printf("%s ,", arr[i]);
    }
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

char **getWordsEndingWith(char **array, char endChar, int size)
{
    char **result = (char **)malloc(size * sizeof(char *)); // Allocate memory for the result array
    int count = 0;                                          // Counter for the number of words that end with the specified character

    for (int i = 0; i < size; i++)
    {
        int len = strlen(array[i]); // Get the length of the current string

        if (array[i][len - 1] == endChar)
        {                             // Check if the last character of the string matches the specified character
            result[count] = array[i]; // Allocate memory for the string in the result array
            // strcpy(result[count], array[i]);
            //    printf(" \n adj ->  %s ",array[i]);                      // Copy the string from the input array to the result array
            count++; // Increment the counter
        }
    }

    result = (char **)realloc(result, count * sizeof(char *)); // Shrink the result array to fit the exact number of words that end with the specified character
    printf(" \n \n Aqui esta  \n \n");
    // print_string_array(result);
    return result;
}

char **remove_first_last(char **arr, int size)
{
    if (size <= 2)
    {
        return NULL;
    }

    // Allocate memory for the new array
    char **new_arr = (char **)malloc((size - 2) * sizeof(char *));

    // Copy elements from the original array to the new array
    for (int i = 1; i < size - 1; i++)
    {
        new_arr[i - 1] = strdup(arr[i]);
    }

    // Free memory of the original array
    for (int i = 0; i < size; i++)
    {
        free(arr[i]);
    }
    free(arr);

    return new_arr;
}

char **remove_char(char **arr, int arr_size, char c)
{
    char **new_arr = (char **)malloc(arr_size * sizeof(char *));
    for (int i = 0; i < arr_size; i++)
    {
        int len = strlen(arr[i]);
        new_arr[i] = (char *)malloc((len + 1) * sizeof(char));
        int j = 0;
        for (int k = 0; k < len; k++)
        {
            if (arr[i][k] != c)
            {
                new_arr[i][j] = arr[i][k];
                j++;
            }
        }
        new_arr[i][j] = '\0';
    }
    return new_arr;
}

char **add_array_label(char **array, char endChar, int size)
{
    char **result = (char **)malloc(size * sizeof(char *)); // Allocate memory for the result array
                                                            // Counter for the number of words that end with the specified character

    for (int i = 0; i < size; i++)
    {
        int len = strlen(array[i]); // Get the length of the current string

        if (array[i][len - 1] == endChar)
        {                      // Check if the last character of the string matches the specified character
            result[i] = "adj"; // Increment the counter
        }
        else
        {
            result[i] = array[i];
        }
    }

    // result = (char **)realloc(result, count * sizeof(char *)); // Shrink the result array to fit the exact number of words that end with the specified character
    return result;
}

void insert_between_equal(char **arr, int len)
{
    int i, j;
    for (i = 0; i < len - 1; i++)
    {
        if (strcmp(arr[i], arr[i + 1]) == 0)
        {
            // elements are equal, so insert a new element between them
            char *new_str = "empty";                           // replace with your desired new element
            len++;                                             // increase length of array
            arr = (char **)realloc(arr, len * sizeof(char *)); // resize array
            // shift elements to the right to make room for new element
            for (j = len - 1; j > i + 1; j--)
            {
                arr[j] = arr[j - 1];
            }
            arr[i + 1] = new_str; // insert new element
            i++;                  // skip over newly inserted element
        }
    }
}

char **insert_new_element(char **arr, int size)
{
    char **new_arr = malloc(MAX_SIZE * sizeof(char *));
    int new_arr_size = 0;

    for (int i = 0; i < size; i++)
    {
        // Add the current string to the new array
        new_arr[new_arr_size++] = arr[i];
        // Check if the next string is the same as the current one
        if (i < size - 1 && strcmp(arr[i], arr[i + 1]) == 0)
        {
            // Add the new element to the new array
            new_arr[new_arr_size++] = "empty";
        }
    }

    // Null-terminate the new array
    new_arr[new_arr_size] = NULL;

    return new_arr;
}



int get_array_size(char **arr)
{
    int size = 0;

    // Loop through the array until a NULL pointer is encountered
    while (arr[size] != NULL)
    {
        size++;
    }
    return size;
}

void add_string_to_array(char ***arr_ptr, char *str)
{
    // Calculate the size of the array
    int size = 0;
    char **arr = *arr_ptr;
    while (arr[size] != NULL)
    {
        size++;
    }

    // Allocate memory for the new string and copy it in
    char *new_str = malloc(strlen(str) + 1);
    strcpy(new_str, str);

    // Reallocate memory for the array and add the new string
    *arr_ptr = realloc(arr, (size + 2) * sizeof(char *));
    (*arr_ptr)[size] = new_str;
    (*arr_ptr)[size + 1] = NULL;
}

void add_string_if_last_element_matches(char ***arr_ptr, char *last_element, char *str_to_add)
{
    char **arr = *arr_ptr;
    int size = 0;
    while (arr[size] != NULL)
    {
        size++;
    }
    if (size > 0 && strcmp(arr[size - 1], last_element) == 0)
    {
        add_string_to_array(arr_ptr, str_to_add);
    }
}

int main()
{
    char **originalWords;
    int originalNumWords;

    originalWords = readWordsFromFile("entrada.txt", &originalNumWords);

    int optionValue = atoi(originalWords[originalNumWords - 1]);

    char **words = remove_first_last(originalWords, originalNumWords);
    int numWords = originalNumWords - 2;

    printf(" \n \n The words in the graph:\n");

    print_string_array(words);

    char **output = getWordsEndingWith(words, ':', numWords);
    int size = sizeof(output);

    int adjSize = get_array_size(output);

    printf(" \n  adj list size %i ", size);

    char **clean_adj = remove_char(output, size, ':');

    char **array_label = add_array_label(words, ':', numWords);

    char **new_arr = insert_new_element(array_label, numWords);

    add_string_if_last_element_matches(&new_arr, "adj", "empty");

    int new_array_size = get_array_size(new_arr);
    // insert_between_equal(array_label, numWords);

    printf("\n labed array :\n");
    print_string_array(array_label);

    printf("\n Array with empty :\n");
    print_string_array(new_arr);

    printf("\n array size : %i \n \n ", new_array_size);

    char **clean_relations = remove_char(new_arr, new_array_size, ';');
    printf("\n labed array :\n");

    // print_string_array(clean_relations);
    printf("\n");

    printf(" \n  \n \n ");

    struct listNode *head = NULL;
    struct listNode *sublist_head = NULL;

    for (int i = 0; i < new_array_size; i++)
    {
        char *current_str = clean_relations[i];

        if (strcmp(current_str, "adj") == 0)
        {
            if (sublist_head != NULL)
            {
                insert_at_end(&head, sublist_head);

                // print_list(sublist_head);
                // printf("\n");
            }
            sublist_head = NULL;
        }
        else
        {

            insert_at_end(&sublist_head, current_str);
        }
    }

    if (sublist_head != NULL)
    {
        insert_at_end(&head, sublist_head);
        // print_list(sublist_head);
    }

    struct listNode *temp = head;
    int sublist_number = 0;
    while (temp != NULL)
    {   printf(" id : %i ",sublist_number);
        printf("%s: ", clean_adj[sublist_number]);
        print_list((struct listNode *)temp->data);
        printf("\n");
        temp = temp->next;
        sublist_number++;
    }

    free_list(head);
    return 0;
}
