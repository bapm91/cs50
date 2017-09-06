#include <stdio.h>
#include <cs50.h>

int main () {
    int value;
    do {
        printf("Height: ");
        value = get_int();
    }
    while(value < 0 || value > 23);
    
    for (int i = 1; i <= value; i++) { // i - number of line
        int position = 0, second = 0; // position - index of char in line 
        while (value - i > position) { // print spaces
            printf(" ");
            position++;
        }
        
        while (value - i <= position && value > position) {// print group #
            printf("#");
            position++;
            second++;
        }
        
        printf("  "); // print two spaces
        while(second > 0) { // print second group of #
            printf("#");
            second--;
        }
        
        printf("\n");
    }
}