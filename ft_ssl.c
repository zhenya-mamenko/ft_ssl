/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:15:38 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/20 12:41:56 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		main(int ac, char **av)
{
	t_cmd	*cmd;

	if (ac == 1)
		print_usage();
	cmd = check_commands(av[1]);
	if (cmd == NULL)
	{
		error(ft_ssprintf("'%s' is an invalid command.\n", av[1]), 0, 1);
		print_standard_commands();
	}
}
