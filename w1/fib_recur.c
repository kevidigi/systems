#include <stdio.h>

// compute the x-th fibonacci number if starting from x1 and x2

int fib (int x, int x1, int x2) {

    if (x == 0) {
        return x2; // if x is 0, no further numbers in the sequence  
    }
    else {
        return fib(x - 1, x1 + x2, x1); // if x is not 0, we count down through iterations recursively, til x=0
    }

}

int main() {
    int fib_6 = fib(6, 0, 1);
    printf("fib(6) =  %d\n", fib_6);
}


