#include <assert.h>
#include "varint.h"
#define NULL 0

static char MSB = 0x80;
static char MSBALL = ~0x7F;

char* varint_encode(long long n, char* buf, int len, unsigned char* bytes) {
  char* ptr = buf;

  while (n & MSBALL) {
    *(ptr++) = (n & 0xFF) | MSB;
    n = n >> 7;
    assert((ptr - buf) < len);
  }
  *ptr = n;
  if (bytes != NULL) *bytes = ptr - buf + 1;

  return buf;
}

long long varint_decode(char* buf, int len, unsigned char* bytes) {
  long long result = 0;
  int bits = 0;
  char *ptr = buf;
  long long ll;
  while (*ptr & MSB) {
    ll = *ptr;
    result += ((ll & 0x7F) << bits);
    ptr++;
    bits += 7;
    assert((ptr - buf) < len);
  }
  ll = *ptr;
  result += ((ll & 0x7F) << bits);

  if (bytes != NULL) *bytes = ptr - buf + 1;

  return result;
}
