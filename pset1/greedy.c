#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main () {
    float input;
    printf("O hai!");
    
    do {
        printf("How much change is owed?\n");
        input = roundf(get_float() * 100);
    }
    while(input < 0);
    
    int monets = 0;
    while(input >= 25) {
        input = input - 25;
        monets++;
    }
    while(input >= 10) {
        input = input - 10;
        monets++;
    }
    while(input >= 5) {
        input = input - 5;
        monets++;
    }
    while(input >= 1) {
        input = input - 1;
        monets++;
    }
    
    printf("%i\n", monets);
}