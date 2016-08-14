// kuznechik.h
// 04-Jan-15  Markku-Juhani O. Saarinen <mjos@iki.fi>

#ifndef KUZNECHIK_H
#define KUZNECHIK_H

#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>

// my 128-bit datatype
typedef union {	
    uint64_t q[2];
    uint8_t  b[16];
} w128_t;

// cipher context
typedef struct {
	w128_t k[10];		// round keys
} kuz_key_t;

// init lookup tables
void kuz_init(void);

// key setup
void kuz_set_encrypt_key(kuz_key_t *subkeys, const uint8_t key[32]);	
void kuz_set_decrypt_key(kuz_key_t *subkeys, const uint8_t key[32]);	

// single-block ecp ops
void kuz_encrypt_block(kuz_key_t *subkeys, void *out, const void *in);
void kuz_decrypt_block(kuz_key_t *subkeys, void *out, const void *in);

#endif
