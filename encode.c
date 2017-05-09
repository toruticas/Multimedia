#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "encode.h"

unsigned long int __last_index_str__ = -1;

void createDictionary(TDictionary *dictionary, int bits) {
  int i;
  char str[3];

  dictionary->max_words = (unsigned long int) pow(2, bits);
  
  fprintf(stderr, "MAX WORD %d\n", dictionary->max_words);
  dictionary->words = malloc(dictionary->max_words * sizeof(TWord));
  dictionary->length = 0;
  dictionary->bits = bits;

  for (i = 0; i < 255; i++) {
    dictionary->words[dictionary->length].word = (string) malloc(1*sizeof(byte));
    dictionary->words[dictionary->length].word[0] = (byte) i;
    dictionary->words[dictionary->length].length = 1;
    dictionary->length++;
  }
}

void addToDictionary(TDictionary *dictionary, TWord word) {
  if (dictionary->length >= dictionary->max_words) {
    fprintf(stderr, "Limit of dictionary reached\n");
    exit(-1);
  }

    // fprintf(stderr, "BEFORE %d ", dictionary->length);
  dictionary->words[dictionary->length].word = malloc((word.length + 1) * sizeof(byte));
  // fprintf(stderr, "AFTER ");
  memcpy(dictionary->words[dictionary->length].word, word.word, word.length);
  dictionary->words[dictionary->length].length = word.length;
  dictionary->length++;
}

unsigned long int presentInDictionary(TDictionary *dictionary, TWord str) {
  unsigned long int i;

  for (i = 0; i < dictionary->length; i++) {
    if (compareWords(str, dictionary->words[i]) == true) {
      return i;
    }
  }

  return -1;
}

bool compareWords(TWord a, TWord b) {
  int i;

  if (a.length != b.length) {
    return false;
  }

  if (memcmp(a.word, b.word, sizeof(a.word)) != 0) {
    return false;
  }

  return true;
}

void processValue(TDictionary *dictionary, TWord *str, byte newValue, FILE *stream, TWord *aux) {
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
    addToDictionary(dictionary, (*aux));
    str->word[0] = newValue;
    str->length = 1;
    __last_index_str__ = presentInDictionary(dictionary, (*str));
  }
}

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


/*
 * THIS SECTION IS ONLY FOR ACADEMIC REASONS
 */
void printDictionary(TDictionary dictionary) {
  int i;

  for (i = 0; i < dictionary.length; i++) {
    printWord(dictionary.words[i]);
  }
}

void printWord(TWord word) {
  int i;

  fprintf(stdout, "Word: ");
  for (i = 0; i < word.length; i++) {
    fprintf(stdout, "%d ", (int) word.word[i]);
  }
  fprintf(stdout, "\n");
}
