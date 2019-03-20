/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 12:29:13 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/20 12:34:15 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	error(char *message, int and_exit, int and_free)
{
	ft_printf("%s: Error: %s", NAME, message);
	if (and_free == 1)
		free(message);
	if (and_exit == 1)
		exit(2);
}
