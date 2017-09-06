#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main () {
    string s = GetString();
    for (int i = 0; i < strlen(s); i++) {
        if (s[i - 1] != ' ' && s[i - 1] != (char) 0) {
            continue;
        }
        if (('0' <= s[i] && s[i] <= '9') || ('A' <= s[i] && s[i] <= 'Z')){
            printf("%c", (char) s[i]);
        }
        if('a' <= s[i] && s[i] <= 'z') {
            s[i] += 'A' - 'a';
            printf("%c", (char) s[i]);
        }
    }
    printf("\n");
}