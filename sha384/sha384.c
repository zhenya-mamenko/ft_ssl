/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:24:40 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/23 15:51:18 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "../sha512/sha512.h"
#include "sha384.h"

extern t_strings	g_ss[100];
extern int			g_ss_cnt;

static void	process_files(size_t f, u_int cnt, char **av)
{
	u_int		i;
	int			fd;
	char		*sha384;
	extern int	errno;

	i = 0;
	while (i < cnt)
	{
		fd = open(av[i], O_RDONLY);
		if (fd != -1)
		{
			print_hash((f & 8) && !(f & 4) ? SHA384_TPL_R : SHA384_TPL,
				av[i], (sha384 = sha384_file(fd)), f);
			ft_strdel(&sha384);
			close(fd);
		}
		else
			file_error("sha384", av[i], errno);
		i++;
	}
}

static char	*sha384_digest(u_char digest[64])
{
	u_int	i;
	char	*result;
	char	*s;

	result = ft_strnew(0);
	i = 0;
	while (i < 48)
	{
		s = ft_ssprintf("%02x", digest[i]);
		ft_strsetdel(&result, ft_strjoin(result, s));
		ft_strdel(&s);
		i++;
	}
	return (result);
}

char		*sha384_file(int fd)
{
	u_char	digest[64];
	u_char	buf[1024];
	t_ctx	ctx;
	int		len;

	sha384_init(&ctx);
	while ((len = read(fd, buf, 1024)) > 0)
		sha512_update(&ctx, buf, len);
	sha512_final(&ctx, digest);
	return (sha384_digest(digest));
}

char		*sha384_str(char *s)
{
	u_char	digest[64];
	t_ctx	ctx;

	sha384_init(&ctx);
	sha512_update(&ctx, (u_char *)s, ft_strlen(s));
	sha512_final(&ctx, digest);
	return (sha384_digest(digest));
}

void		process_sha384(size_t f, int cnt, char **av)
{
	char	*s;
	char	*sha384;
	int		i;

	s = NULL;
	if ((f & 1024) || (cnt == 0 && g_ss_cnt == 0))
		s = read_stdin();
	if (s && ft_strlen(s) != 0)
	{
		sha384 = sha384_str(s);
		print_hash((f & 1024) ? "%s%s\n" : "%s\n", s, sha384,
			(f & 1024) ? 0 : 4);
		ft_strdel(&s);
		ft_strdel(&sha384);
	}
	i = -1;
	while (++i < g_ss_cnt)
	{
		s = ft_ssprintf("\"%s\"", g_ss[i].s);
		print_hash((f & 8) && !(f & 4) ? SHA384_TPL_R : SHA384_TPL,
			s, (sha384 = sha384_str(g_ss[i].s)), f);
		ft_strdel(&sha384);
		ft_strdel(&s);
	}
	process_files(f, cnt, av);
}
