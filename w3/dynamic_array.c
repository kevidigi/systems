#include <stdio.h>
#include <stdlib.h>

int main() {

    printf("How many numbers do you want to average? ");
    
    int count;
   
    if (scanf("%d", &count) == EOF) {   // this useage pattern scans into the varibale while simultaneously checking input
        exit(-1);
    }
    
    int* array = malloc(count * sizeof(int));

    printf("Okay, enter %d numbers: ", count);
    // so an int pointer, pointing to the start of a block of memory the size of int * count
    // aka an array of ints of that size? I can see where the distinction blurs
    
    for (int i = 0; i < count; i++) {

        int number;

        if (scanf("%d", &number) == EOF) {
            exit(-1);
        }
        array[i] = number;
    }

    float sum = 0.0f;
    for (int i = 0; i < count; i++) {
        sum += array[i];
    }
    
    printf("The average is %.2f\n", sum / count);
    free(array);
}
