#include <stdio.h>

int main() {

    int x = 420;
    double y = 69.0;
    printf("address of x: %p; %lu bytes\n", &x, sizeof(x));
    printf("address of y: %p; %lu bytes\n", &y, sizeof(y));

}


