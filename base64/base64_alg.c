/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_alg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:24:08 by emamenko          #+#    #+#             */
/*   Updated: 2019/04/15 11:10:51 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "base64.h"

static void		encode_triplet(unsigned char *in, unsigned char *out, int l)
{
	out[0] = base[in[0] >> 2];
	out[1] = base[((in[0] & 0x03) << 4) | (l > 1 ? in[1] >> 4 : 0)];
	out[2] = l > 1 ? base[((in[1] & 15) << 2) | ((in[2] & 192) >> 6)] : '=';
	out[3] = l > 2 ? base[in[2] & 63] : '=';
}

unsigned char	*base64_encode(unsigned char *b)
{
	unsigned char	*o;
	int				l;
	size_t			i;
	int				k;

	if ((l = ft_strlen((char *)b)) == 0)
		return ((unsigned char *)ft_strnew(0));
	l = ((l / 3) + (l % 3 != 0 ? 1 : 0)) * 4 + 1;
	if ((o = malloc(l)) == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (i < ft_strlen((char *)b))
	{
		l = ft_strlen((char *)b) - i;
		encode_triplet(b + i, o + k, l > 3 ? 3 : l);
		k += 4;
		i += 3;
	}
	o[k] = '\0';
	return (o);
}

static void		decode_quartet(unsigned char *in, unsigned char *out)
{
	out[0] = in[0] << 2 | in[1] >> 4;
	out[1] = (in[1] << 4) | (in[2] >> 2);
	out[2] = (in[2] << 6) | in[3];
}

unsigned char	*base64_decode(unsigned char *b)
{
	unsigned char	*o;
	size_t			i;
	int				k;
	int				j;
	unsigned char	in[4];

	k = ft_strlen((char *)b) / 4 * 3;
	if (k == 0 || (o = (unsigned char *)ft_strnew(k)) == NULL)
		return (NULL);
	i = 0;
	k = -3;
	while (i < ft_strlen((char *)b) && ((k += 3) >= 0))
	{
		ft_memset(in, 0, 4);
		j = 0;
		while (i < ft_strlen((char *)b) && j < 4)
		{
			if (b[i] > 42 && b[i] < 123)
				in[j++] = (b[i] == '=' ? 0 : ft_strchri(base, b[i]));
			i++;
		}
		if (j == 4)
			decode_quartet(in, o + k);
	}
	return (o);
}
