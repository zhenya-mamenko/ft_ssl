/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_alg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:24:08 by emamenko          #+#    #+#             */
/*   Updated: 2019/04/14 14:13:48 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "base64.h"

static void		encode_triplet(unsigned char *in, unsigned char *out, int l)
{
	out[0] = base[in[0] >> 2];
	out[1] = base[((in[0] & 0x03) << 4) | (in[1] >> 4)];
	out[2] = l > 1 ? base[((in[1] & 15) << 2) | ((in[2] & 192) >> 4)] : "=";
	out[3] = l > 2 ? base[in[2] & 63] : "=";
}

unsigned char	*base64_encode(unsigned char *b)
{
	unsigned char	*o;
	int				l;
	int				i;
	int				k;

	if ((l = ft_strlen(b)) == 0)
		return (ft_strnew(""));
	l = ((l / 3) + (l % 3 != 0 ? 1 : 0)) * 4 + 1;
	if ((o = malloc(sizeof(char) * l)) == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (i < ft_strlen(b))
	{
		encode_triplet(b + i, o + k, (ft_strlen(b) - i * 3) % 3);
		k += 4;
		i += 3;
	}
	o[k] = '\0';
}

static void		decode_quartet(unsigned char *in, unsigned char *out)
{
	out[0] = in[0] << 2 | in[1] >> 4;
	out[1] = (in[1] << 4) | (in[2] != '=' ? (in[2] >> 4) : 0);
	out[2] = (in[2] != '=' ? (in[2] << 6) : 0) | (in[3] != '=' ? in[3] : 0);
}

unsigned char	*base64_decode(unsigned char *b)
{
	unsigned char	*o;
	int				i;
	int				k;

	if (ft_strlen(b) == 0)
		return (ft_strnew(""));
	if ((o = malloc(sizeof(char) * (ft_strlen(b) / 4 * 3 + 1))) == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (i < ft_strlen(b))
	{
		decode_quartet(b + i, o + k);
		k += 3;
		i += 4;
	}
	o[k] = '\0';
}
