#ifndef FILEMANAGER_H_INCLUDED
#define FILEMANAGER_H_INCLUDED

// This struct represents a array of indexes
typedef struct {
  int *buffer;
  int length;
  int bits;
} TFileManager;

TFileManager createFileManager(int);
void addIndex(TFileManager*, int);
void writeFile(FILE*, TFileManager);
void analyze(FILE*, unsigned char *buffer_byte, unsigned char current_byte, unsigned char *bits_in_byte_used, unsigned char *total_to_analyze);

#endif
