#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../varint.h"

static int tests_ran = 0;

void tassert(int x) {
  tests_ran++;
  assert(x);
}

void encode_test() {
  unsigned long long number = 23113293191329;
  char* str = calloc(7, sizeof(char));
  unsigned char bts;

  varint_encode(number, str, 7, &bts);
  tassert(bts == 7);
  tassert((unsigned char)(*(str++)) == 0xA1);
  tassert((unsigned char)(*(str++)) == 0xB1);
  tassert((unsigned char)(*(str++)) == 0x85);
  tassert((unsigned char)(*(str++)) == 0xDD);
  tassert((unsigned char)(*(str++)) == 0xD7);
  tassert((unsigned char)(*(str++)) == 0xA0);
  tassert((unsigned char)(*str)     == 0x05);

  /*******************************/
  number = 353938623;
  str = calloc(5, sizeof(char));

  varint_encode(number, str, 5, &bts);
  tassert(bts == 5);
  tassert((unsigned char)(*(str++)) == 0xBF);
  tassert((unsigned char)(*(str++)) == 0xD9);
  tassert((unsigned char)(*(str++)) == 0xE2);
  tassert((unsigned char)(*(str++)) == 0xA8);
  tassert((unsigned char)(*str)     == 0x01);

  /*******************************/

  number = 2142;
  str = calloc(2, sizeof(char));
  varint_encode(number, str, 2, NULL);
  tassert((unsigned char)(*(str++)) == 0xDE);
  tassert((unsigned char)(*str)     == 0x10);
}

void decode_test() {
  char str[] = {0x90, 0xD7, 0x99, 0xDB, 0x82, 0xB2, 0xF0, 0x01, 0xEE, 0xEE, 0xEE};
  unsigned char bts = 0;
  unsigned long long res = 0;

  res = varint_decode(str, 11, &bts);
  tassert(bts == 8);
  tassert(res == 1057249877715856);

  /*******************************/

  char str2[] = {0x98, 0x12};
  res = varint_decode(str2, 2, NULL);
  tassert(res == 2328);
}

void encoding_length_test() {
  tassert(varint_encoding_length(2) == 1);
  tassert(varint_encoding_length(16383) == 2);
  tassert(varint_encoding_length(2097151) == 3);
  tassert(varint_encoding_length(268435455) == 4);
  tassert(varint_encoding_length(34359738367) == 5);
  tassert(varint_encoding_length(4398046511103) == 6);
  tassert(varint_encoding_length(562949953421311) == 7);
  tassert(varint_encoding_length(72057594037927935) == 8);
  tassert(varint_encoding_length(9223372036854775807U) == 9);
  tassert(varint_encoding_length(18446744073709551615U) == 10);
}

int main() {
  encode_test();
  decode_test();
  encoding_length_test();
  printf("%d tests ok\n", tests_ran);
  return 0;
}
