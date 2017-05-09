#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include "encode.h"

unsigned long int __last_index_str__ = -1;

void createDictionary(TDictionary *dictionary, int bits) {
  int i;
  char str[3];
  TWord word;

  dictionary->bits = bits;
  dictionary->length = 0;
  dictionary->max_words = (unsigned long int) pow(2, bits);

  word.word = (string) malloc(1*sizeof(byte));
  word.length = 1;

  for (i = 0; i < 255; i++) {
    word.word[0] = (byte) i;
    insert(dictionary->root, word, i);
    dictionary->length++;
  }
}

void addToDictionary(TDictionary *dictionary, TWord word) {
  if (dictionary->length >= dictionary->max_words) {
    fprintf(stderr, "Limit of dictionary reached\n");
    exit(-1);
  }

  insert(dictionary->root, word, dictionary->length);
  dictionary->length++;
}

int presentInDictionary(TDictionary *dictionary, TWord str) {
  return search(dictionary->root, str);
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
// void printDictionary(TDictionary dictionary) {
//   int i;
//
//   for (i = 0; i < dictionary.length; i++) {
//     printWord(dictionary.words[i]);
//   }
// }
//
// void printWord(TWord word) {
//   int i;
//
//   fprintf(stdout, "Word: ");
//   for (i = 0; i < word.length; i++) {
//     fprintf(stdout, "%d ", (int) word.word[i]);
//   }
//   fprintf(stdout, "\n");
// }
