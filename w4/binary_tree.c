#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    const char *value;
    struct node *left_child;
    struct node *right_child;
};

typedef struct node node;


node * create_tree(const void *value, node *left_child, node *right_child) {
    node *root = malloc(sizeof(node));      // we assign malloc's returned void pointer to a typed pointer
    if (root) {                             // this checks malloc returned successfully I think? cos failure = null = false
        root->value = value;
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

int main() {
    
    node *root = create_tree("b", create_tree("a", NULL, NULL), create_tree("c", create_tree("d", NULL, NULL), 
                                                                                    create_tree("e", NULL, NULL)));

    printf("%s\n", root->right_child->left_child->value);
}

