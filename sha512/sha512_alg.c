/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_alg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:24:25 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/23 15:35:13 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "sha512.h"

void		sha512_init(t_ctx *ctx)
{
	ctx->len_hi = 0LL;
	ctx->len_lo = 0LL;
	ctx->buf_len = 0;
	ft_memset(ctx->buf, 0, 128);
	ctx->state[0] = 0x6a09e667f3bcc908ULL;
	ctx->state[1] = 0xbb67ae8584caa73bULL;
	ctx->state[2] = 0x3c6ef372fe94f82bULL;
	ctx->state[3] = 0xa54ff53a5f1d36f1ULL;
	ctx->state[4] = 0x510e527fade682d1ULL;
	ctx->state[5] = 0x9b05688c2b3e6c1fULL;
	ctx->state[6] = 0x1f83d9abfb41bd6bULL;
	ctx->state[7] = 0x5be0cd19137e2179ULL;
}

void		sha512_update(t_ctx *ctx, u_char *buf, uint64_t len)
{
	uint		i;
	uint64_t	l;

	i = 0;
	while (i < len)
	{
		ctx->buf[ctx->buf_len] = buf[i];
		ctx->buf_len++;
		if (ctx->buf_len == 128)
		{
			sha512_transform(ctx, ctx->buf);
			l = ctx->len_lo + 128 * 8;
			if (l < ctx->len_lo)
				ctx->len_hi++;
			ctx->len_lo = l;
			ctx->buf_len = 0;
		}
		i++;
	}
}

static void	sha512_encode(u_char *b, uint64_t *x, uint len)
{
	uint	i;
	uint	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		b[j + 7] = (u_char)(x[i] & 0xff);
		b[j + 6] = (u_char)((x[i] >> 8) & 0xff);
		b[j + 5] = (u_char)((x[i] >> 16) & 0xff);
		b[j + 4] = (u_char)((x[i] >> 24) & 0xff);
		b[j + 3] = (u_char)((x[i] >> 32) & 0xff);
		b[j + 2] = (u_char)((x[i] >> 40) & 0xff);
		b[j + 1] = (u_char)((x[i] >> 48) & 0xff);
		b[j + 0] = (u_char)((x[i] >> 56) & 0xff);
		i++;
		j += 8;
	}
}

void		sha512_final(t_ctx *ctx, u_char digest[64])
{
	uint		i;
	uint64_t	l;

	i = ctx->buf_len;
	ctx->buf[i] = 0x80;
	ft_memset(&(ctx->buf[i + 1]), 0, (i < 112 ? 112 : 128) - i - 1);
	if (i >= 112)
	{
		sha512_transform(ctx, ctx->buf);
		ft_memset(ctx->buf, 0, 112);
	}
	l = ctx->len_lo + i * 8;
	if (l < ctx->len_lo)
		ctx->len_hi++;
	ctx->len_lo = l;
	i = 0;
	while (i < 8)
	{
		ctx->buf[127 - i] = (u_char)((ctx->len_lo >> (i * 8)) & 0xff);
		ctx->buf[119 - i] = (u_char)((ctx->len_hi >> (i * 8)) & 0xff);
		i++;
	}
	sha512_transform(ctx, ctx->buf);
	sha512_encode(digest, ctx->state, 64);
	ft_memset(ctx, 0, sizeof(*ctx));
}
