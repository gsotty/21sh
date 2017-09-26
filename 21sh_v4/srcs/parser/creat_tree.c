/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 16:25:03 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/26 18:35:29 by gsotty           ###   ########.fr       */
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
	ft_printf("		111\n");
	ft_printf("1 = [%c], [%s]\n", cmd[x].c, ft_print_type(cmd[x].type));
	while (cmd[x].c != '\0' && cmd[x].type == type)
	{
		ft_printf("[%c], [%s]\n", cmd[x].c, ft_print_type(cmd[x].type));
		x++;
	}
	ft_printf("2 = [%c], [%s]\n", cmd[x].c, ft_print_type(cmd[x].type));
	return (x);
}

static void	print_tree(t_exec *c, t_len_exec *len_exec)
{
	int		x;
	int		y;
	int		z;
	int		w;

	x = 0;
	ft_printf("exec = \n");
	while (c->sep[x] != NULL)
	{
		ft_printf("	sep = \n");
		y = 0;
		while (c->sep[x]->pipe[y] != NULL)
		{
			ft_printf("		pipe = \n");
			ft_printf("			cmd = [%s]\n", c->sep[x]->pipe[y]->cmd.exec);
			z = 0;
			while (c->sep[x]->pipe[y]->cmd.argv[z] != NULL)
			{
				ft_printf("			argv = [%s]\n",
						c->sep[x]->pipe[y]->cmd.argv[z]);
				z++;
			}
			w = 0;
			while (w < len_exec->redir)
			{
				ft_printf("			redir = [%s]\n",
						c->sep[x]->pipe[y]->redir[w]->file_name);
				w++;
			}
			y++;
		}
		x++;
	}
}

int			creat_tree(t_exec *c, t_lchar *cmd, t_len_exec *len_exec)
{
	int		sep;
	int		pipe;
	int		redir;
	int		argv;
	int		pos;
	int		tmp_pos;

	pos = 0;
	sep = 0;
	pipe = 0;
	redir = 0;
	argv = 0;
	while (cmd[pos].c != '\0')
	{
		if (cmd[pos].type == _CMD)
		{
			tmp_pos = pos;
			pos += ft_lcharlen_to_type(cmd + pos, _CMD);
			if ((c->sep[sep]->pipe[pipe]->cmd.exec = ft_memalloc(sizeof(char) *
							(pos + 1))) == NULL)
				return (1);
			ft_memcpy_char_lchar(c->sep[sep]->pipe[pipe]->cmd.exec,
					cmd + tmp_pos, pos - tmp_pos);
			if ((c->sep[sep]->pipe[pipe]->cmd.argv[argv] =
						ft_memalloc(sizeof(char) * (pos + 1))) == NULL)
				return (1);
			ft_memcpy_char_lchar(c->sep[sep]->pipe[pipe]->cmd.argv[argv],
					cmd + tmp_pos, pos - tmp_pos);
			argv++;
		}
		else if (cmd[pos].type == _ARGV)
		{
			tmp_pos = pos;
			pos += ft_lcharlen_to_type(cmd + pos, _ARGV);
			if ((c->sep[sep]->pipe[pipe]->cmd.argv[argv] =
						ft_memalloc(sizeof(char) * (pos + 1))) == NULL)
				return (1);
			ft_memcpy_char_lchar(c->sep[sep]->pipe[pipe]->cmd.argv[argv],
					cmd + tmp_pos, pos - tmp_pos);
			argv++;
		}
		else if (cmd[pos].type == _SEP)
		{
			argv = 0;
			sep++;
			pos++;
		}
		else if (cmd[pos].type == _PIPE)
		{
			argv = 0;
			pipe++;
			pos++;
		}
		else if (cmd[pos].type == _RINT || cmd[pos].type == _ROUT ||
				cmd[pos].type == _APPROUT || cmd[pos].type == _HEREDOC ||
				cmd[pos].type == _DUP_RINT || cmd[pos].type == _DUP_ROUT ||
				cmd[pos].type == _ROUTERR)
		{
			
		}
		else
		{
			pos++;
		}
	}
	print_tree(c, len_exec);
	return (0);
}
