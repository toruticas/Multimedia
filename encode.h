#ifndef ENCODE_H_INCLUDED
#define ENCODE_H_INCLUDED

#define WORD_BUFFER 100000 // 100kb
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
  unsigned long int length;
  unsigned long int max_words;
  int bits;
} TDictionary;

void addToDictionary(TDictionary*, TWord);
unsigned long int presentInDictionary(TDictionary *dictionary, TWord s);
void createDictionary(TDictionary *dictionary, int bits);
bool compareWords(TWord, TWord);
void processValue(TDictionary*, TWord*, byte, FILE*, TWord*);
void writeData(FILE *stream, unsigned long int index, int bits);

void printDictionary(TDictionary);
void printWord(TWord);

#endif
