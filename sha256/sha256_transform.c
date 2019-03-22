/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 19:17:44 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/21 23:14:40 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "sha256.h"

static void	sha256_decode(u_int *x, u_char *b)
{
	u_int	i;
	u_int	j;

	i = 0;
	j = 0;
	while (j < 64)
	{
		x[i] = ((u_int)b[j + 3]) | (((u_int)b[j + 2]) << 8) |
			(((u_int)b[j + 1]) << 16) | (((u_int)b[j + 0]) << 24);
		i++;
		j += 4;
	}
	i = 15;
	while (++i < 64)
		x[i] = SI1(x[i - 2]) + x[i - 7] + SI0(x[i - 15]) + x[i - 16];
}

void		sha256_transform(t_ctx *ctx, u_char b[64])
{
	u_int	s[8];
	u_int	t[3];
	u_int	x[64];

	sha256_decode(x, b);
	t[0] = -1;
	while (++t[0] < 8)
		s[t[0]] = ctx->state[t[0]];
	t[0] = -1;
	while (++t[0] < 64)
	{
		t[1] = s[7] + E1(s[4]) + CH(s[4], s[5], s[6]) + g_k[t[0]] + x[t[0]];
		t[2] = E0(s[0]) + MA(s[0], s[1], s[2]);
		s[7] = s[6];
		s[6] = s[5];
		s[5] = s[4];
		s[4] = s[3] + t[1];
		s[3] = s[2];
		s[2] = s[1];
		s[1] = s[0];
		s[0] = t[1] + t[2];
	}
	t[0] = -1;
	while (++t[0] < 8)
		ctx->state[t[0]] += s[t[0]];
}
