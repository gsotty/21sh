/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 13:29:19 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/20 17:47:46 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

/*
** il me faut un char ** qui contien tous les cmd a exe dans le bonne ordre.
*/

static void	exe_fork(int len_cmd, char **tab_cmd, t_struc_envp *struc_envp)
{
	pid_t	father;
	int		status;

	if (len_cmd == 0)
		return ;
	if ((father = fork()) == -1)
		ft_printf("error fork\n");
	if (father > 0)
	{
		signal(SIGINT, SIG_IGN);
		if ((wait(&status)) == -1)
			perror("wait");
		if (WIFSIGNALED(status) == 1)
			write(0, "\n", 1);
		return ;
	}
	if (father == 0)
	{
		ft_exe(tab_cmd, struc_envp);
		exit(0);
	}
}

static char	*replace_var_envp(char *cmd, t_len_cmd *len,
		t_struc_envp *struc_envp)
{
	int		x;
	int		y;
	int		len_replace;
	char	*tmp;
	char	*replace;
	char	*new_cmd;

	x = 0;
	(void)struc_envp;
	while ((x < len->len) && (cmd[x] != '\0'))
	{
		if (cmd[x] == '\\')
		{
		}
		else if (cmd[x] == '$')
		{
			y = x + 1;
			while (cmd[y] != ' ' && cmd[y] != '\t' && cmd[y] != '\0')
				y++;
			if ((tmp = ft_memalloc(sizeof(char) * (y + 1))) == NULL)
				return (NULL);
			ft_memcpy(tmp, cmd + x, y);
			tmp[y - x] = '\0';
			ft_printf("%s\n", tmp);
			if ((replace = find_var_env(tmp + 1, struc_envp)) == NULL)
			{
				if ((new_cmd = ft_memalloc(sizeof(char) *
								(len->len_cmd_malloc))) == NULL)
					return (NULL);
				ft_memcpy(new_cmd, cmd, x);
				ft_memcpy(new_cmd + x, cmd + y, len->len - y);
				new_cmd[x + (len->len - y)] = '\0';
				cmd = new_cmd;
			}
			else
			{
				len_replace = ft_strlen(replace);
				len->len_cmd_malloc += len_replace;
				if ((new_cmd = ft_memalloc(sizeof(char) *
								len->len_cmd_malloc)) == NULL)
					return (NULL);
				ft_memcpy(new_cmd, cmd, x);
				ft_memcpy(new_cmd + x, replace, len_replace);
				ft_memcpy(new_cmd + len_replace + x, cmd + y, len->len - y);
				new_cmd[x + len_replace + (len->len - y)] = '\0';
				cmd = new_cmd;
			}
		}
		x++;
	}
	return (cmd);
}

int			nbr_of_cmd_argc(char *cmd)
{
	int		x;
	int		cmd_argc;
	int		in_double_quote;
	int		in_single_quote;

	x = 0;
	cmd_argc = 0;
	in_double_quote = 0;
	in_single_quote = 0;
	while (cmd[x] != '\0')
	{
		ft_printf("%d\n", x);
		write(1, "111\n", 4);
		if (cmd[x] == '\\')
		{
			if (cmd[x + 1] != '\0')
				x += 2;
			else
				x++;
		}
		else if (cmd[x] != ' ' && cmd[x] != '\t' && cmd[x] != '\0')
		{
			cmd_argc++;
			while (cmd[x] != ' ' && cmd[x] != '\t' && cmd[x] != '\0')
			{
				write(1, "122\n", 4);
				if (cmd[x] == '\'' && cmd[x - 1] == ' ' && cmd[x - 1] == '\t')
				{
					x++;
					while (cmd[x] != '\0')
					{
						ft_printf("%c ", cmd[x]);
				write(1, "133\n", 4);
						if (cmd[x] == '\'')
						{
							x++;
							break ;
						}
						x++;
					}
					break ;
				}
				else if (cmd[x] == '\"' && cmd[x - 1] == ' ' && cmd[x - 1] == '\t')
				{
					x++;
					while (cmd[x] != '\0')
					{
						ft_printf("%c ", cmd[x]);
				write(1, "144\n", 4);
						if (cmd[x] == '\"')
						{
							x++;
							break ;
						}
						x++;
					}
					break ;
				}
				else
				{
					x++;
				}
			}
		}
		else
		{
			x++;
		}
	}
	ft_printf("%d\n", cmd_argc);
	return (cmd_argc);
}

int			parser(char *cmd, t_len_cmd *len, t_struc_envp *struc_envp)
{
	char	**tab_cmd;
	int		len_cmd;
	char	**test;
	int		x;
	int		cmd_argc;
	int		in_double_quote;
	int		in_single_quote;
	int		pos_cmd;

	if ((tab_cmd = ft_memalloc(sizeof(char *) * nbr_of_cmd_argc(cmd))) == NULL)
		return (1);
	x = 0;
	pos_cmd = 0;
	cmd_argc = 0;
	in_double_quote = 0;
	in_single_quote = 0;
	while (cmd[x] != '\0')
	{
		write(1, "211\n", 4);
		if (cmd[x] == '\\')
		{
			if (cmd[x + 1] != '\0')
				x += 2;
			else
				x++;
		}
		else if (cmd[x] != ' ' && cmd[x] != '\t')
		{
			pos_cmd = x;
			while (cmd[x] != ' ' && cmd[x] != '\t' && cmd[x] != '\0')
			{
				write(1, "222\n", 4);
				if (cmd[x] == '\'' && cmd[x - 1] == ' ' && cmd[x - 1] == '\t')
				{
					x++;
					while (cmd[x] != '\0')
					{
						write(1, "233\n", 4);
						if (cmd[x] == '\'')
						{
							x++;
							break ;
						}
						x++;
					}
					break ;
				}
				else if (cmd[x] == '\"' && cmd[x - 1] == ' ' && cmd[x - 1] == '\t')
				{
					x++;
					while (cmd[x] != '\0')
					{
						write(1, "244\n", 4);
						if (cmd[x] == '\"')
						{
							x++;
							break ;
						}
						x++;
					}
					break ;
				}
				else
				{
					x++;
				}
			}
			if ((tab_cmd[cmd_argc] = ft_memalloc(sizeof(char) *
							(x - pos_cmd))) == NULL)
				return (1);
			ft_memcpy(tab_cmd[cmd_argc], cmd + pos_cmd, (x - pos_cmd));
			tab_cmd[cmd_argc][x - pos_cmd] = '\0';
			cmd_argc++;
		}
		else
		{
			x++;
		}
	}
	/*if ((tab_cmd[cmd_argc] = ft_memalloc(sizeof(char) *
					(x - pos_cmd))) == NULL)
		return (1);
	ft_memcpy(tab_cmd[cmd_argc], cmd + pos_cmd, (x - pos_cmd));
	tab_cmd[cmd_argc][x - pos_cmd] = '\0';
	pos_cmd = x;
	*/ft_printf("%d\n", cmd_argc);
	int		a=0;
	while (a < cmd_argc)
	{
		ft_printf("%s\n", tab_cmd[a]);
		a++;
	}
	test = ft_strsplit_space(cmd, "#");
	cmd = replace_var_envp(cmd, len, struc_envp);
	tab_cmd = ft_strsplit_space(cmd, " \t");
	len_cmd = len_tab(tab_cmd);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	exe_fork(len_cmd, tab_cmd, struc_envp);
	free_tab(tab_cmd, len_cmd);
	free(cmd);
	return (0);
}
