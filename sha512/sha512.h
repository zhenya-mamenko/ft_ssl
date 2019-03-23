/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 17:57:32 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/23 12:34:11 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_H
# define SHA512_H

# include <sys/types.h>

# define SHA512_TPL		"SHA512 (%s) = %s\n"
# define SHA512_TPL_R	"%s %s\n"

# define ROR(a,b) (((uint64_t)(a) >> (b)) | ((a) << (64 - (uint64_t)(b))))

# define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
# define MA(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define E0(x) (ROR(x, 28) ^ ROR(x, 34) ^ ROR(x, 39))
# define E1(x) (ROR(x, 14) ^ ROR(x, 18) ^ ROR(x, 41))
# define SI0(x) (ROR(x, 1) ^ ROR(x, 8) ^ ((x) >> 7))
# define SI1(x) (ROR(x, 19) ^ ROR(x, 61) ^ ((x) >> 6))

static const uint64_t g_k[80] = {
	0x428a2f98d728ae22LL, 0x7137449123ef65cdLL,
	0xb5c0fbcfec4d3b2fLL, 0xe9b5dba58189dbbcLL,
	0x3956c25bf348b538LL, 0x59f111f1b605d019LL,
	0x923f82a4af194f9bLL, 0xab1c5ed5da6d8118LL,
	0xd807aa98a3030242LL, 0x12835b0145706fbeLL,
	0x243185be4ee4b28cLL, 0x550c7dc3d5ffb4e2LL,
	0x72be5d74f27b896fLL, 0x80deb1fe3b1696b1LL,
	0x9bdc06a725c71235LL, 0xc19bf174cf692694LL,
	0xe49b69c19ef14ad2LL, 0xefbe4786384f25e3LL,
	0x0fc19dc68b8cd5b5LL, 0x240ca1cc77ac9c65LL,
	0x2de92c6f592b0275LL, 0x4a7484aa6ea6e483LL,
	0x5cb0a9dcbd41fbd4LL, 0x76f988da831153b5LL,
	0x983e5152ee66dfabLL, 0xa831c66d2db43210LL,
	0xb00327c898fb213fLL, 0xbf597fc7beef0ee4LL,
	0xc6e00bf33da88fc2LL, 0xd5a79147930aa725LL,
	0x06ca6351e003826fLL, 0x142929670a0e6e70LL,
	0x27b70a8546d22ffcLL, 0x2e1b21385c26c926LL,
	0x4d2c6dfc5ac42aedLL, 0x53380d139d95b3dfLL,
	0x650a73548baf63deLL, 0x766a0abb3c77b2a8LL,
	0x81c2c92e47edaee6LL, 0x92722c851482353bLL,
	0xa2bfe8a14cf10364LL, 0xa81a664bbc423001LL,
	0xc24b8b70d0f89791LL, 0xc76c51a30654be30LL,
	0xd192e819d6ef5218LL, 0xd69906245565a910LL,
	0xf40e35855771202aLL, 0x106aa07032bbd1b8LL,
	0x19a4c116b8d2d0c8LL, 0x1e376c085141ab53LL,
	0x2748774cdf8eeb99LL, 0x34b0bcb5e19b48a8LL,
	0x391c0cb3c5c95a63LL, 0x4ed8aa4ae3418acbLL,
	0x5b9cca4f7763e373LL, 0x682e6ff3d6b2b8a3LL,
	0x748f82ee5defb2fcLL, 0x78a5636f43172f60LL,
	0x84c87814a1f0ab72LL, 0x8cc702081a6439ecLL,
	0x90befffa23631e28LL, 0xa4506cebde82bde9LL,
	0xbef9a3f7b2c67915LL, 0xc67178f2e372532bLL,
	0xca273eceea26619cLL, 0xd186b8c721c0c207LL,
	0xeada7dd6cde0eb1eLL, 0xf57d4f7fee6ed178LL,
	0x06f067aa72176fbaLL, 0x0a637dc5a2c898a6LL,
	0x113f9804bef90daeLL, 0x1b710b35131c471bLL,
	0x28db77f523047d84LL, 0x32caab7b40c72493LL,
	0x3c9ebe0a15c9bebcLL, 0x431d67c49c100d4cLL,
	0x4cc5d4becb3e42b6LL, 0x597f299cfc657e2aLL,
	0x5fcb6fab3ad6faecLL, 0x6c44198c4a475817LL
};

typedef struct			s_ctx
{
	uint64_t			state[8];
	unsigned char		buf[128];
	uint				buf_len;
	uint64_t			len_lo;
	uint64_t			len_hi;
}						t_ctx;

void					sha512_init(t_ctx *ctx);
void					sha512_update(t_ctx *ctx, u_char *buf, uint len);
void					sha512_final(t_ctx *ctx, u_char digest[64]);
void					sha512_transform(t_ctx *ctx, u_char b[128]);

#endif
