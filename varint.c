#include "varint.h"
#define NULL 0

static char MSB = 0x80;
static char MSBALL = ~0x7F;

char* varint_encode(long long n, char* buf, unsigned char* bytes) {
  char* ptr = buf;

  while (n & MSBALL) {
    *(ptr++) = (n & 0xFF) | MSB;
    n = n >> 7;
  }
  *ptr = n;
  if (bytes != NULL) *bytes = ptr - buf + 1;

  return buf;
}

long long varint_decode(char* buf) {
  return 0;
}
