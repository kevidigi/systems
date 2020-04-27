#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    int number, guess;
    srand(time(0));
    number = rand() % (10+1);

    printf("Guess what the number is: ");
    
    while (scanf("%d", &guess) == 1) {

        if (number == guess) {

            printf("You got it!\n");
            break;
        }
        printf("Your guess was too %s.\n", number < guess ? "high" : "low" );
    }
}
