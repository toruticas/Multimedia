#include <iostream>
#include <cmath>

#include "filemanager.h"

TFileManager createFileManager(int bits) {
  TFileManager file;
  file.buffer = (int*) malloc(pow(2, bits) * sizeof(int));
  file.bits = bits;
  file.length = 0;

  return file;
}

void addIndex(TFileManager *file, int index) {
  file->buffer[file->length] = index;
  file->length++;
}

// write data in oputfile
void writeFile(FILE *stream, TFileManager filemanager) {
  unsigned char byte;
  unsigned short int d_short_int;
  int d_int, i;
  int bits_left = 0;

  int x = 65536;
  unsigned char *y = (unsigned char*) &x;
  fprintf(stderr, "0x%x | 0x%x | 0x%x | 0x%x\n\n", (int) *(y), (int) *(y + 1), (int) *(y + 2), (int) *(y + 3));
  unsigned char *position;

  unsigned char total_to_analyze = 0;
  unsigned char bits_in_byte_used = 0;
  unsigned char buffer_byte = 0;

  for (i = 0; i < filemanager.length; i++) {
    // d_int = (int) filemanager.buffer[i];
    // fwrite(&filemanager.buffer[i], sizeof(int), 1, stream);

    total_to_analyze = filemanager.bits;

    if (filemanager.bits < 16) {
      // pass two bytes more relevant of integer because integer aways will be more longer than the size of alphabet
      position = (unsigned char*) &filemanager.buffer[i];
      analyze(stream, &buffer_byte, (unsigned char) *position, &bits_in_byte_used, &total_to_analyze);
      analyze(stream, &buffer_byte, (unsigned char) *(position + 1), &bits_in_byte_used, &total_to_analyze);
    } else if (filemanager.bits < 24) {
      // pass three bytes of integer
      analyze(stream, &buffer_byte, (unsigned char) *position, &bits_in_byte_used, &total_to_analyze);
      analyze(stream, &buffer_byte, (unsigned char) *(position + 1), &bits_in_byte_used, &total_to_analyze);
      analyze(stream, &buffer_byte, (unsigned char) *(position + 2), &bits_in_byte_used, &total_to_analyze);
    } else {
      // pass the four bytes of integer
      analyze(stream, &buffer_byte, (unsigned char) *position, &bits_in_byte_used, &total_to_analyze);
      analyze(stream, &buffer_byte, (unsigned char) *(position + 1), &bits_in_byte_used, &total_to_analyze);
      analyze(stream, &buffer_byte, (unsigned char) *(position + 2), &bits_in_byte_used, &total_to_analyze);
      analyze(stream, &buffer_byte, (unsigned char) *(position + 3), &bits_in_byte_used, &total_to_analyze);
    }
  }

  fwrite(&buffer_byte, sizeof(unsigned char), 1, stream);
  // write in file here "buffer_byte"
  // fwrite(buffer_byte, sizeof(unsigned char), 1, stream);
}

void analyze(FILE *stream, unsigned char *buffer_byte, unsigned char current_byte, unsigned char *bits_in_byte_used, unsigned char *total_to_analyze) {
  unsigned char current_byte_copy = current_byte;
  unsigned char full_byte = 255;

  // fprintf(stderr, "%d:", (unsigned char) current_byte);
  // fprintf(stderr, "%d:", (unsigned char) *bits_in_byte_used);
  // fprintf(stderr, "%d ", (unsigned char) *total_to_analyze);
  if (*bits_in_byte_used == 0) {
    *buffer_byte = current_byte;

    if (*total_to_analyze < 8) {
      *bits_in_byte_used = *total_to_analyze;
      *total_to_analyze = 0;
    } else {
      *bits_in_byte_used = 0;
      *total_to_analyze = *total_to_analyze - 8;
      // write in file here "buffer_byte"
      fwrite(buffer_byte, sizeof(unsigned char), 1, stream);
    }
  } else {
    if (*bits_in_byte_used + *total_to_analyze <= 8) {
      current_byte << *bits_in_byte_used;
      *buffer_byte = *buffer_byte | current_byte;
      total_to_analyze = 0;
      *bits_in_byte_used = *bits_in_byte_used + *total_to_analyze;
      // fprintf(stderr, "NUNCA ENTROU AQUI3");
    } else {
      current_byte_copy << *bits_in_byte_used;
      *buffer_byte = *buffer_byte | current_byte;
      *bits_in_byte_used = 8 - *bits_in_byte_used;
      *total_to_analyze = *total_to_analyze - *bits_in_byte_used;
      // fprintf(stderr, "NUNCA ENTROU AQUI4");
      // write in file here "buffer_byte"
      fwrite(buffer_byte, sizeof(unsigned char), 1, stream);
      current_byte >> *bits_in_byte_used;
      *buffer_byte = full_byte & current_byte;
    }
  }
}
