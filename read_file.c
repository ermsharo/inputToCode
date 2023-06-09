#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listNode {
    char* data;
    struct listNode* next;
};

void insert_at_end(struct listNode** head, char* value) {
    struct listNode* new_listNode = (struct listNode*)malloc(sizeof(struct listNode));
    new_listNode->data = value;
    new_listNode->next = NULL;

    if (*head == NULL) {
        *head = new_listNode;
    } else {
        struct listNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_listNode;
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
    char* input[] = {"aa", "202", "jump", "30", "40", "jump", "50", "60"};
    int input_length = sizeof(input) / sizeof(input[0]);

    struct listNode* head = NULL;
    struct listNode* sublist_head = NULL;

    for (int i = 0; i < input_length; i++) {
        char* current_str = input[i];

        if (strcmp(current_str, "jump") == 0) {
            if (sublist_head != NULL) {
                insert_at_end(&head, sublist_head);
            }
            sublist_head = NULL;
        } else {
            // int* current_int = (int*)malloc(sizeof(int));
            // *current_int = atoi(current_str);
            insert_at_end(&sublist_head, current_str);
        }
    }

    if (sublist_head != NULL) {
        insert_at_end(&head, sublist_head);
    }

    struct listNode* temp = head;
    int sublist_number = 0;
    while (temp != NULL) {
        printf("%d: ", sublist_number);
        print_list((struct listNode*)temp->data);
        printf("\n");
        temp = temp->next;
        sublist_number++;
    }

    free_list(head);
    return 0;
}
