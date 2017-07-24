/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 16:56:31 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/26 13:48:28 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		verif_pwd_prompt(char *tmp)
{
	char			pwd[PATH_MAX];
	struct stat		lg;
	struct stat		phy;

	if (stat(tmp, &lg) == -1 || stat(".", &phy) == -1)
	{
		getcwd(pwd, PATH_MAX);
		if (ft_strchr(pwd, '/') == ft_strrchr(pwd, '/'))
			ft_printf("\033[32m%s\033[0m \033[36m$>\033[0m ",
					ft_strrchr(pwd, '/'));
		else
			ft_printf("\033[32m%s\033[0m \033[36m$>\033[0m ",
					ft_strrchr(pwd, '/') + 1);
	}
	if (lg.st_dev == phy.st_dev && lg.st_ino == phy.st_ino)
	{
		if (ft_strchr(tmp, '/') == ft_strrchr(tmp, '/'))
			ft_printf("\033[32m%s\033[0m \033[36m$>\033[0m ",
					ft_strrchr(tmp, '/'));
		else
			ft_printf("\033[32m%s\033[0m \033[36m$>\033[0m ",
					ft_strrchr(tmp, '/') + 1);
	}
}

void		print_prompt(void)
{
	char			*tmp;
	char			pwd[PATH_MAX];

	if ((tmp = find_var_env("PWD")) != NULL && *tmp == '/')
		verif_pwd_prompt(tmp);
	else
	{
		getcwd(pwd, PATH_MAX);
		if (ft_strchr(pwd, '/') == ft_strrchr(pwd, '/'))
			ft_printf("\033[32m%s\033[0m \033[36m$>\033[0m ",
					ft_strrchr(pwd, '/'));
		else
			ft_printf("\033[32m%s\033[0m \033[36m$>\033[0m ",
					ft_strrchr(pwd, '/') + 1);
	}
}
