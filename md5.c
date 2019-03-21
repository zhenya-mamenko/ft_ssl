/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:24:40 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/20 19:56:06 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*md5_str(char *s)
{
	return (ft_strdup("ho-ho-ho!"));
}

void	process_md5(size_t f, int cnt, char **av)
{
	char	*stdin;
	char	*md5;
	int		i;

	stdin = NULL;
	if ((f & 1024) || cnt == 0)
		stdin = read_stdin();
	if (stdin && ft_strlen(stdin) != 0)
	{
		if (f & 1024)
			ft_printf("%s\n", stdin);
		md5 = md5_str(stdin);
		ft_printf("%s\n", md5);
		ft_strdel(stdin);
		ft_strdel(md5);
	}
	i = 0;
	if (f & 65536)
	{

	}
}
