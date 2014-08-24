varint.c
========

Static C library to use [protobuf-style varint](https://developers.google.com/protocol-buffers/docs/encoding#varints) in C.

API
---

#### `char* varint_encode(long long n, char* buf, int len, unsigned char* bytes)`

Encodes a `long long` number into varint and stores the result in the char
array passed the `buf` parameter. If you want to know how many bytes the encoded
number takes, you cans pass the `bytes` parameter and the amount of bytes will
be stored there.

### `long long varint_decode(char buf*, int len, unsigned char* bytes);`

Decodes a varint passed as a char array and returns it as a `long long` integer.
If you want to know how many bytes the decoder when through, pass a the `bytes`
argument and it will be stored there.

Building
--------

Just run

```
make
```
and you should get a static library in `varint.a`.

License
-------

MIT
