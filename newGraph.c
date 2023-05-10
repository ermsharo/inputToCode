#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listNode {
    char* data;
    int index;
    struct listNode* next;
};

void insert_at_end(struct listNode** head, char* value, int index) {
    struct listNode* new_node = (struct listNode*)malloc(sizeof(struct listNode));
    new_node->data = value;
    new_node->index = index;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        struct listNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void print_list(struct listNode* head) {
    struct listNode* temp = head;
    while (temp != NULL) {
        printf("%s ", temp->data);
        temp = temp->next;
    }
}

void free_list(struct listNode* head) {
    while (head != NULL) {
        struct listNode* temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

int main() {
    char* input[] = {"10", "20", "jump", "jump", "40", "jump", "50", "60"};
    int input_length = sizeof(input) / sizeof(input[0]);

    struct listNode* head = NULL;
    struct listNode* sublist_head = NULL;
    int sublist_number = 1;

    for (int i = 0; i < input_length; i++) {
        char* current_str = input[i];

        if (strcmp(current_str, "jump") == 0) {
            if (sublist_head != NULL) {
                insert_at_end(&head, sublist_head->data, sublist_number);
                printf("%d: ", sublist_number);
                print_list(sublist_head);
                printf("\n");
                sublist_number++;
            }
            sublist_head = NULL;
        } else {
            char* current_char = (char*)malloc(strlen(current_str) + 1);
            strcpy(current_char, current_str);
            insert_at_end(&sublist_head, current_char, i);
        }
    }

    if (sublist_head != NULL) {
        insert_at_end(&head, sublist_head->data, sublist_number);
        printf("%d: ", sublist_number);
        print_list(sublist_head);
        printf("\n");
    }

    free_list(head);
    return 0;
}
