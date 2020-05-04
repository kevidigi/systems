#include <stdio.h>
#include <stdlib.h>

struct node {

    struct node *next;
    struct node *prev;
    char *value;

};

typedef struct node node;

void print_list(node *head) {
    while(head->next) {
        printf("%s\n", head->value);
        head = head->next;
    }
    printf("%s\n", head->value);
}

void reverse_list(node *head) {

    node *temp = head->next;

    head->next = head->prev;
    head->prev = temp;

    if(temp){
        reverse_list(temp);
    }

}

node * create_node(char * val_ptr) {
    node * n = malloc(sizeof(node));
    n->value = val_ptr;
    return n;
}

void destroy_node(node * n) {
    free(n);
}


int main() {

    node a = {NULL, NULL, "a"}; 
    node b = {NULL, NULL, "b"};
    node c = {NULL, NULL, "c"};

    a.next = &b;
    b.prev = &a;
    b.next = &c;
    c.prev = &b;

    print_list(&a);
    printf("\n");
    print_list(&c);
    printf("\n");

    reverse_list(&a);
    
    print_list(&c);
    printf("\n");
    print_list(&a);
    printf("\n");

    node *d = create_node("d");
    print_list(d);
    destroy_node(d);

}
