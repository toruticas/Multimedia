#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (255)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

typedef struct {
  unsigned char *word;
  int length;
} TWord;

// trie node
typedef struct TrieNode {
  struct TrieNode *children[ALPHABET_SIZE];
  int index;
} TTrie;

TTrie *getNode(void);
void insert(TTrie *root, TWord key, int index);
int search(TTrie *root, TWord key);


#endif
