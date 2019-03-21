/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:24:40 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/20 20:18:28 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char		*md5_file(char *s)
{
	return (ft_strdup("ho-ho-ho!"));
}

char		*md5_str(char *s)
{
	return (ft_strdup("ho-ho-ho FILE!"));
}

static void	process_files(size_t f, int cnt, char **av)
{
	size_t	i;
	char	*md5;

	i = 0;
	while (i < cnt)
	{
		print_hash((f & 8) && !(f & 4) ? MD5_TEMPLATE_R : MD5_TEMPLATE,
			av[i], (md5 = md5_file(av[i])), f);
		ft_strdel(md5);
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
		ft_strdel(stdin);
		ft_strdel(md5);
	}
	if ((f & 65536) && cnt--)
	{
		print_hash((f & 8) && !(f & 4) ? MD5_TEMPLATE_R : MD5_TEMPLATE,
			av, (md5 = md5_str(av++)), f);
		ft_strdel(md5);
	}
	process_files(f, cnt, av);
}
