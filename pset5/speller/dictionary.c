/**
 * Implements a dictionary's functionality.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
#define HASH_TABLE_LENGTH 100000

#define LENGTH_WORD 47

int hash_code(const char *word);
int Hash_size = 0;

typedef struct node {
    char word[50];
    struct node *next;
}
node;

node* link_list[HASH_TABLE_LENGTH];
node* single_link;
node* step = NULL;
char s[50];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int len = strlen(word);
    for(int i = 0; i < len; i++){
        s[i] = tolower(word[i]);
    }
    s[len] = '\0';
    
    int index = hash_code(s);
    
    node *single = link_list[index];
    while(single != NULL){
        if(strcmp(single->word, s) == 0) {
            return true;
        }
        single = single->next;
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary) {
    int hashVal;
    
    FILE *dic = fopen(dictionary, "r");
    if(dic == NULL) {
        fprintf(stderr, "File %s does not exist\n", dictionary);
        return false;
    }
    
    while(fgets(s, LENGTH_WORD, dic) != NULL) {
        if (!isalpha(s[0])) {
            continue;
        }
        single_link = malloc(sizeof(struct node));
        single_link->next = NULL;
        s[strlen(s) - 1] = '\0';
        
        strcpy(single_link->word, s);
        hashVal = hash_code(s);
        
        if (link_list[hashVal] == NULL) {
            link_list[hashVal] = single_link;
        } else {
            single_link->next = link_list[hashVal];
            link_list[hashVal] = single_link;
        }
        Hash_size++;
    }
    fclose(dic);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void) {
    return Hash_size;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void) {
    free(single_link);
    return true;
}

int hash_code(const char *word) {
    int hashVal = 0;
    
    while (*word) {
        hashVal = (hashVal * 29 + *word++) % HASH_TABLE_LENGTH;
    }
    
    return hashVal;
}
