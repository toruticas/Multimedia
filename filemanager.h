#ifndef FILEMANAGER_H_INCLUDED
#define FILEMANAGER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// This struct represents a array of indexes
typedef uint8_t byte;

typedef struct {
  int *buffer;
  int length;
  int bits;
} TFileManager;

typedef struct {
	FILE *fp;
	uint32_t accu;
	int bits;
} bit_io_t, *bit_filter;

TFileManager createFileManager(int);
void addIndex(TFileManager*, int);
void writeFile(FILE*, TFileManager);
// void analyze(FILE *stream, int value, unsigned char *buffer_byte, unsigned char *bits_in_byte_used, int bits);

#endif
