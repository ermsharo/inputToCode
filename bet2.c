#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100000

char** insert_new_element(char** arr, int size) {
  char** new_arr = malloc(MAX_SIZE * sizeof(char*));
  int new_arr_size = 0;

  for (int i = 0; i < size; i++) {
    // Add the current string to the new array
    new_arr[new_arr_size++] = arr[i];
    
    // Check if the next string is the same as the current one
    if (i < size - 1 && strcmp(arr[i], arr[i+1]) == 0) {
      // Add the new element to the new array
      new_arr[new_arr_size++] = "new_element";
    }
  }

  // Null-terminate the new array
  new_arr[new_arr_size] = NULL;

  return new_arr;
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
  char* arr[] = {"apple", "banana", "banana", "cherry", "cherry", "cherry"};
  int size = sizeof(arr)/sizeof(arr[0]);

  char** new_arr = insert_new_element(arr, size);

  // Print the new array
  printf("New array:\n");
//   for (int i = 0; i < size*2-1; i++) {
//     printf("%s ", new_arr[i]);
//   }

print_string_array(new_arr);
  printf("\n");

  // Free the memory used by new_arr
  free(new_arr);

  return 0;
}