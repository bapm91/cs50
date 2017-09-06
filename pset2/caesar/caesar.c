#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    int index = atoi(argv[1]);
    
    printf("plaintext: ");
    string s = GetString();
    printf("ciphertext: ");
    
    int difference;
    for(int i = 0; i < strlen(s); i++) {
        if ('a' <= s[i] && s[i] <= 'z') {
            difference = 0;
            while (s[i] + index + difference > 'z') {
                difference += ('a' - 1) - 'z';
            }
            s[i] += index + difference;
        }
        if ('A' <= s[i] && s[i] <= 'Z'){
            difference = 0;
            while (s[i] + index + difference > 'Z'){
                difference += ('A' - 1) - 'Z';
            }
            s[i] += index + difference;
        }
        printf("%c", s[i]);
    }
    printf("\n");
}