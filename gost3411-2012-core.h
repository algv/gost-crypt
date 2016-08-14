/*
 * Copyright (c) 2013, Alexey Degtyarev. 
 * All rights reserved.
 *
 * $Id: gost3411-2012-core.h 526 2013-05-26 18:24:29Z alexey $
 */

//#include <string.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
//#include <linux/errno.h>
//#include <crypto/internal/hash.h>
//#include <linux/crypto.h>
//#include <asm/byteorder.h>

#include "gost3411-2012-config.h"

#if defined _MSC_VER
#define GOST32112012_ALIGN(x) __declspec(align(x))
#else
#define GOST32112012_ALIGN(x) __attribute__ ((__aligned__(x)))
#endif

GOST32112012_ALIGN(16) typedef union uint512_u
{
    unsigned long long QWORD[8];
} uint512_u;

#include "gost3411-2012-const.h"
#include "gost3411-2012-precalc.h"

GOST32112012_ALIGN(16) typedef struct GOST34112012Context
{
    GOST32112012_ALIGN(16) unsigned char buffer[64];
    GOST32112012_ALIGN(16) union uint512_u hash;
    GOST32112012_ALIGN(16) union uint512_u h;
    GOST32112012_ALIGN(16) union uint512_u N;
    GOST32112012_ALIGN(16) union uint512_u Sigma;
    size_t bufsize;
    unsigned int digest_size;
} GOST34112012Context;

void GOST34112012Init(GOST34112012Context *CTX,
        const unsigned int digest_size);

void GOST34112012Update(GOST34112012Context *CTX, const unsigned char *data,
        size_t len); 

void GOST34112012Final(GOST34112012Context *CTX, unsigned char *digest); 

void GOST34112012Cleanup(GOST34112012Context *CTX);
