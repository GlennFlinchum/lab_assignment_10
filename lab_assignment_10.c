#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int count;
    struct Trie* next[26];
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* root = malloc(sizeof(struct Trie));
    root->count = 0;

    for (int i=0; i<26; i++) 
        root->next[i] = NULL;

    return root;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie* current = pTrie;
    int index;

    for (int i = 0; i < strlen(word); i++)
    {
        index = word[i] - 'a';
        if (!current->next[index])
            current->next[index] = createTrie();
        
        current = current->next[index];
    }
    // Mark the end of the word
    current->count++;
}


// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* current = pTrie;
    int index;

    for (int i = 0; i < strlen(word); i++)
    {
        index = word[i] - 'a';
        if (!current->next[index])
            return 0; // Word not found
        
        current = current->next[index];
    }

    return current->count;
}


// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for (int i = 0; i < 26; i++){
        if (pTrie->next[i] != NULL) 
            deallocateTrie(pTrie->next[i]);
    }
    free(pTrie);
    return NULL; 
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    int n = 0;
    FILE *inFile = fopen(filename, "r");
    if (inFile == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    // Read the number of words
    fscanf(inFile, "%d", &n);
    // Allocate memory for each word
    for (int i = 0; i < n; i++)
    {
        pInWords[i] = malloc(100 * sizeof(char)); // Assuming maximum word length is 100
        fscanf(inFile, "%s", pInWords[i]);
    }

    fclose(inFile);
    return n;
}


int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}