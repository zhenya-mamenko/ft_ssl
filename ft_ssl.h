/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:24:33 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/20 14:32:22 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft/libft.h"

# define NAME		"ft_ssl"
# define MAX_PARAM	10

typedef enum		e_ct
{
	dgst,
	ciph
}					t_ct;

typedef struct		s_param
{
	char			*param;
	char			*description;
	size_t			flag;
}					t_param;

typedef struct		s_cmd
{
	char			*command;
	t_ct			type;
	int				param_count;
	t_param			*params;
}					t_cmd;

static int			g_cmd_count = 2;

static t_param		g_md5_params[] =
{
	{
		"-p",
		"Echo stdin to stdout and append the checksum to stdout.",
		2
	},
	{
		"-q",
		"Quiet mode - only the checksum is printed out.  Overrides the -r option.",
		4
	},
	{
		"-r",
		"Reverses the format of the output.  Does nothing when combined with the -p option.",
		8
	},
	{
		"-s",
		"Print a checksum of the given %~u~string%~-u~.",
		16
	}
};

static t_cmd		g_commands[] =
{
	{"md5", dgst, 4, g_md5_params},
	{"sha256", dgst, 0, NULL}
};

void				error(char *message, int and_exit, int and_free);
void				print_usage(void);
void				print_standard_commands(void);
void				print_options_for_command(t_cmd *cmd);
t_cmd				*check_commands(char *command);
size_t				check_params(int *ac, char **av);

#endif
