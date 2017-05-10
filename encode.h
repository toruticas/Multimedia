#ifndef ENCODE_H_INCLUDED
#define ENCODE_H_INCLUDED

#include "trie.h"

#define WORD_BUFFER 100000 // 100kb

// Define a structure of dictionary based in Trie
typedef struct {
  TTrie *root;
  int length;
  int max_words;
  int bits;
} TDictionary;

// Build a dictionary made with Trie
void createDictionary(TDictionary*, int);
// Add a word to dictionary
void addToDictionary(TDictionary*, TWord);
// Check if a word is present in dictionary
int presentInDictionary(TDictionary*, TWord);
// Process a newValue in LZW interaction
void processValue(TDictionary*, TWord*, unsigned char, FILE*, TWord*);
// Write data in output file
void writeData(FILE*, unsigned long int, int);

#endif
