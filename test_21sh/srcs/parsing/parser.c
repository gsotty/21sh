/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 12:29:03 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/07 15:37:53 by gsotty           ###   ########.fr       */
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
		prepare_term();
		return ;
	}
	if (father == 0)
	{
		reset_term();
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

void		parser(int len, char *buf, char ***envp)
{
	int				x;
	int				j;
	int				z;
	int				chk_word;
	int				len_argv;
	int				argc;
	int				chk_s_quote;
	int				chk_d_quote;
	int				chk_space;
	char			**argv;
	char			**sep_exe;
	char			**cmd;
	char			*len_cmd;

	x = 0;
	j = 0;
	chk_s_quote = 0;
	chk_d_quote = 0;
	chk_space = 0;
	while (x < len)
	{
		if (buf[x] == '\\')
		{
			buf[x] = '\0';
			x++;
		}
		else if (buf[x] == '\'' && chk_d_quote == 0)
		{
			if (chk_s_quote == 0)
				j++;
			(chk_s_quote == 1 ? (chk_s_quote = 0) : (chk_s_quote = 1));
			buf[x] = '\0';
		}
		else if (buf[x] == '\"' && chk_s_quote == 0)
		{
			if (chk_d_quote == 0)
				j++;
			(chk_d_quote == 1 ? (chk_d_quote = 0) : (chk_d_quote = 1));
			buf[x] = '\0';
		}
		else if ((buf[x] == ' ' || buf[x] == '\t') && chk_s_quote == 0 &&
				chk_d_quote == 0)
		{
			chk_space = 1;
			buf[x] = '\0';
		}
		else if (buf[x] == '#')
			break ;
		else
		{
			if (chk_space == 1 && chk_s_quote == 0 && chk_d_quote == 0)
				j++;
			if (j == 0)
				j = 1;
			chk_space = 0;
		}
		x++;
	}
	write(1, buf, len);
	write(1, "\n", 1);
	if ((cmd = ft_memalloc(sizeof(cmd) * (j + 1))) == NULL)
		return ;
	x = 0;
	z = 0;
	chk_word = 0;
	while (x < len)
	{
		if (buf[x] != '\0' && chk_word == 0)
		{
			cmd[z] = ft_strdup(buf + x);
			chk_word = 1;
		}
		else if (buf[x] == '\0' && chk_word == 1)
		{
			z++;
			chk_word = 0;
		}
		if (z == j)
			break ;
		x++;
	}
	cmd[j] = NULL;
	x = 0;
	while (cmd[x] != NULL)
	{
		printf("%s\n", cmd[x]);
		x++;
	}
	exe_cmd(j, cmd, envp);
	free_tab(cmd);
	return ;
}
