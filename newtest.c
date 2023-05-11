#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **get_elements_ending_with_colon(char **arr, int n) {
    char **result = malloc((n+1) * sizeof(char *));
    int j = 0;

    for (int i = 0; i < n; i++) {
        int len = strlen(arr[i]);
        if (len > 0 && arr[i][len-1] == ':') {
            result[j] = malloc(len + 1);
            strcpy(result[j], arr[i]);
            j++;
        }
    }

    result[j] = NULL;
    result = realloc(result, (j+1) * sizeof(char *));
    return result;
}

int main() {
    char *arr[] = {"pants;", "shoes;", "pants:", "belt;", "shoes;", "belt:", "jacket;", "shirt:", "belt;", "tie;", "tie:", "jacket;", "jacket:", "socks:", "shoes;", "shoes:", "watch:"};
    int n = sizeof(arr) / sizeof(char *);

    char **result = get_elements_ending_with_colon(arr, n);

    for (int i = 0; result[i] != NULL; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }

    free(result);

    return 0;
}