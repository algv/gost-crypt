#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/crypto.h>
#include <asm/byteorder.h>

#include "kuznechik.h"

#define KUZNECHIK_KEY_SIZE	32
#define KUZNECHIK_BLOCK_SIZE	16

struct crypto_kuznechik_ctx {
	kuz_key_t encrypt_key;
	kuz_key_t decrypt_key;
};

int kuznechik_set_key(struct crypto_tfm *tfm, const u8 *in_key, unsigned int key_len)
{
	struct crypto_kuznechik_ctx *ctx = crypto_tfm_ctx(tfm);
	if (key_len == KUZNECHIK_KEY_SIZE)
	{
		kuz_set_encrypt_key(&ctx->encrypt_key, in_key);
		kuz_set_decrypt_key(&ctx->decrypt_key, in_key);
		return 0;
	}
	return -EINVAL;
}

static void kuznechik_encrypt(struct crypto_tfm *tfm, u8 *out, const u8 *in)
{
	struct crypto_kuznechik_ctx *ctx = crypto_tfm_ctx(tfm);
	kuz_encrypt_block(&ctx->encrypt_key, out, in);
}

static void kuznechik_decrypt(struct crypto_tfm *tfm, u8 *out, const u8 *in)
{
	struct crypto_kuznechik_ctx *ctx = crypto_tfm_ctx(tfm);
	kuz_decrypt_block(&ctx->decrypt_key, out, in);
}

static struct crypto_alg kuznechik_alg = {
	.cra_name		=	"kuznechik",
	.cra_driver_name	=	"kuznechik-generic",
	.cra_priority		=	100,
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	KUZNECHIK_BLOCK_SIZE,
	.cra_ctxsize		=	sizeof(struct crypto_kuznechik_ctx),
	.cra_alignmask		=	3,
	.cra_module		=	THIS_MODULE,
	.cra_u			=	{
		.cipher = {
			.cia_min_keysize	=	KUZNECHIK_KEY_SIZE,
			.cia_max_keysize	=	KUZNECHIK_KEY_SIZE,
			.cia_setkey		=	kuznechik_set_key,
			.cia_encrypt		=	kuznechik_encrypt,
			.cia_decrypt		=	kuznechik_decrypt
		}
	}
};

static int __init kuznechik_init(void)
{
	kuz_init();
	return crypto_register_alg(&kuznechik_alg);
}

static void __exit kuznechik_exit(void)
{
	crypto_unregister_alg(&kuznechik_alg);
}

module_init(kuznechik_init);
module_exit(kuznechik_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Petr Sokolov <petka.sokolov@gmail.com>");
MODULE_DESCRIPTION("GOST R 34.12-2015");
MODULE_VERSION("0.0.1");

