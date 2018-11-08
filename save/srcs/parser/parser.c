/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 13:29:19 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 17:49:52 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

/*
** il me faut un char ** qui contien tous les cmd a exe dans le bonne ordre.
**
** token: pour le moemnt on a [||], [&&], [>>], [<<], [>], [<], [|], [;], [ ].
** il me manque: [n>], [>&n], [>& file_name], [n>>], [>|], [n>&n], [$>]
**
** ps: n = un monbre.
*/

static void		ft_memset_lchar(t_lchar *cmd, int clean, int len)
{
	int		x;

	x = 0;
	while (x < len)
	{
		cmd[x].type = clean;
		x++;
	}
}

static void		print_t_lchar(t_lchar *cmd)
{
	int		a;

	a = 0;
	while (cmd[a].c != '\0')
	{
		ft_printf("cmd = [%d], [%c], [%s]\n", a, cmd[a].c,
				ft_print_type(cmd[a].type));
		a++;
	}
}

int				parser(t_lchar *cmd, int len, t_history *history)
{
	t_exec			c;
	t_creat_tree	a;
	t_len_exec		len_exec;

	ft_memset_lchar(cmd, 0, len);
	ft_memset(&c, 0, sizeof(t_exec));
	ft_memset(&len_exec, 0, sizeof(t_len_exec));
	define_lchar(cmd);
	creat_t_len_exec(cmd, &len_exec);
	if (malloc_t_exec(cmd, &c) == 1)
		return (1);
	print_t_lchar(cmd);
	ft_memset(&a, 0, sizeof(t_creat_tree));
	a.redir = -1;
	creat_tree(&a, &c, cmd, history);
	if (reset_termcaps() == 1)
		return (1);
	print_tree(&c);
	exec_tree(&c);
	return (0);
}
