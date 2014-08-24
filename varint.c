#include <assert.h>
#include "varint.h"
#define NULL 0

static const char MSB = 0x80;
static const char MSBALL = ~0x7F;

static const unsigned long long N1 = 128; // 2 ^ 7
static const unsigned long long N2 = 16384;
static const unsigned long long N3 = 2097152;
static const unsigned long long N4 = 268435456;
static const unsigned long long N5 = 34359738368;
static const unsigned long long N6 = 4398046511104;
static const unsigned long long N7 = 562949953421312;
static const unsigned long long N8 = 72057594037927936;
static const unsigned long long N9 = 9223372036854775808U;

long long ll_pow(long long base, int exp) {
  int i;
  long long res = 1;
  for (i = 0; i < exp; i++) {
    res *= base;
  }

  return res;
}

int varint_encoding_length(long long n) {
  return (
      n < N1 ? 1
    : n < N2 ? 2
    : n < N3 ? 3
    : n < N4 ? 4
    : n < N5 ? 5
    : n < N6 ? 6
    : n < N7 ? 7
    : n < N8 ? 8
    : n < N9 ? 9
    :         10
  );
}

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
