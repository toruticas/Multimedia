#ifndef BITMAP_H_INCLUDED
#define BITMAP_H_INCLUDED

#define TRUE 1
#define FALSE 0

typedef struct {
  unsigned short int type;                 /* Magic identifier            */
  unsigned int size;                       /* File size in bytes          */
  unsigned short int reserved1, reserved2;
  unsigned int offset;                     /* Offset to image data, bytes */
} HEADER;

typedef struct {
  unsigned int size;               /* Header size in bytes      */
  int width,height;                /* Width and height of image */
  unsigned short int planes;       /* Number of colour planes   */
  unsigned short int bits;         /* Bits per pixel            */
  unsigned int compression;        /* Compression type          */
  unsigned int imagesize;          /* Image size in bytes       */
  int xresolution,yresolution;     /* Pixels per meter          */
  unsigned int ncolours;           /* Number of colours         */
  unsigned int importantcolours;   /* Important colours         */
} INFOHEADER;

typedef struct {
  unsigned char r,g,b,junk;
} COLOURINDEX;

int ReadUInt(FILE*, unsigned int*, int);
int ReadUShort(FILE*, short unsigned*, int);

#endif
