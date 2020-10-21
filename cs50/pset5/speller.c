// Implements a dictionary's functionality
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5381;
// variable to store number of words globally
unsigned int wordCount = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash the word to obtain a hash value
    int index = hash(word);
    // temprorary cursor pointer variable
    node *cursor = table[index];
    // loop over each node until at the end of the list
    while (cursor != NULL)
    {
        // compare the current word cursor is pointing to to the input word
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // if no match found - go to next item in list
        cursor = cursor->next;
    }
    // return false if word is not found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Credit to: Dan Bernstein
    // Name: djb2
    // Link: http://www.cse.yorku.ca/~oz/hash.html
    // Some modifications made -- added brackets around line 57 - as well as the 'tolower' on the same line
    unsigned long hash = 5381;
    int c;
    while ((c = tolower(*word++)))
        hash = ((hash << 5) + hash) + c;
    return (hash % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // initialize word variable
    char word[LENGTH + 1];
    // Open dictionary file
    FILE *d = fopen(dictionary, "r");
    // if invalid file
    if (d == NULL)
    {
        return false;
    }
    // Loop entil end of file
    // Read strings from file one at a time
    while (fscanf(d, "%s", word) != EOF)
    {
        // create memory for new node
        node *n = malloc(sizeof(node));
        // ensure enough memory
        if(n == NULL)
        {
            // exit if not enough memory
            return false;
        }
        // copy the word into your new node
        strcpy(n->word, word);
        // set next to NULL
        n->next = NULL;
        // Hash that word to obtain a hash value
        int index = hash(word);
        // if first item at index
        if (table[index] == NULL)
        {
            // point 'head' at newnode
            table[index] = n;
        }
        // if not the first item
        else
        {
            // point newnode at first item in the list
            n->next = table[index];
            // point 'head' at newnode
            table[index] = n;
        }
        // increment wordcount
        wordCount++;
    }
    // close file and return true
    fclose(d);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // self explanatory
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // loop through each linked list in table
    for (int i = 0; i < N; i ++)
    {
        // create head variable
        node *head = table[i];
        // same thing for temp
        node *temp = head;
        // create cursor and point it to the head
        node *cursor = head;
        // loop until cursor == NULL - meaning end of list
        while (cursor != NULL)
        {
            // point cursor to the next item
            cursor = cursor->next;
            // free the memory of tmps pointee
            free(temp);
            // point tmp to cursor
            temp = cursor;
        }
    }
    return true;
}
