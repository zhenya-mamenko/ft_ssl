/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:49:55 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/20 12:40:39 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_cmd	*check_commands(char *command)
{
	int		i;

	i = 0;
	while (i < g_cmd_count)
	{
		if (ft_strcmp(command, g_commands[i].command) == 0)
			return (&g_commands[i]);
		i++;
	}
	return (NULL);
}
