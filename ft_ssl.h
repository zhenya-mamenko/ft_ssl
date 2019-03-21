/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:24:33 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/21 12:08:05 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/errno.h>
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

typedef void		(*t_fn)(size_t, int, char **);

typedef struct		s_cmd
{
	char			*command;
	t_ct			type;
	int				param_count;
	t_param			*params;
	t_fn			fn;
}					t_cmd;

static int			g_cmd_count = 2;

static t_param		g_md5_sha_params[] =
{
	{
		"-p",
		"Echo stdin to stdout and append the checksum to stdout.",
		1024
	},
	{
		"-q",
		"Quiet mode - only the checksum is printed out. "\
		"Overrides the -r option.",
		4
	},
	{
		"-r",
		"Reverses the format of the output.  Does nothing when combined "\
		"with the -p option.",
		8
	},
	{
		"-s",
		"\x1b[14D %~u~string%~-u~\tPrint a checksum of the given string.",
		65536
	}
};

static t_cmd		g_commands[] =
{
	{"md5", dgst, 4, g_md5_sha_params, process_md5},
	{"sha256", dgst, 4, g_md5_sha_params, NULL}
};

void				error(char *message, int and_exit, int and_free);
void				file_error(char *command, char *file_name, int err);
void				print_usage(void);
void				print_standard_commands(void);
void				print_options_for_command(t_cmd *cmd);
void				print_hash(char *template, char *str, char *hash, size_t f);
t_cmd				*check_commands(char *command);
size_t				check_params(t_cmd *cmd, int *ac, char **av);
char				*read_stdin(void);
void				process_md5(size_t f, int cnt, char **av);
char				*md5_str(char *s);
char				*md5_file(char *s, int fd);

#endif
