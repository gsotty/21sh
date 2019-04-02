/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 13:43:30 by gsotty            #+#    #+#             */
/*   Updated: 2019/01/16 14:22:09 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_int.h"

void		verif_pwd_2(char *path, char *pwd, t_envp *my_envp)
{
	struct stat		lg;
	struct stat		phy;

	if (stat(path, &lg) == -1 || stat(".", &phy) == -1)
	{
		add_env("PWD", pwd, my_envp);
	}
	if (lg.st_dev == phy.st_dev && lg.st_ino == phy.st_ino)
	{
		add_env("PWD", path, my_envp);
	}
}

void		verif_pwd(char *path, char *pwd, t_envp *my_envp)
{
	if (path != NULL && *path == '/')
		verif_pwd_2(path, pwd, my_envp);
	else
		add_env("PWD", pwd, my_envp);
}

int			add_pwd(t_flag_cd *flag_cd, char *path, t_envp *my_envp)
{
	char			pwd[PATH_MAX + 1];

	getcwd(pwd, PATH_MAX);
	if (flag_cd->p_maj == 1)
		add_env("PWD", pwd, my_envp);
	else
		verif_pwd(path, pwd, my_envp);
	return (0);
}
