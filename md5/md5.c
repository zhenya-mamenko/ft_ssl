/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:24:40 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/21 17:13:51 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "md5.h"

static void	process_files(size_t f, u_int cnt, char **av)
{
	u_int		i;
	int			fd;
	char		*md5;
	extern int	errno;

	i = 0;
	while (i < cnt)
	{
		fd = open(av[i], O_RDONLY);
		if (fd != -1)
		{
			print_hash((f & 8) && !(f & 4) ? MD5_TEMPLATE_R : MD5_TEMPLATE,
				av[i], (md5 = md5_file(fd)), f);
			ft_strdel(&md5);
			close(fd);
		}
		else
			file_error("md5", av[i], errno);
		i++;
	}
}

static char	*md5_digest(u_char digest[16])
{
	u_int	i;
	char	*result;
	char	*s;

	result = ft_strnew(0);
	i = 0;
	while (i < 16)
	{
		s = ft_ssprintf("%02x", digest[i]);
		ft_strsetdel(&result, ft_strjoin(result, s));
		ft_strdel(&s);
		i++;
	}
	return (result);
}

char		*md5_file(int fd)
{
	u_char	digest[16];
	u_char	buf[1024];
	t_ctx	ctx;
	int		len;

	md5_init(&ctx);
	while ((len = read(fd, buf, 1024)) > 0)
		md5_update(&ctx, buf, len);
	md5_final(&ctx, digest);
	return (md5_digest(digest));
}

char		*md5_str(char *s)
{
	u_char	digest[16];
	t_ctx	ctx;

	md5_init(&ctx);
	md5_update(&ctx, (u_char *)s, ft_strlen(s));
	md5_final(&ctx, digest);
	return (md5_digest(digest));
}

void		process_md5(size_t f, int cnt, char **av)
{
	char	*s;
	char	*md5;

	s = NULL;
	if ((f & 1024) || cnt == 0)
		s = read_stdin();
	if (s && ft_strlen(s) != 0)
	{
		md5 = md5_str(s);
		print_hash((f & 1024) ? "%s%s\n" : "%s\n", s, md5, (f & 1024) ? 0 : 4);
		ft_strdel(&s);
		ft_strdel(&md5);
	}
	if ((f & 65536) && cnt--)
	{
		s = ft_ssprintf("\"%s\"", *av);
		print_hash((f & 8) && !(f & 4) ? MD5_TEMPLATE_R : MD5_TEMPLATE,
			s, (md5 = md5_str(*av)), f);
		ft_strdel(&md5);
		ft_strdel(&s);
		av++;
	}
	process_files(f, cnt, av);
}
