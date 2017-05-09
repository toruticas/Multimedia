#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "encode.h"

void createDictionary(TDictionary *dictionary, int bits) {
  byte i;
  char str[3];

  dictionary->words = malloc(1024 * 3000 * sizeof(TWord*));
  dictionary->length = 0;

  for (i = 0; i < 255; i++) {
    dictionary->words[dictionary->length].word = (string) malloc(1*sizeof(byte));
    dictionary->words[dictionary->length].word[0] = (byte) i;
    dictionary->words[dictionary->length].length = 1;
    dictionary->length++;
  }
}

void addToDictionary(TDictionary *dictionary, TWord word) {
  dictionary->words[dictionary->length].word = word.word;
  dictionary->words[dictionary->length].length = word.length;
  dictionary->length++;
}

int presentInDictionary(TDictionary *dictionary, TWord str) {
  int i;

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

  for (i = 0; i < b.length; i++) {
    if (b.word[i] != a.word[i]) {
      return false;
    }
  }

  return true;
}

void processValue(TDictionary *dictionary, TWord *str, byte newValue) {
  int i;
  TWord aux;
  aux.word = (string) malloc((str->length + 1) * sizeof(byte));

  for (i = 0; i < str->length; i++) {
    aux.word[i] = str->word[i];
    aux.length = str->length;
  }
  aux.word[str->length] = newValue;
  aux.length++;

  // fprintf(stdout, "NEW VALUE: %d\n", (int) newValue);
  // fprintf(stdout, "AUX: ");
  // printWord(aux);

  if (presentInDictionary(dictionary, aux) != -1) {
    free(str->word);
    str->word = aux.word;
    str->length = aux.length;
  } else {
    fprintf(stdout, "%d ", presentInDictionary(dictionary, (*str)));
    addToDictionary(dictionary, aux);
    // printWord(aux);
    str->word[0] = newValue;
    str->length = 1;
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
