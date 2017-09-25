/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 16:25:03 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/25 17:08:48 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static char	*ft_memcpy_char_lchar(char *dest, const t_lchar *src, size_t n)
{
	size_t			x;
	size_t			y;
	const t_lchar	*tabsrc;
	char			*tabdest;

	x = 0;
	y = 0;
	tabsrc = src;
	tabdest = dest;
	while (x < n)
	{
		if (tabsrc[x].c != '\0')
		{
			tabdest[y] = tabsrc[x].c;
			y++;
		}
		x++;
	}
	tabdest[y] = '\0';
	return (tabdest);
}

static int	ft_lcharlen_to_type(t_lchar *cmd, int type)
{
	int		x;

	x = 0;
	ft_printf("111\n");
	ft_printf("[%c], [%s]\n", cmd[x].c, ft_print_type(cmd[x].type));
	while (cmd[x].c != '\0' && cmd[x].type == type)
	{
		ft_printf("[%c], [%s]\n", cmd[x].c, ft_print_type(cmd[x].type));
		x++;
	}
	return (x);
}

int			creat_tree(t_exec *c, t_lchar *cmd, t_len_exec *len_exec)
{
	int		sep;
	int		pipe;
	int		redir;
	int		pos;
	int		tmp_pos;

	pos = 0;
	sep = 0;
	pipe = 0;
	redir = 0;
	while (sep < len_exec->sep)
	{
		tmp_pos = pos;
		pos = ft_lcharlen_to_type(cmd + pos, _CMD);
		ft_printf("[%d]\n", pos);
		if ((c->sep[sep]->pipe[pipe]->cmd.exec = ft_memalloc(sizeof(char) *
						(pos + 1))) == NULL)
			return (1);
		ft_memcpy_char_lchar(c->sep[sep]->pipe[pipe]->cmd.exec,
				cmd + tmp_pos, pos);
		ft_printf("[%s]\n", c->sep[sep]->pipe[pipe]->cmd.exec);
		tmp_pos = pos;
		pos = ft_lcharlen_to_type(cmd + pos, _SPACE);
		tmp_pos = pos;
		pos = ft_lcharlen_to_type(cmd + pos, _ARGV);
		sep++;
	}
	return (0);
}
