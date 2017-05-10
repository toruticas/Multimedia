#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include <getopt.h>
#include <unistd.h>

#include "encode.h"

unsigned long int __last_index_str__ = -1;

// Implement dictionary with Trie add the initial alphabet
void createDictionary(TDictionary *dictionary, int bits) {
  int i;
  char str[3];
  TWord word;

  dictionary->bits = bits;
  dictionary->length = 0;
  dictionary->max_words = (unsigned long int) pow(2, bits);
  dictionary->root = getNode();

  word.word = (unsigned char*) malloc(1 * sizeof(unsigned char));
  word.length = 1;

  for (i = 0; i < 255; i++) {
    word.word[0] = (unsigned char) i;
    insert(dictionary->root, word, i);
    dictionary->length++;
  }
}

// Add a new word to dictionary
void addToDictionary(TDictionary *dictionary, TWord word) {
  if (dictionary->length >= dictionary->max_words) {
    fprintf(stderr, "Limit of dictionary reached\n");
    exit(-1);
  }

  insert(dictionary->root, word, dictionary->length);
  dictionary->length++;
}

// Check if a word is present in dictionary
int presentInDictionary(TDictionary *dictionary, TWord str) {
  return search(dictionary->root, str);
}

// Implement pseudo code of LZW algorithm
void processValue(TDictionary *dictionary, TWord *str, unsigned char newValue, FILE *stream, TWord *aux) {
  int i;
  unsigned long int index;

  memcpy(aux->word, str->word, str->length);
  aux->word[str->length] = newValue;
  aux->length = str->length + 1;

  index = presentInDictionary(dictionary, (*aux));
  if (index != -1) {
    memcpy(str->word, aux->word, aux->length);
    str->length = aux->length;
    __last_index_str__ = index;
  } else {
    writeData(stream, __last_index_str__, dictionary->bits);
    // fprintf(stderr, "%d ", __last_index_str__);
    addToDictionary(dictionary, (*aux));
    str->word[0] = newValue;
    str->length = 1;
    __last_index_str__ = presentInDictionary(dictionary, (*str));
  }
}

// write data in oputfile
void writeData(FILE *stream, unsigned long int index, int bits) {
  unsigned char d_unsigned_char;
  unsigned short int d_short_int;
  unsigned int d_int;

  if (bits <= 8) {
    d_unsigned_char = (unsigned char) index;
    fwrite(&d_unsigned_char, sizeof(unsigned char), 1, stream);
  } else if (bits <= 16) {
    d_short_int = (unsigned short int) index;
    fwrite(&d_short_int, sizeof(unsigned short int), 1, stream);
  } else if (bits <= 32) {
    d_int = (unsigned int) index;
    fwrite(&index, sizeof(unsigned int), 1, stream);
  } else {
    fwrite(&index, sizeof(unsigned long int), 1, stream);
  }
}
