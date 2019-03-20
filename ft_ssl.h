/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:24:33 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/20 12:41:22 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft/libft.h"

# define NAME	"ft_ssl"

typedef enum	e_ct
{
	dgst,
	ciph
}				t_ct;

typedef struct	s_cmd
{
	char		*command;
	t_ct		type;
}				t_cmd;

static int		g_cmd_count = 2;
static t_cmd	g_commands[] =
{
	{"md5", dgst},
	{"sha256", dgst}
};

void			error(char *message, int and_exit, int and_free);
void			print_usage(void);
void			print_standard_commands(void);
t_cmd			*check_commands(char *command);

#endif
