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
  long long result = 0;
  int bits = 0;
  long long ll;
  while (*buf & MSB) {
    ll = *buf;
    result += ((ll & 0x7F) << bits);
    buf++;
    bits += 7;
  }
  ll = *buf;
  result += ((ll & 0x7F) << bits);

  return result;
}
