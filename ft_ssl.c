/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:15:38 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/20 15:08:50 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static size_t	process_params(t_cmd *cmd, int *cnt, char **av)
{
	size_t	result;

	result = check_params(cmd, cnt, av);
	if (result == 1)
	{
		error(ft_ssprintf("'%s' is an illegal option.\n", av[*cnt - 1]), 0, 1);
		print_options_for_command(cmd);
	}
	return (result);
}

int				main(int ac, char **av)
{
	t_cmd	*cmd;
	int		cnt;
	size_t	f;

	if (ac == 1)
		print_usage();
	cmd = check_commands(av[1]);
	if (cmd == NULL)
	{
		error(ft_ssprintf("'%s' is an invalid command.\n", av[1]), 0, 1);
		print_standard_commands();
	}
	cnt = ac - 2;
	if (cnt != 0)
		f = process_params(cmd, &cnt, av + 2);
}
