/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 17:35:08 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/20 19:15:18 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*read_stdin(void)
{
	char	*line;
	char	*buf;

	buf = NULL;
	while (get_next_line(0, &line) > 0)
	{
		ft_strsetdel(&buf, ft_strjoin(buf, line));
		ft_strdel(&line);
		ft_strsetdel(&buf, ft_strjoin(buf, "\n"));
	}
	buf[ft_strlen(buf) - 1] = '\0';
	return (buf);
}
