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


bit_filter b_attach(FILE *f) {
	bit_filter b = (bit_filter) malloc(sizeof(bit_io_t));
	b->bits = b->accu = 0;
	b->fp = f;
	return b;
}

void b_detach(bit_filter bf) {
	if (bf->bits) {
		bf->accu <<= 8 - bf->bits;
		fputc(bf->accu, bf->fp);
	}
	free(bf);
}

void b_write(byte *buf, size_t n_bits, size_t shift, bit_filter bf) {
	uint32_t accu = bf->accu;
	int bits = bf->bits;

	buf += shift / 8;
	shift %= 8;

	while (n_bits || bits >= 8) {
		while (bits >= 8) {
			bits -= 8;
			fputc(accu >> bits, bf->fp);
			accu &= (1 << bits) - 1;
		}
		while (bits < 8 && n_bits) {
			accu = (accu << 1) | (((128 >> shift) & *buf) >> (7 - shift));
			--n_bits;
			bits++;
			if (++shift == 8) {
				shift = 0;
				buf++;
			}
		}
	}
	bf->accu = accu;
	bf->bits = bits;
}

void writeFile(FILE *f, TFileManager filemanager) {
    unsigned char *position;
    int i, aux;

    bit_filter b = b_attach(f);

    for (i = 0; i < filemanager.length; i++) {
        position = (unsigned char*) &filemanager.buffer[i];
        b_write(position, 8, 0, b);

        if (filemanager.bits < 16) {
            aux = (16 - filemanager.bits) % 8;
            b_write(position + 1, 8 - aux, aux, b);
        } else {
            b_write(position, 8, 0, b);

            if (filemanager.bits >= 16 && filemanager.bits < 24) {
                aux = (24 - filemanager.bits) % 8;
                b_write(position + 1, 8 - aux, aux, b);
            } else {
                b_write(position, 8, 0, b);

                if (filemanager.bits >= 24) {
                    aux = 32 - filemanager.bits;
                    b_write(position + 1, 8 - aux, aux, b);
                } else {
                    b_write(position, 8, 0, b);
                }
            }
        }
    }
	b_detach(b);
}
