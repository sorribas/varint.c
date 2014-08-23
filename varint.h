#ifndef _VARINT_H_
#define _VARINT_H_

char* varint_encode(long long, char*, unsigned char*);
long long varint_decode(char*);

#endif
