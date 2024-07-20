#ifndef SHA256_H
# define SHA256_H

#include <string.h>
#include <stdio.h>

#include <ft_ssl.h>

struct sha256_ctx {
    unsigned int data[16];
    unsigned int datalen;
    unsigned long long bitlen;
    unsigned int state[8];
};

void sha256_init(struct sha256_ctx *ctx);
void sha256_update(struct sha256_ctx *ctx, const unsigned char data[], size_t len);
void sha256_final(struct sha256_ctx *ctx, unsigned char hash[]);

#endif 