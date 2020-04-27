#include <stdio.h>

// pass in x as your numbr of iterations i.e. fib steps
// starting with 0 and 1

int fib(int x) {
    int x1 = 0;
    int x2 = 1;

    while (x>0) {
        int xsum = x1 + x2; // until the steps are exhausted (decrement), add the two previous and shift everything forward
        x2 = x1;
        x1 = xsum;
        x = x-1;
    }
    return x2;
}

int main() {
    int fib_6 = fib(6);
    printf("fib(6) = %d\n", fib_6);
}
