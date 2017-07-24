/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 14:35:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/03 08:57:40 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_no_argv(t_flag_cd *flag_cd)
{
	char	*tmp;

	if ((tmp = find_var_env("HOME")) == NULL)
	{
		ft_printf_e("\033[31mcd: HOME not set\033[0m\n");
		return ;
	}
	add_oldpwd(flag_cd, find_var_env("PWD"));
	if (chdir(tmp) == -1)
	{
		ft_printf_e("\033[31mcd: no such file or directory:\033[0m %s\n", tmp);
		return ;
	}
	add_pwd(flag_cd, tmp);
	return ;
}

void	cd_argv(char **argv, t_flag_cd *flag_cd, int x)
{
	add_oldpwd(flag_cd, find_var_env("PWD"));
	if (chdir(argv[x]) == -1)
	{
		ft_printf_e("\033[31mcd: no such file or directory:\033[0m %s\n",
				argv[x]);
		return ;
	}
	add_pwd(flag_cd, argv[x]);
	return ;
}

void	cd_argv_neg(t_flag_cd *flag_cd)
{
	char	*tmp;
	char	*tmp_join;

	if (g_envp == NULL || ((tmp = find_var_env("OLDPWD")) == NULL))
	{
		ft_printf_e("\033[31mcd: OLDPWD not set\033[0m\n");
		return ;
	}
	tmp_join = ft_strdup(tmp);
	add_oldpwd(flag_cd, find_var_env("PWD"));
	if (chdir(tmp_join) == -1)
	{
		ft_printf_e("\033[31mcd: no such file or directory:\033[0m %s\n",
				tmp_join);
		free(tmp_join);
		return ;
	}
	ft_printf("%s\n", tmp_join);
	add_pwd(flag_cd, tmp_join);
	free(tmp_join);
	return ;
}

int		check_flag_cd(t_flag_cd *flag_cd, char **argv)
{
	int		x;

	x = 1;
	while (argv[x] != NULL)
	{
		if (ft_strcmp(argv[x], "-L") == 0)
			flag_cd->l_maj = 1;
		else if (ft_strcmp(argv[x], "-P") == 0)
			flag_cd->p_maj = 1;
		else
			break ;
		x++;
	}
	if (argv[x] == NULL)
		flag_cd->no_ag = 1;
	else if (ft_strcmp(argv[1], "-") == 0)
		flag_cd->neg = 1;
	else if (!(argv[x] != '\0' || argv[x] == '\0'))
	{
		ft_printf_e("\033[31mcd: string not in pwd:\033[0m %s\n", argv[x]);
		return (-1);
	}
	return (x);
}

void	cd(char **argv)
{
	int			x;
	char		*pwd;
	t_flag_cd	flag_cd;

	x = 0;
	ft_memset(&flag_cd, '\0', sizeof(flag_cd));
	if ((x = check_flag_cd(&flag_cd, argv)) == -1)
		return ;
	if (g_envp == NULL || ((pwd = find_var_env("PWD")) == NULL))
		add_pwd(&flag_cd, argv[x]);
	if (flag_cd.no_ag == 1)
		cd_no_argv(&flag_cd);
	else if (flag_cd.neg == 1)
		cd_argv_neg(&flag_cd);
	else
		cd_argv(argv, &flag_cd, x);
	return ;
}
