// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// MAY NEED TO INCREASE THIS -- 5381?
const unsigned int N = 25;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    // case insensitive
    // PSEUDOCODE
    // Hash the word to obtain a hash value
        // poop = hash(word);
    // Access linked list at that hash value
    // check that list looking for word
        // use strcasecmp(word)
        // to traverse list
            // set up variable CURSOR which points to the first element in the list
            // check if first element is the same as the word you are looking for?
            // if not then
                // cursor = cursor->next
                // if cursor OR cursor->next == NULL
                // word not found - invalid word
                // return false
            // if found
                // return true - word found

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // credit to - Dan Bernstein / djb2
    // unsigned long hash(unsigned char *str)
    // {
    //     unsigned long hash = 5381;
    //     int c;
    //     while (c = *str++)
    //     {
    //         hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    //     }
    //     return hash;
    // }

    // PSEUDOCODE
    // input = word (alphabetical chars and maybe apostrophes)
    // output = index number between 0 and N - 1 INCLUSIVE
    // change N
        //  the larger N is the more buckets
    // if your function ends up with a number greater than N
        // value % N
        // will return a value in the appropriate range

    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // PSEUDOCODE
    int index = 0;
    unsigned char *word;
    // Open dictionary file
    FILE *d = fopen(dictionary, "r");
    // if invalid file
    if (d == NULL)
    {
        // error message and return 1
        printf("Invalid Dictionary File\n");
        return 1;
    }
    // else
    // Loop entil end of file\
    // Read strings from file one at a time
    WHILE (fscanf(d, "%s", word) != EOF)
    {
        // Not sure if this will work - but is this to create 'head'
        // int head = table[index]
        // create memory for new node
        node *n = malloc(sizeof(node));
        // ensure enough memory
        if(n == NULL)
        {
            // print error if not enough memory
            printf("Error\n")
            return 1
        }
        // copy the word into your new node
        strcpy(n->word, word);
        // n->next = NULL ?? not sure why i put this here..
        // Hash that word to obtain a hash value
        index = hash(word);
        // if first item at index
        if (table[index]->next == NULL)
        {
            // point 'head' at n
            table[index]->next = n;
            // point n at nothing
            n->next = NULL;
        }
        // if not the first item
        else
        {
            // point n at first item in the list
            n->next = table[index][0];
            // point 'head' at n
            table[index]->next = n;
        }
    }

    // TODO
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // keep track of total # of words as loading them in a global varibal and return that
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // anytime you use malloc
    // you must use free();
    // free each linked list in your hashtable
    // loop over each item
    // HOW to free a linked list
        // create a pointer cursor that points to the first item in list
        // create a temp variable that also points to the first item
        // loop until cursor = NULL
            // cursor = cursor->next
            // free(temp)
            // temp = cursor
    return false;
}
