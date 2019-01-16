/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 14:35:53 by gsotty            #+#    #+#             */
/*   Updated: 2019/01/16 14:17:13 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_int.h"

void	cd_no_argv(t_flag_cd *flag_cd, t_envp *my_envp)
{
	char	*tmp;

	if ((tmp = find_var_env("HOME", my_envp)) == NULL)
	{
		write(2, "\033[31mcd: HOME not set\033[0m\n", 26);
		return ;
	}
	add_oldpwd(flag_cd, find_var_env("PWD", my_envp), my_envp);
	if (chdir(tmp) == -1)
	{
		write(2, "\033[31mcd: no such file or director:\033[0m ", 39);
		write(2, tmp, ft_strlen(tmp));
		write(2, "\n", 1);
		return ;
	}
	add_pwd(flag_cd, tmp, my_envp);
	return ;
}

void	cd_argv(char **argv, t_flag_cd *flag_cd, int x, t_envp *my_envp)
{
	add_oldpwd(flag_cd, find_var_env("PWD", my_envp), my_envp);
	if (chdir(argv[x]) == -1)
	{
		write(2, "\033[31mcd: no such file or director:\033[0m ", 39);
		write(2, argv[x], ft_strlen(argv[x]));
		write(2, "\n", 1);
		return ;
	}
	add_pwd(flag_cd, argv[x], my_envp);
	return ;
}

void	cd_argv_neg(t_flag_cd *flag_cd, t_envp *my_envp)
{
	char	*tmp;
	char	*tmp_join;

	if (my_envp->envp == NULL || ((tmp = find_var_env("OLDPWD", my_envp)) == NULL))
	{
		write(2, "\033[31mcd: OLDPWD not set\033[0m\n", 28);
		return ;
	}
	tmp_join = ft_strdup(tmp);
	add_oldpwd(flag_cd, find_var_env("PWD", my_envp), my_envp);
	if (chdir(tmp_join) == -1)
	{
		write(2, "\033[31mcd: no such file or director:\033[0m ", 39);
		write(2, tmp_join, ft_strlen(tmp_join));
		write(2, "\n", 1);
		free(tmp_join);
		return ;
	}
	add_pwd(flag_cd, tmp_join, my_envp);
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
		write(2, "\033[31mcd: string not in pwd:\033[0m ", 31);
		write(2, argv[x], ft_strlen(argv[x]));
		write(2, "\n", 1);
		return (-1);
	}
	return (x);
}

int		cd(char **argv, t_envp *my_envp)
{
	int			x;
	char		*pwd;
	t_flag_cd	flag_cd;

	x = 0;
	ft_memset(&flag_cd, '\0', sizeof(flag_cd));
	if ((x = check_flag_cd(&flag_cd, argv)) == -1)
		return (1);
	if (my_envp->envp == NULL || ((pwd = find_var_env("PWD", my_envp)) == NULL))
		add_pwd(&flag_cd, argv[x], my_envp);
	if (flag_cd.no_ag == 1)
		cd_no_argv(&flag_cd, my_envp);
	else if (flag_cd.neg == 1)
		cd_argv_neg(&flag_cd, my_envp);
	else
		cd_argv(argv, &flag_cd, x, my_envp);
	return (0);
}
