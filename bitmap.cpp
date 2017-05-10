#include <iostream>
#include "bitmap.h"

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
