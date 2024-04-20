#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

// Trie structure
struct Trie
{	
  int count; 
  struct Trie *children[26];
};

// Initializes a trie structure
struct Trie *createTrie()
{
  
  struct Trie* pTrie = (struct Trie *)malloc(sizeof(struct Trie));
  pTrie->count = 0;
  
  for (int i=0; i<26; i++)
    pTrie->children[i] = NULL;
  
  return pTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
  int nextIndex;
  int len;
  len = strlen(word); 
  
  for(int i=0; i<len; i++){
    nextIndex = word[i] - 'a';
    if (pTrie->children[nextIndex] == NULL){
      pTrie->children[nextIndex] = createTrie();
    }
    pTrie = pTrie->children[nextIndex];
  }

  pTrie->count += 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
  int nextIndex; 
  int len;
  len = strlen(word);
  struct Trie *temp = pTrie; 
  
  for(int i=0; i<len; i++){
    nextIndex = word[i] - 'a'; 
    if (temp->children[nextIndex] == NULL){
      return 0; 
    }
    temp = temp->children[nextIndex]; 
  }

  return temp->count; 
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
  for (int i=0; i<26; i++){
    if (pTrie->children[i] != NULL)
      deallocateTrie(pTrie->children[i]);
  }
  free(pTrie);
  return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
  FILE *fp; 
  int n; 

  fp = fopen(filename, "r"); 

  fscanf(fp, "%d", &n);

  for(int i=0; i<n; i++){
    pInWords[i] = (char * )malloc(21*sizeof(char)); 
    fscanf(fp,"%s", pInWords[i]);
  }
  fclose(fp); 

  return n;
}

int main(void) {
 
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