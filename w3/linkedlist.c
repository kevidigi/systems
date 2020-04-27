#include <stdio.h>

struct node {
    char val;
    struct node * next;
};

int main() {

    struct node c = {'c', NULL};
    struct node b = {'b', &c};
    struct node a = {'a', &b};


    struct node * ptr = &a;
    while (ptr) {
        printf("%c\n", (*ptr).val);
        ptr = (*ptr).next;
    }
}
