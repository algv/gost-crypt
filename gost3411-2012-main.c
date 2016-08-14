#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <crypto/internal/hash.h>
//#include <linux/crypto.h>
#include <asm/byteorder.h>

#include "gost3411-2012-core.h"

#define STRIBOG_256_DIGEST_SIZE (256 / 8)
#define STRIBOG_256_BLOCK_SIZE  64
#define STRIBOG_512_DIGEST_SIZE (512 / 8)
#define STRIBOG_512_BLOCK_SIZE  64

static int stribog_256_init(struct shash_desc *desc)
{
	GOST34112012Context *CTX = shash_desc_ctx(desc);

	GOST34112012Init(CTX, 256);
	return 0;
}

static int stribog_512_init(struct shash_desc *desc)
{
	GOST34112012Context *CTX = shash_desc_ctx(desc);

	GOST34112012Init(CTX, 512);
	return 0;
}

static int stribog_update(struct shash_desc *desc, const u8 *data, unsigned int len)
{
	GOST34112012Context *CTX = shash_desc_ctx(desc);

	GOST34112012Update(CTX, data, len);
	return 0;
}

static int stribog_final(struct shash_desc *desc, u8 *out)
{
	GOST34112012Context *CTX = shash_desc_ctx(desc);

	GOST34112012Final(CTX, out);
	return 0;
}

static struct shash_alg stribog256_alg = {
	.digestsize		=	STRIBOG_256_DIGEST_SIZE,
	.init   		=	stribog_256_init,
	.update 		=	stribog_update,
	.final  		=	stribog_final,
	.descsize		=	sizeof(GOST34112012Context),
	.base			=	{
		.cra_name		=	"stribog256",
		.cra_driver_name	=	"stribog256-generic",
		.cra_flags		=	CRYPTO_ALG_TYPE_SHASH,
		.cra_blocksize		=	STRIBOG_256_BLOCK_SIZE,
		.cra_module		=	THIS_MODULE,
	}
};

static struct shash_alg stribog512_alg = {
	.digestsize		=	STRIBOG_512_DIGEST_SIZE,
	.init   		=	stribog_512_init,
	.update 		=	stribog_update,
	.final  		=	stribog_final,
	.descsize		=	sizeof(GOST34112012Context),
	.base			=	{
		.cra_name		=	"stribog512",
		.cra_driver_name	=	"stribog512-generic",
		.cra_flags		=	CRYPTO_ALG_TYPE_SHASH,
		.cra_blocksize		=	STRIBOG_512_BLOCK_SIZE,
		.cra_module		=	THIS_MODULE,
	}
};


static int __init stribog_init(void)
{
	int ret;

	ret = crypto_register_shash(&stribog256_alg);
	if (ret < 0)
		goto err_out;
	ret = crypto_register_shash(&stribog512_alg);
	if (ret < 0)
		goto err_out_256;

	return 0;

err_out_256:
	crypto_unregister_shash(&stribog256_alg);
err_out:
	return ret;
}

static void __exit stribog_fini(void)
{
	crypto_unregister_shash(&stribog256_alg);
	crypto_unregister_shash(&stribog512_alg);
}

module_init(stribog_init);
module_exit(stribog_fini);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Petr Sokolov <petka.sokolov@gmail.com>");
MODULE_DESCRIPTION("GOST R 34.11-2012");
MODULE_VERSION("0.0.1");
MODULE_ALIAS_CRYPTO("stribog256");
MODULE_ALIAS_CRYPTO("stribog256-generic");
MODULE_ALIAS_CRYPTO("stribog512");
MODULE_ALIAS_CRYPTO("stribog512-generic");

