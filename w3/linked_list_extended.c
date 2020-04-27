#include <stdio.h>
#include <stdlib.h>

struct node {
    char value;
    struct node * next;
};

struct node* create_node(char value) {
    struct node * node_ptr = malloc(sizeof(struct node));
    node_ptr->value = value;
    node_ptr->next = NULL;
    return node_ptr;
}

void add_node_to_list(struct node* list, struct node* node) {
    if (!list) {
        return;
    }
    while (list->next) {
        list = list->next;
    }
    list->next = node;
}

void free_list(struct node* list) {
    if (!list) {
        return;
    }
    while (list->next) {
        struct node* head = list;
        list = list->next;
        free(head);
    }
}

int main() {

    struct node* root = create_node('x');
    struct node* first = create_node('y');
    struct node* second = create_node('z');
    struct node* third = create_node('q');

    add_node_to_list(root, first);
    add_node_to_list(root, second);
    add_node_to_list(root, third);

    struct node* ptr = root;
    while(ptr) {
        printf("%c\n", ptr->value);
        ptr = ptr->next;
    }

}

