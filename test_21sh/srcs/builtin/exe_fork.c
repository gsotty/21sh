/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 12:49:24 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/06 12:32:44 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/tools.h"
#include "../../includes/vingt_et_un_sh.h"

#include <stdio.h>
#include <errno.h>

static int		ft_while_exe_path(char **argv, char **path, int x,
		char ***envp)
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
		execve(tmp_join, argv, *envp);
		free(tmp_join);
		return (1);
	}
	free(tmp_path);
	free(tmp_join);
	return (0);
}

static void		exe_path(char **argv, char **path, char ***envp)
{
	int			x;

	x = 0;
	if (path == NULL)
		return ;
	while (path[x] != NULL)
	{
		if ((ft_while_exe_path(argv, path, x, envp)) == 1)
			return ;
		x++;
	}
	write(2, "\033[31m21sh: command not found:\033[0m ", 34);
	write(2, ft_strjoin(argv[0], "\n"), ft_strlen(argv[0]) + 1);
}

static void		no_exe_cmd_2(char **argv, int x, char ***envp)
{
	char	*p;
	char	*tmp;
	char	**path;

	if (*envp == NULL || envp[0][x] == NULL)
	{
		write(2, "\033[31m21sh: command not found:\033[0m ", 34);
		write(2, ft_strjoin(argv[0], "\n"), ft_strlen(argv[0]) + 1);
		return ;
	}
	else
	{
		tmp = ft_strdup(envp[0][x]);
		p = ft_strchr(tmp, '=');
		*p = '\0';
		path = ft_strsplit_space(p + 1, ":");
		exe_path(argv, path, envp);
		free_tab(path);
		free(tmp);
	}
}

static void		no_exe_cmd(char **argv, char ***envp)
{
	int		x;
	char	*p;
	char	*tmp;

	x = 0;
	if (*envp == NULL || envp[0][x] == NULL)
	{
		write(2, "\033[31m21sh: command not found:\033[0m ", 34);
		write(2, ft_strjoin(argv[0], "\n"), ft_strlen(argv[0]) + 1);
		return ;
	}
	while (envp[0][x] != NULL)
	{
		tmp = ft_strdup(envp[0][x]);
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
	no_exe_cmd_2(argv, x, envp);
}

void			exe_fork(int argc, char **argv, char ***envp)
{
	pid_t	father;

	father = fork();
	if (argc == 0)
	{
		write(2, "\033[31m21sh: command not found:\033[0m ", 34);
		write(2, ft_strjoin(argv[0], "\n"), ft_strlen(argv[0]) + 1);
		return ;
	}
	if (father > 0)
	{
		wait(NULL);
		prepare_term();
		return ;
	}
	if (father == 0)
	{
		reset_term();
		if (access(argv[0], F_OK | X_OK) == 0)
			execve(argv[0], argv, *envp);
		else
			no_exe_cmd(argv, envp);
		exit(0);
	}
	return ;
}
