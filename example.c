#include <stdio.h>
#include <stdlib.h>
#include "varint.h"

int main() {
  unsigned long long number = 23113293191329;
  char* str = calloc(7, sizeof(char));
  unsigned char bts;

  varint_encode(number, str, 7, &bts);

  unsigned long long r = varint_decode(str, 7, &bts);
  printf("RESULT: %lld\nBYTES: %hhu\n", r, bts);

  return 0;
}
