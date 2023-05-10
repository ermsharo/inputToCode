#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 120
#define MAX_ARRAY_LEN 1000

int insert_between_equal(char* arr[], int len) {
    int i, j;
    int insertion_count = 0;
    // create a new array to hold the modified elements
    char** new_arr = (char**)malloc(2*len*sizeof(char*));
    int new_idx = 0; // next free index in new array
    for (i = 0; i < len; i++) {
        // copy element to new array
        new_arr[new_idx++] = arr[i];
        if (i < len - 1 && strcmp(arr[i], arr[i+1]) == 0) {
            // elements are equal, so insert a new element between them
            char* new_str = "new element";  // replace with your desired new element
            new_arr[new_idx++] = new_str;  // insert new element
            insertion_count++;  // increment insertion count
        }
    }
    // copy remaining elements to new array
    for (j = i - insertion_count; j < len; j++) {
        new_arr[new_idx++] = arr[j];
    }
    int new_len = new_idx;
    // copy modified elements back to original array
    for (i = 0; i < new_len; i++) {
        arr[i] = new_arr[i];
    }
    free(new_arr);  // free dynamically allocated memory
    return new_len;
}

void print_string_array(char** arr) {
  int size = 0;

  // Loop through the array until a NULL pointer is encountered
  while (arr[size] != NULL) {
    size++;
  }

  // Loop through the array again and print each string
  for (int i = 0; i < size; i++) {
    printf("%s\n", arr[i]);
  }
}

int main() {
    char* arr[] = {"apple", "banana", "banana", "cherry", "cherry", "cherry", NULL};
    int len = 6;
    len = insert_between_equal(arr, len);
    // allocate dynamic array to store modified strings
    char** strs = (char**)malloc(len * sizeof(char*));
    int i;
    for (i = 0; i < len; i++) {
        strs[i] = (char*)malloc(strlen(arr[i]) + 1);  // allocate memory for each string
        strcpy(strs[i], arr[i]);  // copy string to dynamic array
    }
    // print out modified array
    for (i = 0; i < len; i++) {
        printf("%s ", strs[i]);
        free(strs[i]);  // free memory for each string
    }
    free(strs);  // free memory for dynamic array
    return 0;
}