#include <stdio.h>

void swap (void *x, void *y, size_t l) {

    char *a = x;
    char *b = y;
    char tmp;

    while(l--) {

        tmp = *a;
        *a++ = *b;
        *b++ = tmp; 
    }

}

int main() {

    int int_a = 420;
    int int_b = 69;

    printf("int_a = %d, int_b = %d\n", int_a, int_b);

    swap(&int_a, &int_b, sizeof(int));
    
    printf("int_a = %d, int_b = %d\n", int_a, int_b);

    double dbl_a = 4.20;
    double dbl_b = 6.9;

    printf("dbl_a = %f, dbl_b = %f\n", dbl_a, dbl_b);

    swap(&dbl_a, &dbl_b, sizeof(double));
    
    printf("dbl_a = %f, dbl_b = %f\n", dbl_a, dbl_b);

}
