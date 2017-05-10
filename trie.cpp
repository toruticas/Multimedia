// C implementation of search and insert operations
// on Trie
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdbool>

#include "encode.h"
#include "trie.h"

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void) {
  struct TrieNode *pNode = NULL;

  pNode = (struct TrieNode *) malloc(sizeof(struct TrieNode));

  if (pNode) {
    int i;

    pNode->index = -1;

    for (i = 0; i < ALPHABET_SIZE; i++) {
      pNode->children[i] = NULL;
    }
  }

  return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, TWord key, int dictionary_index) {
    int level;
    int index;
    struct TrieNode *pCrawl = root;
    //

    for (level = 0; level < key.length; level++) {
      index = key.word[level];
      if (!pCrawl->children[index]) {
        pCrawl->children[index] = getNode();
      }

      pCrawl = pCrawl->children[index];
    }
    //
    // // mark last node as leaf
    pCrawl->index = dictionary_index;
}

// Returns the position of a word or -1 if not found
int search(struct TrieNode *root, TWord key) {
  int level;
  int index;
  struct TrieNode *pCrawl = root;

  for (level = 0; level < key.length; level++) {
    index = key.word[level];

    if (!pCrawl->children[index]) {
      return -1;
    }

    pCrawl = pCrawl->children[index];
  }

  if (pCrawl != NULL && pCrawl->index != -1) {
    return pCrawl->index;
  } else {
    return -1;
  }
}
