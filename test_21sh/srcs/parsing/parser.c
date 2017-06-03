/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 12:29:03 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/03 14:40:30 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vingt_et_un_sh.h"
#include "../../includes/builtin.h"
#include "../../includes/tools.h"

static void	env_fork(char **argv, char ***envp)
{
	pid_t	father;

	father = fork();
	if (father > 0)
	{
		wait(NULL);
		return ;
	}
	if (father == 0)
	{
		ft_env(argv, envp);
		free_tab(*envp);
		exit(0);
	}
	return ;
}

void		exe_cmd(int argc, char **argv, char ***envp)
{
	if (argv == NULL || argv[0] == NULL)
		return ;
	if (ft_strcmp(argv[0], "env") == 0)
		env_fork(argv, envp);
	else if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argv);
	else if (ft_strcmp(argv[0], "setenv") == 0)
		ft_setenv(argv, envp);
	else if (ft_strcmp(argv[0], "unsetenv") == 0)
		ft_unsetenv(argv, envp);
	else if (ft_strcmp(argv[0], "cd") == 0)
		ft_cd(argv, envp);
	else
		exe_fork(argc, argv, envp);
	return ;
}

static int	len_tab(char **argv)
{
	int		x;

	x = 0;
	while (argv[x] != NULL)
		x++;
	return (x);
}

void		parser(char *buf, char ***envp)
{
	int		x;
	int		len_argv;
	int		argc;
	char	**argv;
	char	**sep_exe;

	x = 0;
	sep_exe = ft_strsplit_space(buf, ";");
	len_argv = len_tab(sep_exe);
	while (x < len_argv)
	{
		if (sep_exe != NULL && sep_exe[x] != NULL)
		{
			if ((argv = ft_strsplit_space(sep_exe[x], " \t")) != NULL)
			{
				argc = len_tab(argv);
				exe_cmd(argc, argv, envp);
				free_tab(argv);
			}
		}
		x++;
	}
	free_tab(sep_exe);
	return ;
}
