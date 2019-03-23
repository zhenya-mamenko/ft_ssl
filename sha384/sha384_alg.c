/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384_alg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:24:25 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/23 15:48:11 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "sha384.h"

void		sha384_init(t_ctx *ctx)
{
	ctx->len_hi = 0LL;
	ctx->len_lo = 0LL;
	ctx->buf_len = 0;
	ft_memset(ctx->buf, 0, 128);
	ctx->state[0] = 0xcbbb9d5dc1059ed8ULL;
	ctx->state[1] = 0x629a292a367cd507ULL;
	ctx->state[2] = 0x9159015a3070dd17ULL;
	ctx->state[3] = 0x152fecd8f70e5939ULL;
	ctx->state[4] = 0x67332667ffc00b31ULL;
	ctx->state[5] = 0x8eb44a8768581511ULL;
	ctx->state[6] = 0xdb0c2e0d64f98fa7ULL;
	ctx->state[7] = 0x47b5481dbefa4fa4ULL;
}
