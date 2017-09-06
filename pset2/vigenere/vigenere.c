#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main (int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    
    string key = argv[1];
    for (int i = 0; i < strlen(key); i++){
        if (!isalpha(key[i])) {
            printf("Keyword must only contain letters A-Z and a-z");
            return 1;
        }
        key[i] = toupper(key[i]);
    }
    int keys[strlen(key)];
    for (int i = 0; i < strlen(key); i++) {
        keys[i] = key[i] - 'A';
    }
    
    printf("plaintext: "); 
    string s = GetString();
    printf("ciphertext: ");
    
    int index;
    for(int i = 0; i < strlen(s); i++) {
        if (!isalpha(s[i])) {
            printf("%c", s[i]);
            continue;
        }
        if(index == strlen(key)){
            index = 0;
        }
        if (isupper(s[i])){
            s[i] = ((s[i] - 65 + keys[index]) % 26) + 65;
            index++;
        } else {
            s[i] = ((s[i] - 97 + keys[index]) % 26) + 97;
            index++;
        } 
        printf("%c", s[i]);
    }
    printf("\n");
}