/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 12:49:24 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/27 16:44:53 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_while_exe_path(char **argv, char **path, int x)
{
	char		*tmp_join;
	char		*tmp_path;
	int			len_path;

	len_path = ft_strlen(path[x]);
	if (!(tmp_path = ft_memalloc(sizeof(char) * (len_path + 2))))
		return (1);
	ft_memcpy(tmp_path, path[x], len_path);
	ft_strcat(tmp_path, "/");
	if (access(tmp_join = ft_strjoin(tmp_path, argv[0]),
				F_OK | X_OK) == 0)
	{
		free(argv[0]);
		argv[0] = ft_strdup(tmp_join);
		execve(tmp_join, argv, g_envp);
		free(tmp_join);
		return (1);
	}
	free(tmp_path);
	free(tmp_join);
	return (0);
}

static void		exe_path(char **argv, char **path)
{
	int			x;

	x = 0;
	if (path == NULL)
		return ;
	while (path[x] != NULL)
	{
		if ((ft_while_exe_path(argv, path, x)) == 1)
			return ;
		x++;
	}
	ft_printf_e("\033[31mminishell: command not found:\033[0m %s\n", argv[0]);
}

void			no_exe_cmd_2(char **argv, int x)
{
	char	*p;
	char	*tmp;
	char	**path;

	if (g_envp == NULL || g_envp[x] == NULL)
	{
		ft_printf_e("\033[31mminishell: command not found:\033[0m %s\n",
				argv[0]);
		return ;
	}
	else
	{
		tmp = ft_strdup(g_envp[x]);
		p = ft_strchr(tmp, '=');
		*p = '\0';
		path = ft_strsplit_space(p + 1, ":");
		exe_path(argv, path);
		free_tab(path);
		free(tmp);
	}
}

void			no_exe_cmd(char **argv)
{
	int		x;
	char	*p;
	char	*tmp;

	x = 0;
	if (g_envp == NULL || g_envp[x] == NULL)
	{
		ft_printf_e("\033[31mminishell: command not found:\033[0m %s\n",
				argv[0]);
		return ;
	}
	while (g_envp[x] != NULL)
	{
		tmp = ft_strdup(g_envp[x]);
		p = ft_strchr(tmp, '=');
		*p = '\0';
		if (ft_strcmp(tmp, "PATH") == 0)
			break ;
		free(tmp);
		tmp = NULL;
		x++;
	}
	if (tmp != NULL)
		free(tmp);
	no_exe_cmd_2(argv, x);
}

void			exe_fork(int argc, char **argv)
{
	pid_t	father;

	father = fork();
	if (argc == 0)
	{
		ft_printf_e("\033[31mminishell: command not found:\033[0m %s\n",
				argv[0]);
		return ;
	}
	if (father > 0)
	{
		wait(NULL);
		return ;
	}
	if (father == 0)
	{
		if (access(argv[0], F_OK | X_OK) == 0)
			execve(argv[0], argv, g_envp);
		else
			no_exe_cmd(argv);
		exit(0);
	}
	return ;
}
