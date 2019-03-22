/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_alg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:24:25 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/21 19:44:11 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "sha256.h"

void		sha256_init(t_ctx *ctx)
{
	ctx->buf_len = 0;
	ctx->bit_len = 0;
	ft_memset(ctx->buf, 0, 64);
	ctx->state[0] = 0x6a09e667;
	ctx->state[1] = 0xbb67ae85;
	ctx->state[2] = 0x3c6ef372;
	ctx->state[3] = 0xa54ff53a;
	ctx->state[4] = 0x510e527f;
	ctx->state[5] = 0x9b05688c;
	ctx->state[6] = 0x1f83d9ab;
	ctx->state[7] = 0x5be0cd19;
}

void		sha256_update(t_ctx *ctx, u_char *buf, u_int len)
{
	u_int i;

	i = 0;
	while (i < len)
	{
		ctx->buf[ctx->buf_len] = buf[i];
		ctx->buf_len++;
		if (ctx->buf_len == 64)
		{
			sha256_transform(ctx, ctx->buf);
			ctx->bit_len += 512;
			ctx->buf_len = 0;
		}
	}
}

static void	sha256_encode(u_char *b, u_int *x, u_int len)
{
	u_int	i;
	u_int	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		b[j + 3] = (u_char)(x[i] & 0xff);
		b[j + 2] = (u_char)((x[i] >> 8) & 0xff);
		b[j + 1] = (u_char)((x[i] >> 16) & 0xff);
		b[j] = (u_char)((x[i] >> 24) & 0xff);
		i++;
		j += 4;
	}
}

void		sha256_final(t_ctx *ctx, u_char digest[32])
{
	u_int i;

	i = ctx->buf_len;
	ctx->buf[i] = 0x80;
	ft_memset(&(ctx->buf[i]), 0, (i < 56 ? 56 : 64) - i - 1);
	if (i >= 56)
	{
		sha256_transform(ctx, ctx->buf);
		ft_memset(ctx->buf, 0, 56);
	}
	ctx->bit_len += i * 8;
	i = 0;
	while (i < 8)
	{
		ctx->buf[63 - i] = ctx->bit_len >> (i * 8);
		i++;
	}
	sha256_transform(ctx, ctx->buf);
	sha256_encode(digest, ctx->state, 32);
	ft_memset(ctx, 0, sizeof(*ctx));
}
