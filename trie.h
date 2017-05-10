#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Size of Alphabet
#define ALPHABET_SIZE 256

// This struct represents a string with alphabet composed by 255 characters
typedef struct {
  unsigned char *word;
  int length;
} TWord;

// Tire Node
typedef struct TrieNode {
  struct TrieNode *children[ALPHABET_SIZE];
  int index;
} TTrie;

// Get a new node from Trie
TTrie *getNode(void);
// Insert a word in Trie
void insert(TTrie*, TWord, int);
// Search a word in Trie
int search(TTrie*, TWord);

#endif
