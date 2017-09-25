/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 13:29:19 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/25 17:09:06 by gsotty           ###   ########.fr       */
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

static int		define_lchar(t_lchar *cmd)
{
	int		x;
	int		y;
	int		is_cmd;
	int		is_redir;
	int		cmd_is_enpli;

	x = 0;
	y = 0;
	is_cmd = 0;
	is_redir = 0;
	cmd_is_enpli = 0;
	while (cmd[x].c != '\0')
	{
		if (cmd[x].c == '\\')
		{
			x++;
			if (is_cmd == 0)
			{
				if (is_redir == 1)
				{
					cmd[x].type = _FILE_NAME;
				}
				else
				{
					cmd[x].type = _CMD;
					cmd_is_enpli = 1;
				}
			}
			else if (is_cmd == 1)
			{
				if (cmd[x].type == 0)
				{
					if (is_redir == 1)
					{
						cmd[x].type = _FILE_NAME;
					}
					else
						cmd[x].type = _ARGV;
				}
			}
		}
		else if (cmd[x].c == '\'')
		{
			x++;
			while (cmd[x].c != '\'')
			{
				if (is_cmd == 0)
				{
					if (is_redir == 1)
					{
						cmd[x].type = _FILE_NAME;
					}
					else
					{
						cmd[x].type = _CMD;
						cmd_is_enpli = 1;
					}
				}
				else if (is_cmd == 1)
				{
					if (cmd[x].type == 0)
					{
						if (is_redir == 1)
						{
							cmd[x].type = _FILE_NAME;
						}
						else
							cmd[x].type = _ARGV;
					}
				}
				x++;
			}
		}
		else if (cmd[x].c == '\"')
		{
			x++;
			while (cmd[x].c != '\"')
			{
				if (is_cmd == 0)
				{
					if (is_redir == 1)
					{
						cmd[x].type = _FILE_NAME;
					}
					else
					{
						cmd[x].type = _CMD;
						cmd_is_enpli = 1;
					}
				}
				else if (is_cmd == 1)
				{
					if (cmd[x].type == 0)
					{
						if (is_redir == 1)
						{
							cmd[x].type = _FILE_NAME;
						}
						else
							cmd[x].type = _ARGV;
					}
				}
				x++;
			}
		}
		else if (cmd[x].c == ';')
		{
			cmd[x].type = _SEP;
			cmd_is_enpli = 0;
			is_redir = 0;
			is_cmd = 0;
		}
		else if (cmd[x].c == '&' && cmd[x + 1].c == '&')
		{
			cmd[x].type = _AND;
			cmd[x + 1].type = _AND;
			is_redir = 0;
		}
		else if (cmd[x].c == '|' && cmd[x + 1].c == '|')
		{
			cmd[x].type = _OR;
			cmd[x + 1].type = _OR;
			is_redir = 0;
		}
		else if (cmd[x].c == '|' && cmd[x].type != _OR)
		{
			cmd[x].type = _PIPE;
			cmd_is_enpli = 0;
			is_cmd = 0;
			is_redir = 0;
		}
		else if (cmd[x].c == '>' && cmd[x + 1].c == '>')
		{
			cmd[x].type = _APPROUT;
			cmd[x + 1].type = _APPROUT;
			is_redir = 1;
		}
		else if (cmd[x].c == '<' && cmd[x + 1].c == '<')
		{
			cmd[x].type = _HEREDOC;
			cmd[x + 1].type = _HEREDOC;
			is_redir = 1;
		}
		else if (cmd[x].c == '>' && cmd[x + 1].c == '&')
		{
			cmd[x].type = _DUP_ROUT;
			cmd[x + 1].type = _DUP_ROUT;
			is_redir = 1;
		}
		else if (cmd[x].c == '<' && cmd[x + 1].c == '&')
		{
			cmd[x].type = _DUP_RINT;
			cmd[x + 1].type = _DUP_RINT;
			is_redir = 1;
		}
		else if (cmd[x].c == '&' && cmd[x + 1].c == '>')
		{
			cmd[x].type = _ROUTERR;
			cmd[x + 1].type = _ROUTERR;
			is_redir = 1;
		}
		else if (cmd[x].c == '>' && cmd[x].type == 0)
		{
			cmd[x].type = _ROUT;
			is_redir = 1;
		}
		else if (cmd[x].c == '<' && cmd[x].type == 0)
		{
			cmd[x].type = _RINT;
			is_redir = 1;
		}
		else if (cmd[x].c == ' ' || cmd[x].c == '\t' || cmd[x].c == '\n')
		{
			cmd[x].type = _SPACE;
			if (cmd_is_enpli == 1)
				is_cmd = 1;
		}
		else if (cmd[x].c == '-' && (cmd[x + 1].c == ' ' ||
					cmd[x + 1].c == '\t' || cmd[x + 1].c == '\n'))
		{
			cmd[x].type = _TIRET;
		}
		else if ((cmd[x].type == _DUP_ROUT || cmd[x].type == _DUP_RINT)
				&& ft_isdigit(cmd[x + 1].c) == 1)
		{
			y = (x + 1);
			while (ft_isdigit(cmd[y].c) == 1)
				y++;
			x++;
			while (x < y)
			{
				cmd[x].type = _DIGIT;
				x++;
			}
			x--;
		}
		else if (ft_isdigit(cmd[x].c) == 1)
		{
			y = x;
			while (ft_isdigit(cmd[y].c) == 1)
				y++;
			if (cmd[y].c == '>' || cmd[y].c == '<')
			{
				while (x < y)
				{
					cmd[x].type = _FD;
					x++;
				}
				x--;
			}
			else
			{
				if (is_cmd == 0)
				{
					if (is_redir == 1)
					{
						cmd[x].type = _FILE_NAME;
					}
					else
					{
						cmd[x].type = _CMD;
						cmd_is_enpli = 1;
					}
				}
				else if (is_cmd == 1)
				{
					if (cmd[x].type == 0)
					{
						if (is_redir == 1)
						{
							cmd[x].type = _FILE_NAME;
						}
						else
							cmd[x].type = _ARGV;
					}
				}
			}
		}
		else if (is_cmd == 0)
		{
			if (is_redir == 1)
			{
				cmd[x].type = _FILE_NAME;
			}
			else
			{
				cmd[x].type = _CMD;
				cmd_is_enpli = 1;
			}
		}
		else if (is_cmd == 1)
		{
			if (cmd[x].type == 0)
			{
				if (is_redir == 1)
				{
					cmd[x].type = _FILE_NAME;
				}
				else
					cmd[x].type = _ARGV;
			}
		}
		x++;
	}
	return (0);
}

int				parser(t_lchar *cmd, int len)
{
	t_exec			c;
	t_len_exec		len_exec;
	int				first_call;
	int				a;

	(void)len;
	a = 0;
	first_call = 0;
	ft_memset(&c, 0, sizeof(t_exec));
	ft_memset(&len_exec, 0, sizeof(t_len_exec));
	creat_t_len_exec(cmd, &len_exec);
	if (malloc_t_exec(&c, &len_exec) == 1)
		return (1);
	ft_printf("cmd 1 = \n");
	while (cmd[a].c != '\0')
	{
		cmd[a].type = 0;
		ft_printf("[%c], [%s]\n", cmd[a].c, ft_print_type(cmd[a].type));
		a++;
	}
	define_lchar(cmd);
	a = 0;
	ft_printf("cmd 2 = \n");
	while (cmd[a].c != '\0')
	{
		ft_printf("[%c], [%s]\n", cmd[a].c, ft_print_type(cmd[a].type));
		a++;
	}
	creat_tree(&c, cmd, &len_exec);
	return (0);
}
