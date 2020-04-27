#include <stdio.h>
#include <stdlib.h>
#include "linked_list_extended.h"

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
