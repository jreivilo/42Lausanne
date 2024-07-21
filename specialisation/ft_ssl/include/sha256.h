#ifndef SHA256_H
# define SHA256_H

#include <string.h>
#include <stdio.h>

#include <ft_ssl.h>

// typedef struct {
//     unsigned int data[64];
//     unsigned int datalen;
//     unsigned long long bitlen;
//     unsigned int state[8];
// } SHA256_CTX;

struct BUFFER_STATE {
    uint8_t data[64];
    int datalen;
    unsigned long long bitlen;
};


void sha256_init(uint32_t state[8], struct BUFFER_STATE *buffstate);
void sha256_update(uint32_t state[8], struct BUFFER_STATE *buffstate, const uint8_t data[], size_t len);
void sha256_final(uint32_t state[8], struct BUFFER_STATE *buffstate, uint8_t hash[]);

void transform_sha256(unsigned char *digest, char *hex_output);
void process_sha256_stdin(ft_flags flags);
void process_sha256_input(char *input, bool is_string, ft_flags flags);

#endif 