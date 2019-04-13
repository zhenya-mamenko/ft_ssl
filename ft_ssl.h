/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:24:33 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/23 21:05:50 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/errno.h>
# include "libft/libft.h"
# include "processes.h"

# define NAME		"ft_ssl"
# define MAX_PARAM	10

typedef enum		e_ct
{
	dgst,
	ciph,
	std
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
	int				exact_match_params;
	t_fn			fn;
}					t_cmd;

typedef struct		s_strings
{
	size_t			f;
	char			*s;
}					t_strings;

static t_param		g_md5_sha_params[] =
{
	{
		"s",
		"\x1b[15D %~u~string%~-u~\tPrint a checksum of the given string.",
		65536
	},
	{
		"p",
		"Echo stdin to stdout and append the checksum to stdout.",
		1024
	},
	{
		"q",
		"Quiet mode - only the checksum is printed out. "\
		"Overrides the -r option.",
		4
	},
	{
		"r",
		"Reverses the format of the output.  Does nothing when combined "\
		"with the -p option.",
		8
	}
};

static int			g_cmd_cnt = 4;
static t_cmd		g_commands[] =
{
	{"md5", dgst, 4, g_md5_sha_params, 0, process_md5},
	{"sha256", dgst, 4, g_md5_sha_params, 0, process_sha256},
	{"sha384", dgst, 4, g_md5_sha_params, 0, process_sha384},
	{"sha512", dgst, 4, g_md5_sha_params, 0, process_sha512}
};

void				error(char *message, int and_exit, int and_free);
void				file_error(char *command, char *file_name, int err);
void				print_usage(void);
void				print_standard_commands(void);
void				print_options_for_command(t_cmd *cmd);
void				print_hash(char *template, char *str, char *hash, size_t f);
size_t				check_params(t_cmd *cmd, int *ac, char **av);
char				*read_stdin(void);
char				*md5_str(char *s);
char				*md5_file(int fd);
char				*sha256_str(char *s);
char				*sha256_file(int fd);
char				*sha384_str(char *s);
char				*sha384_file(int fd);
char				*sha512_str(char *s);
char				*sha512_file(int fd);

#endif
