/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:23:08 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/20 12:45:55 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		print_usage(void)
{
	ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	exit(1);
}

static void	print_commands_by_type(t_ct type)
{
	int		i;

	i = 0;
	while (i < g_cmd_count)
	{
		if (g_commands[i].type == type)
			ft_printf("%s\n", g_commands[i].command);
		i++;
	}
}

void		print_standard_commands(void)
{
	ft_printf("\nStandard commands:\n");
	ft_printf("\nMessage Digest commands:\n");
	print_commands_by_type(dgst);
	ft_printf("\nCipher commands:\n");
	print_commands_by_type(ciph);
	ft_printf("\n");
	exit(1);
}
