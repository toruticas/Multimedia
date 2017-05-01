#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
//#include "paulslib.h"

#define TRUE 1
#define FALSE 0
#define DICTIONARY_BUFFER 1024
#define WORD_BUFFER 1000

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

typedef char *string;

typedef struct {
  string *words;
  int last_position;
} TDictionary;

int ReadUInt(FILE *fptr, unsigned int *n, int swap) {
  unsigned char *cptr,tmp;

  if (fread(n,4,1,fptr) != 1) {
    return(FALSE);
  }

  if (swap) {
    cptr = (unsigned char *)n;
    tmp = cptr[0];
    cptr[0] = cptr[3];
    cptr[3] = tmp;
    tmp = cptr[1];
    cptr[1] = cptr[2];
    cptr[2] = tmp;
  }

  return(TRUE);
}

int ReadUShort(FILE *fptr, short unsigned *n, int swap) {
  unsigned char *cptr,tmp;

  if (fread(n,2,1,fptr) != 1) {
    return(FALSE);
  }

	if (swap) {
   	cptr = (unsigned char *)n;
   	tmp = cptr[0];
   	cptr[0] = cptr[1];
   	cptr[1] =tmp;
	}

  return(TRUE);
}

void addToDictionary(TDictionary *dictionary, string value) {
  char *str;
  str = (string) malloc( strlen(value) * sizeof(char));

  strcpy(str, value);
  dictionary->words[dictionary->last_position] = str;
  dictionary->last_position++;
}

int presentInDictionary(TDictionary dictionary, string s, string ch) {
  int i;
  char str[WORD_BUFFER];
  strcpy(str, s);
  strcat(str, ch);

  for (i = 0; i < dictionary.last_position; i++) {
    if (strcmp(dictionary.words[i], str) == 0) {
      return i;
    }
  }

  return -1;
}

int main(int argc, char **argv) {
  int i,j;
  int gotindex = FALSE;
  unsigned char grey,r,g,b;
  HEADER header;
  INFOHEADER infoheader;
  COLOURINDEX colourindex[256];
  FILE *fptr;
  TDictionary dictionary;
  char str[WORD_BUFFER], ch[WORD_BUFFER];
  int dicionary_pos;
  // string s, ch;

  /* Check arguments */
  if (argc < 2) {
    fprintf(stderr,"Usage: %s filename\n",argv[0]);
    exit(-1);
  }

  /* Open file */
  if ((fptr = fopen(argv[1],"r")) == NULL) {
    fprintf(stderr,"Unable to open BMP file \"%s\"\n",argv[1]);
    exit(-1);
  }

  /* Read and check the header */
  ReadUShort(fptr,&header.type,FALSE);
  fprintf(stderr,"ID is: %d, should be %d\n",header.type,'M'*256+'B');
  ReadUInt(fptr,&header.size,FALSE);
  fprintf(stderr,"File size is %d bytes\n",header.size);
  ReadUShort(fptr,&header.reserved1,FALSE);
  ReadUShort(fptr,&header.reserved2,FALSE);
  ReadUInt(fptr,&header.offset,FALSE);
  fprintf(stderr,"Offset to image data is %d bytes\n",header.offset);

  /* Read and check the information header */
  if (fread(&infoheader,sizeof(INFOHEADER),1,fptr) != 1) {
    fprintf(stderr,"Failed to read BMP info header\n");
    exit(-1);
  }
  fprintf(stderr,"Image size = %d x %d\n",infoheader.width,infoheader.height);
  fprintf(stderr,"Number of colour planes is %d\n",infoheader.planes);
  fprintf(stderr,"Bits per pixel is %d\n",infoheader.bits);
  fprintf(stderr,"Compression type is %d\n",infoheader.compression);
  fprintf(stderr,"Number of colours is %d\n",infoheader.ncolours);
  fprintf(stderr,"Number of required colours is %d\n",
    infoheader.importantcolours);

  /* Read the lookup table if there is one */
  for (i = 0 ; i < 255 ; i++) {
    colourindex[i].r = rand() % 256;
    colourindex[i].g = rand() % 256;
    colourindex[i].b = rand() % 256;
    colourindex[i].junk = rand() % 256;
  }

  if (infoheader.ncolours > 0) {
    for (i = 0 ; i < infoheader.ncolours ; i++) {
      if (fread(&colourindex[i].b,sizeof(unsigned char),1,fptr) != 1) {
        fprintf(stderr,"Image read failed\n");
        exit(-1);
      }
      if (fread(&colourindex[i].g,sizeof(unsigned char),1,fptr) != 1) {
        fprintf(stderr,"Image read failed\n");
        exit(-1);
      }
      if (fread(&colourindex[i].r,sizeof(unsigned char),1,fptr) != 1) {
        fprintf(stderr,"Image read failed\n");
        exit(-1);
      }
      if (fread(&colourindex[i].junk,sizeof(unsigned char),1,fptr) != 1) {
        fprintf(stderr,"Image read failed\n");
        exit(-1);
      }

      fprintf(stderr,"%3d\t%3d\t%3d\t%3d\n", i,
        colourindex[i].r, colourindex[i].g, colourindex[i].b);
    }
    gotindex = TRUE;
  }

  /* Seek to the start of the image data */
  fseek(fptr,header.offset,SEEK_SET);

  dictionary.words = malloc(DICTIONARY_BUFFER * sizeof(string*));
  dictionary.last_position = 0;

  for (i = 0; i < 255; i++) {
    sprintf(str, "%d", i);
    addToDictionary(&dictionary, str);
  }

  strcpy(str, "");

  /* Read the image */
  for (j = 0 ; j < infoheader.height ; j++) {
    for (i = 0 ; i < infoheader.width ; i++) {
      switch (infoheader.bits) {
        case 1:
          break;
        case 4:
          break;
        case 8:
          if (fread(&grey,sizeof(unsigned char),1,fptr) != 1) {
            fprintf(stderr,"Image read failed\n");
            exit(-1);
          }
          if (gotindex) {
            //putchar(colourindex[grey].r);
            //putchar(colourindex[grey].g);
            //putchar(colourindex[grey].b);
			      printf("(%d,%d,%d)", colourindex[grey].r, colourindex[grey].g, colourindex[grey].b);
          } else {
            //putchar(grey);
		        printf("(%d)", grey);
          }
          break;
        case 24:
          if (fread(&b,sizeof(unsigned char),1,fptr) != 1) {
            fprintf(stderr,"Image read failed\n");
            exit(-1);
          }
          if (fread(&g,sizeof(unsigned char),1,fptr) != 1) {
            fprintf(stderr,"Image read failed\n");
            exit(-1);
          }
          if (fread(&r,sizeof(unsigned char),1,fptr) != 1) {
            fprintf(stderr,"Image read failed\n");
            exit(-1);
          }
          //putchar(r);
          //putchar(g);
          //putchar(b);
		      // printf("(%d,%d,%d)", r, g, b);

          sprintf(ch, "%d", r);
          if (presentInDictionary(dictionary, str, ch) != -1) {
            strcat(str, ch);
          } else {
            fprintf(stdout, "%d ", presentInDictionary(dictionary, str, ""));
            strcat(str, ch);
            addToDictionary(&dictionary, str);
            strcpy(str, ch);
          }
          break;
       }
    } /* i */
  } /* j */
  //
  // for (i = 0; i < dictionary.last_position; i++) {
  //   fprintf(stdout, "%d\t | %s\n", i, dictionary.words[i]);
  // }

  free(dictionary.words);
  fclose(fptr);

  return 0;
}
