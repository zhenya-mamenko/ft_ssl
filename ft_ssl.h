/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:24:33 by emamenko          #+#    #+#             */
/*   Updated: 2019/04/17 16:10:27 by emamenko         ###   ########.fr       */
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
		"\x1b[14D %~u~string%~-u~\tPrint a checksum of the given string.",
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

static t_param		g_base64_params[] =
{
	{
		"i",
		"\x1b[14D %~u~input_file%~-u~\tRead input from input_file.",
		65536
	},
	{
		"o",
		"\x1b[14D %~u~output_file%~-u~\tWrite output to output_file.",
		131072
	},
	{
		"d",
		"Decode incoming Base64 stream into binary data.",
		4
	},
	{
		"e",
		"Encode incoming data into Base64 stream.",
		8
	}
};

static t_param		g_des_params[] =
{
	{
		"i",
		"\x1b[14D %~u~input_file%~-u~\tRead input from input_file.",
		65536
	},
	{
		"o",
		"\x1b[14D %~u~output_file%~-u~\tWrite output to output_file.",
		131072
	},
	{
		"d",
		"Decrypt the input data.",
		4
	},
	{
		"e",
		"Encrypt the input data (default).",
		8
	},
	{
		"a",
		"Perform base64 encoding/decoding.",
		16
	},
	{
		"k",
		"\x1b[14D %~u~key%~-u~\tKey to use, specified as a hexidecimal string.",
		262144
	},
	{
		"p",
		"\x1b[14D %~u~password%~-u~\tPassword source in ascii.",
		524288
	},
	{
		"s",
		"\x1b[14D %~u~salt%~-u~\tSalt to use, specified as a hexidecimal string.",
		524288
	},
	{
		"v",
		"\x1b[14D %~u~IV%~-u~\tIV to use, specified as a hexidecimal string.",
		1048576
	},
};

static int			g_cmd_cnt = 6;
static t_cmd		g_commands[] =
{
	{"md5", dgst, 4, g_md5_sha_params, 0, process_md5},
	{"sha256", dgst, 4, g_md5_sha_params, 0, process_sha256},
	{"sha384", dgst, 4, g_md5_sha_params, 0, process_sha384},
	{"sha512", dgst, 4, g_md5_sha_params, 0, process_sha512},
	{"base64", ciph, 4, g_base64_params, 0, process_base64},
	{"des", ciph, 9, g_des_params, 0, process_base64},
	{"des-cbc", ciph, 9, g_des_params, 0, process_base64},
	{"des-ecb", ciph, 9, g_des_params, 0, process_base64},
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
char				*base64_str(char *s, int mode);
char				*base64_file(char *fname, int mode);

#endif
