/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:24:40 by emamenko          #+#    #+#             */
/*   Updated: 2019/04/20 21:26:09 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "sha512.h"

extern t_strings	g_ss[100];
extern int			g_ss_cnt;

static void	process_files(size_t f, u_int cnt, char **av)
{
	u_int		i;
	int			fd;
	char		*sha512;
	extern int	errno;

	i = 0;
	while (i < cnt)
	{
		fd = open(av[i], O_RDONLY);
		if (fd != -1)
		{
			print_hash((f & 8) && !(f & 4) ? SHA512_R : SHA512_TPL,
				av[i], (sha512 = sha512_file(fd)), f);
			ft_strdel(&sha512);
			close(fd);
		}
		else
			file_error("sha512", av[i], errno);
		i++;
	}
}

static char	*sha512_digest(u_char digest[64])
{
	u_int	i;
	char	*result;
	char	*s;

	result = ft_strnew(0);
	i = 0;
	while (i < 64)
	{
		s = ft_ssprintf("%02x", digest[i]);
		ft_strsetdel(&result, ft_strjoin(result, s));
		ft_strdel(&s);
		i++;
	}
	return (result);
}

char		*sha512_file(int fd)
{
	u_char	digest[64];
	u_char	buf[1024];
	t_ctx	ctx;
	int		len;

	sha512_init(&ctx);
	while ((len = read(fd, buf, 1024)) > 0)
		sha512_update(&ctx, buf, len);
	sha512_final(&ctx, digest);
	return (sha512_digest(digest));
}

char		*sha512_str(char *s)
{
	u_char	digest[64];
	t_ctx	ctx;

	sha512_init(&ctx);
	sha512_update(&ctx, (u_char *)s, ft_strlen(s));
	sha512_final(&ctx, digest);
	return (sha512_digest(digest));
}

void		process_sha512(size_t f, int cnt, char **av)
{
	char	*s;
	char	*sha512;
	int		i;

	s = NULL;
	if ((f & 1024) || (cnt == 0 && g_ss_cnt == 0))
		s = read_stdin();
	if (s && ft_strlen(s) != 0)
	{
		sha512 = sha512_str(s);
		print_hash((f & 1024) ? "%s%s\n" : "%s\n", s, sha512,
			(f & 1024) ? 0 : 4);
		ft_strdel(&s);
		ft_strdel(&sha512);
	}
	i = -1;
	while (++i < g_ss_cnt)
	{
		s = ft_ssprintf("\"%s\"", g_ss[i].s);
		print_hash((g_ss[i].f & 8) && !(g_ss[i].f & 4) ? SHA512_R : SHA512_TPL,
			s, (sha512 = sha512_str(g_ss[i].s)), g_ss[i].f);
		ft_strdel(&sha512);
		ft_strdel(&s);
	}
	process_files(f, cnt, av);
}
