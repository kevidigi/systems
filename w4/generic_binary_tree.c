#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    void *value_ptr;
    struct node *left_child;
    struct node *right_child;
};

typedef struct node node;


node * create_tree(void *value, node *left_child, node *right_child) {
    node *root = malloc(sizeof(node));      // we assign malloc's returned void pointer to a typed pointer
    if (root) {                             // this checks malloc returned successfully I think? cos failure = null = false
        root->value_ptr = value;
        root->left_child = left_child;
        root->right_child = right_child;
    }
    return root;
}


void destroy_tree(node *root) {
    if (root) {
        destroy_tree(root->left_child);
        destroy_tree(root->right_child);
        free(root);
    }
}


void print_string(void *value_ptr) {
    char *string = value_ptr;                   // casting the void * to a type *, giving the bits meaning
    printf("%s\n", string);
}


void print(node *root, void(* print_function)(void *) ) {
    if (root) {
        print_function(root->value_ptr);
        print(root->left_child, print_function);
        print(root->right_child, print_function);
    }
}           // so we define a parameter of this function to be a function pointer - returntype (* paramvar) (argument types)


int main() {
    
    node *root = create_tree("b", create_tree("a", NULL, NULL), create_tree("c", create_tree("d", NULL, NULL), 
                                                                                    create_tree("e", NULL, NULL)));

    print(root, print_string);      // we could define a 'print_somethingelse' function and pass it here
}

