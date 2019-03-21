/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:28:41 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/21 11:10:22 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include <stdlib.h>

# define MD5_TEMPLATE	"MD5 (%s) = %s\n"
# define MD5_TEMPLATE_R	"%s %s\n"

# define S11 7
# define S12 12
# define S13 17
# define S14 22
# define S21 5
# define S22 9
# define S23 14
# define S24 20
# define S31 4
# define S32 11
# define S33 16
# define S34 23
# define S41 6
# define S42 10
# define S43 15
# define S44 21

# define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
# define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
# define H(x, y, z) ((x) ^ (y) ^ (z))
# define I(x, y, z) ((y) ^ ((x) | (~z)))

# define ROL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

# define AS(a,s,b) (a)=ROL((a),(s));(a)+=(b);
# define FF(a,b,c,d,x,s,ac){(a)+=F((b),(c),(d))+(x)+(size_t)(ac);AS(a,s,b)}
# define GG(a,b,c,d,x,s,ac){(a)+=G((b),(c),(d))+(x)+(size_t)(ac);AS(a,s,b)}
# define HH(a,b,c,d,x,s,ac){(a)+=H((b),(c),(d))+(x)+(size_t)(ac);AS(a,s,b)}
# define II(a,b,c,d,x,s,ac){(a)+=I((b),(c),(d))+(x)+(size_t)(ac);AS(a,s,b)}

void	process_md5(size_t f, int cnt, char **av);

#endif
