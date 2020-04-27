#include <stdio.h>

struct node {
    int value;
    struct node * left_child;
    struct node * right_child;
};

struct node * find(int value, struct node * root) {

    if (value == root->value) {
        return root;
    }
    if (value < root->value && root->left_child != NULL) {
        return find(value, root->left_child);
    }
    if (value > root->value && root->right_child != NULL) {
        return find(value, root->right_child);
    }
    return NULL;

}

int main() {

    struct node * ptr;

    struct node c = {69, NULL, NULL};
    struct node e = {17, NULL, NULL};
    struct node d = {12, NULL, NULL};
    struct node b = {13, &d, &e};
    struct node a = {21, &b, &c};

    ptr = &a;
    int val = find(17, ptr)->value;
    printf("%d\n", val);

}
