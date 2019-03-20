/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:49:55 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/20 15:08:40 by emamenko         ###   ########.fr       */
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

size_t	check_params(t_cmd *cmd, int *ac, char **av)
{
	int		i;
	int		j;
	size_t	f;

	i = 0;
	f = 0;
	while (i < *ac)
	{
		if (av[i][0] != '-')
			return (f);
		j = -1;
		while (++j < cmd->param_count)
			if (ft_strcmp(av[i], cmd->params[j].param) == 0)
			{
				f |= cmd->params[j].flag;
				break ;
			}
		if (j == cmd->param_count)
			return (1);
		i++;
	}
	return (f);
}
