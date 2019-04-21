/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:49:55 by emamenko          #+#    #+#             */
/*   Updated: 2019/04/15 19:12:39 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

extern t_strings	g_ss[100];
extern int			g_ss_cnt;
extern int			g_exit_value;

static void	check_next_arg(t_cmd *cmd, char *param, int i, int ac)
{
	if (i == ac)
	{
		error(ft_ssprintf("%s: '%s' option requires an argument.\n",
			cmd->command, param), 0, 1);
		print_options_for_command(cmd);
	}
}

static int	check_exact_params(t_cmd *cmd, char **av, int *i, int ac)
{
	int		j;

	j = -1;
	while (++j < cmd->param_count)
		if (ft_strcmp(&av[*i][1], cmd->params[j].param) == 0)
			break ;
	if (j == cmd->param_count)
		return (-1);
	if (cmd->params[j].flag & 0xffff0000)
	{
		check_next_arg(cmd, cmd->params[j].param, *i + 1, ac);
		g_ss[g_ss_cnt++].s = av[++(*i)];
	}
	return (cmd->params[j].flag);
}

static int	error_in_pparams(t_cmd *cmd, char *p)
{
	error(ft_ssprintf("%s: illegal option(s) -- %s.\n", cmd->command, p), 0, 1);
	print_options_for_command(cmd);
	return (-1);
}

static int	check_partial_params(t_cmd *cmd, char **av, int *i, int ac)
{
	int		j;
	size_t	k;
	int		f;
	char	*p;
	t_param	pm;

	f = 0;
	j = -1;
	p = ft_strsub(av[*i], 1, ft_strlen(av[*i]) - 1);
	while (++j < cmd->param_count)
		if ((k = ft_strstri(p, cmd->params[j].param)) != -1)
		{
			if ((pm = cmd->params[j]).flag & 0xffff0000)
			{
				g_ss[g_ss_cnt++].s = (k == (ft_strlen(p) - 1)) ? av[++(*i)] :
					&av[(*i)][ft_strstri(av[(*i)], pm.param) + 1];
				if (k == (ft_strlen(p) - 1))
					check_next_arg(cmd, pm.param, *i, ac);
				else
					ft_strsetdel(&p, ft_strsub(p, 0, k));
			}
			ft_strcpy(p + k, p + k + ft_strlen(pm.param));
			f |= pm.flag;
		}
	return (ft_strlen(p) == 0 ? f : error_in_pparams(cmd, p));
}

size_t		check_params(t_cmd *cmd, int *ac, char **av)
{
	int		i;
	int		j;
	size_t	f;

	f = 0;
	i = -1;
	while (++i < *ac)
	{
		if (av[i][0] != '-')
			break ;
		if (cmd->exact_match_params == 1)
		{
			if ((j = check_exact_params(cmd, av, &i, *ac)) == -1)
				return (1);
		}
		else if ((j = check_partial_params(cmd, av, &i, *ac)) == -1)
			return (1);
		if ((f = (f & 65535) | j) & 0xffff0000)
			g_ss[g_ss_cnt - 1].f = f;
	}
	*ac -= i;
	return (f);
}
