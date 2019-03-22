/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:24:40 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/21 19:49:31 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "sha256.h"

static void	process_files(size_t f, u_int cnt, char **av)
{
	u_int		i;
	int			fd;
	char		*sha256;
	extern int	errno;

	i = 0;
	while (i < cnt)
	{
		fd = open(av[i], O_RDONLY);
		if (fd != -1)
		{
			print_hash((f & 8) && !(f & 4) ? SHA256_TPL_R : SHA256_TPL,
				av[i], (sha256 = sha256_file(fd)), f);
			ft_strdel(&sha256);
			close(fd);
		}
		else
			file_error("sha256", av[i], errno);
		i++;
	}
}

static char	*sha256_digest(u_char digest[32])
{
	u_int	i;
	char	*result;
	char	*s;

	result = ft_strnew(0);
	i = 0;
	while (i < 32)
	{
		s = ft_ssprintf("%02x", digest[i]);
		ft_strsetdel(&result, ft_strjoin(result, s));
		ft_strdel(&s);
		i++;
	}
	return (result);
}

char		*sha256_file(int fd)
{
	u_char	digest[32];
	u_char	buf[1024];
	t_ctx	ctx;
	int		len;

	sha256_init(&ctx);
	while ((len = read(fd, buf, 1024)) > 0)
		sha256_update(&ctx, buf, len);
	sha256_final(&ctx, digest);
	return (sha256_digest(digest));
}

char		*sha256_str(char *s)
{
	u_char	digest[32];
	t_ctx	ctx;

	sha256_init(&ctx);
	sha256_update(&ctx, (u_char *)s, ft_strlen(s));
	sha256_final(&ctx, digest);
	return (sha256_digest(digest));
}

void		process_sha256(size_t f, int cnt, char **av)
{
	char	*s;
	char	*sha256;

	s = NULL;
	if ((f & 1024) || cnt == 0)
		s = read_stdin();
	if (s && ft_strlen(s) != 0)
	{
		sha256 = sha256_str(s);
		print_hash((f & 1024) ? "%s%s\n" : "%s\n", s, sha256,
			(f & 1024) ? 0 : 4);
		ft_strdel(&s);
		ft_strdel(&sha256);
	}
	if ((f & 65536) && cnt--)
	{
		s = ft_ssprintf("\"%s\"", *av);
		print_hash((f & 8) && !(f & 4) ? SHA256_TPL_R : SHA256_TPL,
			s, (sha256 = sha256_str(*av)), f);
		ft_strdel(&sha256);
		ft_strdel(&s);
		av++;
	}
	process_files(f, cnt, av);
}
