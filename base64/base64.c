/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:24:40 by emamenko          #+#    #+#             */
/*   Updated: 2019/04/14 14:41:43 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "base64.h"

extern t_strings	g_ss[100];
extern int			g_ss_cnt;

static void	process_files(size_t f, u_int cnt, char **av)
{
	u_int		i;
	int			fd;
	char		*base64;
	extern int	errno;

	i = 0;
	while (i < cnt)
	{
		fd = open(av[i], O_RDONLY);
		if (fd != -1)
		{
			ft_strdel(&base64);
			close(fd);
		}
		else
			file_error("base64", av[i], errno);
		i++;
	}
}

char		*base64_file(int fd, int mode)
{
	int		len;
	char	*base64;
	char	buf[999];

	while ((len = read(fd, buf, 999)) > 0)
		base64 = mode == 2 ? base64_decode((unsigned char)buf) :
		base64_encode((unsigned char)buf);
	return (base64);
}

char		*base64_str(char *s, int mode)
{
	char	*base64;

	base64 = mode == 2 ? base64_decode((unsigned char)s) :
		base64_encode((unsigned char)s);
	return (base64);
}

void		process_base64(size_t f, int cnt, char **av)
{
	char	*s;
	char	*base64;
	int		i;

	s = NULL;
	if ((f & 1024) || (cnt == 0 && g_ss_cnt == 0))
		s = read_stdin();
	if (s && ft_strlen(s) != 0)
	{
		base64 = base64_str(s, f & 4 ? 2 : 1);
		ft_strdel(&s);
		ft_strdel(&base64);
	}
	i = -1;
	while (++i < g_ss_cnt)
	{
		ft_strdel(&base64);
		ft_strdel(&s);
	}
	process_files(f, cnt, av);
}
