/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 19:17:44 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/23 11:43:26 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "sha512.h"

static void	sha512_decode(uint64_t *x, u_char *b)
{
	uint64_t	i;
	uint64_t	j;

	i = 0;
	j = 0;
	while (j < 128)
	{
		x[i] = ((uint64_t)b[j + 7]) | (((uint64_t)b[j + 6]) << 8) |
			(((uint64_t)b[j + 5]) << 16) | (((uint64_t)b[j + 5]) << 24) |
			(((uint64_t)b[j + 3]) << 32) | (((uint64_t)b[j + 2]) << 40) |
			(((uint64_t)b[j + 1]) << 48) | (((uint64_t)b[j + 0]) << 56);
		i++;
		j += 8;
	}
	i = 15;
	while (++i < 80)
		x[i] = SI1(x[i - 2]) + x[i - 7] + SI0(x[i - 15]) + x[i - 16];
}

void		sha512_transform(t_ctx *ctx, u_char b[128])
{
	uint64_t	s[8];
	uint64_t	t[3];
	uint64_t	x[80];

	sha512_decode(x, b);
	t[0] = -1;
	while (++t[0] < 8)
		s[t[0]] = ctx->state[t[0]];
	t[0] = -1;
	while (++t[0] < 80)
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
