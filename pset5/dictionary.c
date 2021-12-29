// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdbool.h>
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
const unsigned int N = 150000;
int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // printf("HATDOGGERS");
    char lower_word[LENGTH+1];
    for (int i = 0; i < LENGTH+1; i++)
    {
	    lower_word[i] = 0;
    }
    
    for (int i = 0; i < strlen(word); i++)
    {
	lower_word[i] = tolower(word[i]);
    }

    int index = hash(word);
    node *current_node = malloc(sizeof(node)); 
    current_node = table[index];

    while (current_node != NULL)
    {
        if (strcasecmp(current_node->word, word) == 0)
        {
        	return true;
        }
        current_node = current_node->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // int l = strlen(word); 
    // int sum = 0;
    // for (int i = 0; i < l; i++)
    // {
    //     sum += (int) word[i] - (int) 'a';
    // }
    // return sum % N;
    // djb2
    unsigned int hash = 5381;
    int c;
    
    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
            return false;
    }
            
    char word[LENGTH+1];

    while(fscanf(dict, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
        	return false;
        }
        strcpy(n->word, word);
        int index = hash(word);
        n->next = table[index];
        table[index] = n;
	word_count++;
    }

    fclose(dict);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
   node *current_node = malloc(sizeof(node));
   node *tmp = malloc(sizeof(node));
    for (int i = 0; i < N; i++)
    {
	current_node = table[i];
	while (current_node != NULL)
	{
		tmp = current_node;
		current_node = current_node->next;	
		free(tmp);
	}
	free(current_node);
    }

    return true;
}
