/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:24:40 by emamenko          #+#    #+#             */
/*   Updated: 2019/04/15 13:11:42 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "base64.h"

extern t_strings	g_ss[100];
extern int			g_ss_cnt;

static void	output(char *fname, char *base64, size_t f)
{
	extern int	errno;
	int			fd;

	if (fname == NULL || (ft_strcmp(fname, "-") == 0))
	{
		ft_printf("%s%s", base64, (f & 1024) ? "\n" : "");
	}
	else
	{
		if ((fd = open(fname, O_RDWR | O_CREAT, 0666)) == -1)
		{
			file_error("base64", fname, errno);
			ft_strdel(&base64);
			exit(errno);
		}
		write(fd, base64, ft_strlen(base64));
		close(fd);
	}
	ft_strdel(&base64);
}

char		*base64_file(char *fname, int mode)
{
	int			i[2];
	char		*base64;
	char		*tmp;
	char		buf[1000];
	extern int	errno;

	if ((i[0] = open(fname, O_RDONLY)) == -1)
	{
		file_error("base64", fname, errno);
		exit(errno);
	}
	base64 = NULL;
	while ((i[1] = read(i[0], buf, 999)) > 0)
	{
		buf[i[1]] = '\0';
		ft_strsetdel(&base64, ft_strjoin(base64, buf));
	}
	close(i[0]);
	tmp = (char *)(mode == 2 ? base64_decode((unsigned char *)base64) :
		base64_encode((unsigned char *)base64));
	ft_strdel(&base64);
	return (tmp);
}

char		*base64_str(char *s, int mode)
{
	char	*base64;

	base64 = (char *)(mode == 2 ? base64_decode((unsigned char *)s) :
		base64_encode((unsigned char *)s));
	return (base64);
}

void		process_base64(size_t f, int cnt, char **av)
{
	char	*s;
	char	*base64;
	char	*out;
	int		i;

	(void)av;
	s = NULL;
	base64 = NULL;
	out = NULL;
	i = -1;
	while (++i < g_ss_cnt)
		if ((g_ss[i].f & 65536) && base64 == NULL)
		{
			if (ft_strcmp(g_ss[i].s, "-") == 0)
				f |= 1024;
			else
				base64 = base64_file(g_ss[i].s, g_ss[i].f & 4 ? 2 : 1);
		}
		else if ((g_ss[i].f & 131072) && out == NULL)
			out = g_ss[i].s;
	if ((f & 1024) || base64 == NULL || cnt == 0)
		s = read_stdin();
	base64 = base64 == NULL ? base64_str(s, (f >> 1) & 2) : base64;
	ft_strdel(&s);
	output(out, base64, f | (base64 == NULL ? 1024 : 0));
}
