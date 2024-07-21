#ifndef MD5_H
#define MD5_H

#include <string.h>
#include <stdio.h>

#include <ft_ssl.h>

typedef struct {
    unsigned int state[4];  // state (ABCD)
    unsigned int count[2];  // number of bits, modulo 2^64 (low-order word first)
    unsigned char buffer[64];  // input buffer
} MD5_CTX;

void MD5Init(MD5_CTX *context);
void MD5Update(MD5_CTX *context, const unsigned char *input, unsigned int inputLen);
void MD5Final(unsigned char digest[16], MD5_CTX *context);

void transform_md5(unsigned char *digest, char *hex_output);
void process_md5_stdin(ft_flags flags);
void process_md5_input(char *input, bool is_string, ft_flags flags);

#endif
