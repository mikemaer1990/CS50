// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>
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
    // Some modifications credit to Reddit user SocratesSatisfied because I couldn't get the original to work properly
    unsigned long hash = 5381;
    int c = *word;
    c = tolower(c);
    while (*word != 0)
    {
        hash = ((hash << 5) + hash) + c;
        c = *word++;
        c = tolower(c);
    }
    return (hash % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // initialize word variable
    char word[LENGTH + 1];
    // Open dictionary file
    FILE *dictionary_pointer = fopen(dictionary, "r");
    // if invalid file
    if (dictionary_pointer == NULL)
    {
        return false;
    }
    // Loop entil end of file
    // Read strings from file one at a time
    while (fscanf(dictionary_pointer, "%s", word) != EOF)
    {
        // create memory for new node
        node *newNode = malloc(sizeof(node));
        // ensure enough memory
        if(newNode == NULL)
        {
            // exit if not enough memory
            return false;
        }
        // copy the word into your new node
        strcpy(newNode->word, word);
        // Hash that word to obtain a hash value
        int index = hash(word);
        // if first item at index
        if (table[index] == NULL)
        {
            // point 'head' at newnode
            table[index] = newNode;
        }
        // if not the first item
        else
        {
            // point newnode at first item in the list
            newNode->next = table[index];
            // point 'head' at newnode
            table[index] = newNode;
        }
        // increment wordcount
        wordCount++;
    }
    // close file and return true
    fclose(dictionary_pointer);
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
        node *head = table[i];
        node *cursor = head;
        node *temp = cursor;
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
