// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 200000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check( const char *word)
{
    // TODO
    
   
    node *cursor = NULL ; 
    
    int hashed= hash(word);
    
    cursor= table[hashed];
    

    while(cursor!=NULL)
    {
        
        if (strcasecmp(cursor->word,word)==0)
        {
            return true ; 
        }
            else
        {
            cursor=cursor->next ;
        }
        
    }
    
    if(cursor==NULL)
    {
        return false ;
    }
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
 /* credits to...
     *https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
     */
    unsigned int hash = 0;
    
    char Word[LENGTH+1];
    
    for(int i=0, n=strlen(word); i<n; i++)
    {
        Word[i]=word[i];
        
        if(isupper(word[i]))
        {
            Word[i] = tolower(word[i]);

        }
        
        hash = (hash << 2) ^ Word[i];
    
    }
    
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
int ze = 0;
bool load(const char *dictionary)
{
    // TODO


    FILE *input=fopen(dictionary,"r");
    char Word[LENGTH+1];
   // node *n= NULL;
    
    if(input==NULL)
    {
        printf("wrong\n");
        return false ;
    }
    
    while(fscanf(input, "%s", Word)!=EOF)
    {
     ze++ ;
     node *n= malloc(sizeof(node));

     if(n==NULL)
     {
        printf("wrong\n");
        return false ;
     }

     strcpy(n->word, Word);

     n->next= NULL ;

     int index = hash(Word);

     n->next=table[index];

     table[index]= n;
    }
    
    fclose(input) ;
    return true ;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return ze;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

       node *cursor = NULL ;
       node *tmp = NULL ;
    
    for(int i=0; i<N; i++)
    {
       cursor= table[i];
       tmp= table[i];
       
       while(cursor!=NULL)
       {
       
       tmp=cursor;
       cursor=cursor->next;
      
       free(tmp);
       }
    }
    
    return true;
}
