#ifndef ENCODE_H_INCLUDED
#define ENCODE_H_INCLUDED

#include "trie.h"

#define WORD_BUFFER 100000 // 100kb

typedef unsigned char byte;
typedef byte *string;

typedef struct {
  TTrie *root;
  int length;
  int max_words;
  int bits;
} TDictionary;

void createDictionary(TDictionary *dictionary, int bits);
void addToDictionary(TDictionary*, TWord);
int presentInDictionary(TDictionary *dictionary, TWord s);
void processValue(TDictionary*, TWord*, byte, FILE*, TWord*);
void writeData(FILE *stream, unsigned long int index, int bits);

// void printDictionary(TDictionary);
void printWord(TWord);

#endif
