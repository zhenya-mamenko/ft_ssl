/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:24:40 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/21 13:35:06 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
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
				av[i], (md5 = md5_file(av[i], fd)), f);
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
	u_char	i;
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

char		*md5_file(char *s, int fd)
{
	u_char	digest[16];
	u_char	buf[1024];
	t_ctx	ctx;
	int		len;

	md5_init(&ctx);
	while (len = read(fd, buf, 1024))
		md5_update(&ctx, buf, len);
	md5_final(&ctx, digest);
	return (md5_digest(digest));
}

char		*md5_str(char *s)
{
	u_char	digest[16];
	t_ctx	ctx;

	md5_init(&ctx);
	md5_update(&ctx, s, ft_strlen(s));
	md5_final(&ctx, digest);
	return (md5_digest(digest));
}

void		process_md5(size_t f, int cnt, char **av)
{
	char	*stdin;
	char	*md5;

	stdin = NULL;
	if ((f & 1024) || cnt == 0)
		stdin = read_stdin();
	if (stdin && ft_strlen(stdin) != 0)
	{
		if (f & 1024)
			ft_printf("%s\n", stdin);
		md5 = md5_str(stdin);
		print_hash("%s\n", stdin, md5, 0);
		ft_strdel(&stdin);
		ft_strdel(&md5);
	}
	if ((f & 65536) && cnt--)
	{
		stdin = ft_ssprintf("\"%s\"", *av);
		print_hash((f & 8) && !(f & 4) ? MD5_TEMPLATE_R : MD5_TEMPLATE,
			stdin, (md5 = md5_str(*av)), f);
		ft_strdel(&md5);
		ft_strdel(&stdin);
		av++;
	}
	process_files(f, cnt, av);
}
