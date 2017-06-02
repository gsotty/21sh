/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 14:35:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/02 11:12:35 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void	cd_no_argv(t_flag_cd *flag_cd, char ***envp)
{
	char	*tmp;

	if ((tmp = find_var_env("HOME", *envp)) == NULL)
	{
		write(2, "\033[31mcd: HOME not set\033[0m\n", 32);
		return ;
	}
	add_oldpwd(flag_cd, find_var_env("PWD", *envp), envp);
	if (chdir(tmp) == -1)
	{
		write(2, "\033[31mcd: no such file or directory:\033[0m ", 44);
		write(2, ft_strjoin(tmp, "\n"), ft_strlen(tmp) + 1);
		return ;
	}
	add_pwd(flag_cd, tmp, envp);
	return ;
}

void	cd_argv(char **argv, t_flag_cd *flag_cd, int x, char ***envp)
{
	add_oldpwd(flag_cd, find_var_env("PWD", *envp), envp);
	if (chdir(argv[x]) == -1)
	{
		write(2, "\033[31mcd: no such file or directory:\033[0m ", 44);
		write(2, ft_strjoin(argv[x], "\n"), ft_strlen(argv[x]) + 1);
		return ;
	}
	add_pwd(flag_cd, argv[x], envp);
	return ;
}

void	cd_argv_neg(t_flag_cd *flag_cd, char ***envp)
{
	char	*tmp;
	char	*tmp_join;

	if (*envp == NULL || ((tmp = find_var_env("OLDPWD", *envp)) == NULL))
	{
		write(2, "\033[31mcd: OLDPWD not set\033[0m\n", 31);
		return ;
	}
	tmp_join = ft_strdup(tmp);
	add_oldpwd(flag_cd, find_var_env("PWD", *envp), envp);
	if (chdir(tmp_join) == -1)
	{
		write(2, "\033[31mcd: no such file or directory:\033[0m ", 44);
		write(2, ft_strjoin(tmp_join, "\n"), ft_strlen(tmp_join) + 1);
		return ;
	}
	write(1, tmp_join, ft_strlen(tmp_join));
	add_pwd(flag_cd, tmp_join, envp);
	free(tmp_join);
	return ;
}

int		check_flag_cd(t_flag_cd *flag_cd, char **argv, char ***envp)
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
		write(2, "\033[31mcd: string not in pwd:\033[0m ", 36);
		write(2, ft_strjoin(argv[x], "\n"), ft_strlen(argv[x]) + 1);
		return (-1);
	}
	return (x);
}

void	ft_cd(char **argv, char ***envp)
{
	int			x;
	char		*pwd;
	t_flag_cd	flag_cd;

	x = 0;
	ft_memset(&flag_cd, '\0', sizeof(flag_cd));
	if ((x = check_flag_cd(&flag_cd, argv, envp)) == -1)
		return ;
	if (*envp == NULL || ((pwd = find_var_env("PWD", *envp)) == NULL))
		add_pwd(&flag_cd, argv[x], envp);
	if (flag_cd.no_ag == 1)
		cd_no_argv(&flag_cd, envp);
	else if (flag_cd.neg == 1)
		cd_argv_neg(&flag_cd, envp);
	else
		cd_argv(argv, &flag_cd, x, envp);
	return ;
}
