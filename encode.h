#ifndef ENCODE_H_INCLUDED
#define ENCODE_H_INCLUDED

#define WORD_BUFFER 1000000 // 1MB
#define true 1
#define false 0

typedef unsigned char byte;
typedef byte bool;
typedef byte *string;

typedef struct {
  string word;
  int length;
} TWord;

typedef struct {
  TWord *words;
  int length;
} TDictionary;

void addToDictionary(TDictionary*, TWord);
int presentInDictionary(TDictionary *dictionary, TWord s);
void createDictionary(TDictionary *dictionary, int bits);
bool compareWords(TWord, TWord);
void processValue(TDictionary*, TWord*, byte);

void printDictionary(TDictionary);
void printWord(TWord);

#endif
