#ifndef _VARINT_H_
#define _VARINT_H_

char* varint_encode(long long, char*, int, unsigned char*);
long long varint_decode(char*, int, unsigned char*);
int encodingLength(long long);

#endif
