/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 16:25:03 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/27 17:51:20 by gsotty           ###   ########.fr       */
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

static void	print_tree(t_exec *c)
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
			while (c->sep[x]->pipe[y]->redir[w] != NULL)
			{
				ft_printf("			redir = [%s]\n",
						c->sep[x]->pipe[y]->redir[w]->file_name);
				ft_printf("				[%s]\n",
						ft_print_type(c->sep[x]->pipe[y]->redir[w]->type));
				ft_printf("				[%d]\n",
						c->sep[x]->pipe[y]->redir[w]->fd);
				ft_printf("				[%d]\n",
						c->sep[x]->pipe[y]->redir[w]->digit);
				w++;
			}
			y++;
		}
		x++;
	}
}

int			creat_tree(t_exec *c, t_lchar *cmd, t_history *history)
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
	redir = -1;
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
		else if (cmd[pos].type == _FILE_NAME)
		{
			tmp_pos = pos;
			pos += ft_lcharlen_to_type(cmd + pos, _FILE_NAME);
			if ((c->sep[sep]->pipe[pipe]->redir[redir]->file_name =
						ft_memalloc(sizeof(char) * (pos + 1))) == NULL)
				return (1);
			ft_memcpy_char_lchar(c->sep[sep]->pipe[pipe]->redir[redir]->
					file_name, cmd + tmp_pos, pos - tmp_pos);
			if (c->sep[sep]->pipe[pipe]->redir[redir]->type == _HEREDOC)
				creat_heredoc(c->sep[sep]->pipe[pipe]->redir[redir], history);
		}
		else if (cmd[pos].type == _DIGIT)
		{
			tmp_pos = pos;
			pos += ft_lcharlen_to_type(cmd + pos, _DIGIT);
			c->sep[sep]->pipe[pipe]->redir[redir + 1]->digit =
				ft_atoi_lchar(cmd + tmp_pos);
			ft_printf("			[%d]\n",
					c->sep[sep]->pipe[pipe]->redir[redir + 1]->digit);
		}
		else if (cmd[pos].type == _FD)
		{
			tmp_pos = pos;
			pos += ft_lcharlen_to_type(cmd + pos, _FD);
			c->sep[sep]->pipe[pipe]->redir[redir + 1]->fd =
				ft_atoi_lchar(cmd + tmp_pos);
			ft_printf("			[%d]\n",
					c->sep[sep]->pipe[pipe]->redir[redir + 1]->fd);
		}
		else if (cmd[pos].type == _SEP)
		{
			argv = 0;
			pipe = 0;
			redir = -1;
			sep++;
			pos++;
		}
		else if (cmd[pos].type == _PIPE)
		{
			argv = 0;
			redir = -1;
			pipe++;
			pos++;
		}
		else if (cmd[pos].type == _RINT || cmd[pos].type == _ROUT)
		{
			redir++;
			c->sep[sep]->pipe[pipe]->redir[redir]->type = cmd[pos].type;
			pos++;
		}
		else if (cmd[pos].type == _APPROUT || cmd[pos].type == _HEREDOC ||
				cmd[pos].type == _DUP_RINT || cmd[pos].type == _DUP_ROUT ||
				cmd[pos].type == _ROUTERR)
		{
			redir++;
			c->sep[sep]->pipe[pipe]->redir[redir]->type = cmd[pos].type;
			pos = pos + 2;
		}
		else
		{
			pos++;
		}
	}
	print_tree(c);
	return (0);
}