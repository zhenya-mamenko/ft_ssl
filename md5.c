/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:24:40 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/20 20:51:07 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char		*md5_file(char *s)
{
	return (ft_ssprintf("ho-ho-ho, file: %s!", s));
}

char		*md5_str(char *s)
{
	return (ft_ssprintf("ho-ho-ho: %s!", s));
}

static void	process_files(size_t f, int cnt, char **av)
{
	int			i;
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
				av[i], (md5 = md5_file(av[i])), f);
			ft_strdel(&md5);
		}
		else
			file_error("md5", av[i], errno);
		i++;
	}
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
