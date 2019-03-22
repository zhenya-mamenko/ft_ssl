/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_alg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 21:33:03 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/21 16:14:18 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "md5.h"

void		md5_init(t_ctx *ctx)
{
	ctx->state[0] = 0x67452301;
	ctx->state[1] = 0xefcdab89;
	ctx->state[2] = 0x98badcfe;
	ctx->state[3] = 0x10325476;
	ctx->count[0] = 0;
	ctx->count[1] = 0;
	ft_memset(ctx->buf, 0, 64);
}

void		md5_update(t_ctx *ctx, u_char *buf, u_int len)
{
	u_int	i;
	u_int	index;
	u_int	p_len;

	index = (u_int)((ctx->count[0] >> 3) & 0x3f);
	if ((ctx->count[0] += ((u_int)len << 3)) < ((u_int)len << 3))
		ctx->count[1]++;
	ctx->count[1] += ((u_int)len >> 29);
	p_len = 64 - index;
	if (len >= p_len)
	{
		ft_memcpy(&ctx->buf[index], buf, p_len);
		md5_transform(ctx, ctx->buf);
		i = p_len;
		while (i + 63 < len)
		{
			md5_transform(ctx, &buf[i]);
			i += 64;
		}
		index = 0;
	}
	else
		i = 0;
	ft_memcpy(&ctx->buf[index], &buf[i], len - i);
}

static void	md5_encode(u_char *b, u_int *x, u_int len)
{
	u_int	i;
	u_int	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		b[j] = (u_char)(x[i] & 0xff);
		b[j + 1] = (u_char)((x[i] >> 8) & 0xff);
		b[j + 2] = (u_char)((x[i] >> 16) & 0xff);
		b[j + 3] = (u_char)((x[i] >> 24) & 0xff);
		i++;
		j += 4;
	}
}

void		md5_final(t_ctx *ctx, u_char digest[16])
{
	u_char	bits[8];
	u_int	index;
	u_int	p_len;
	u_char	pad[64];

	ft_memset(pad, 0, 64);
	ft_memset(bits, 0, 8);
	md5_encode(bits, ctx->count, 8);
	pad[0] = 0x80;
	index = (unsigned int)((ctx->count[0] >> 3) & 0x3f);
	p_len = (index < 56) ? (56 - index) : (120 - index);
	md5_update(ctx, pad, p_len);
	md5_update(ctx, bits, 8);
	md5_encode(digest, ctx->state, 16);
	ft_memset(ctx, 0, sizeof(*ctx));
}

void		md5_decode(u_int *x, u_char *b, u_int len)
{
	u_int	i;
	u_int	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		x[i] = ((u_int)b[j]) | (((u_int)b[j + 1]) << 8) |
			(((u_int)b[j + 2]) << 16) | (((u_int)b[j + 3]) << 24);
		i++;
		j += 4;
	}
}
