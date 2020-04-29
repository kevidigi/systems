#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char first_name[20+1];
    char second_name[20+1];
} name;                     // a string (char array) - +1 is just a menmonic for the trailing \0


void bubble_sort (name *names, int n) {             // why not passed as an array? unnecessary cos array names are pointers?
    
    int i; 
    int j = n; 
    int s = 1;
    name tempname;

    while (s) {
        s = 0;
        for (i = 0; i < j; i++) {
            if (strncmp(names[i].second_name, names[i-1].second_name, 20) < 0) {        // and you can index a pointer?
                strncpy(tempname.first_name, names[i].first_name, 20);
                strncpy(tempname.second_name, names[i].second_name, 20);
                strncpy(names[i].first_name, names[i-1].first_name, 20);
                strncpy(names[i].second_name, names[i-1].second_name, 20);
                strncpy(names[i-1].first_name, tempname.first_name, 20);
                strncpy(names[i-1].second_name, tempname.second_name, 20);
                s = 1;
            }
        }
        j--;
    }
}
    

int main() {

    printf("You will be prompted to enter four names.\n");

    name names[4];
    int arraysize = sizeof(names) / (sizeof names[0]);

    for (int i = 0; i < arraysize; i++) {

        printf("Please enter a first name: ");
        scanf("%20s", names[i].first_name);
        printf("Please enter a surname: ");
        scanf("%20s", names[i].second_name);
    }

    bubble_sort(names, 4);

    for(int i = 0; i < 4; i++) {
        printf("%s\n", names[i].second_name);
    }

}


