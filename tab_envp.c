/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 16:10:12 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/21 16:57:15 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

char			**creat_env(char **envp_begin)
{
	char	**envp;
	int		x;

	x = 0;
	if (envp_begin == NULL || envp_begin[0] == NULL)
		return (NULL);
	while (envp_begin[x] != NULL)
		x++;
	if ((envp = ft_memalloc(sizeof(char *) * (x + 1))) == NULL)
		return (NULL);
	x = 0;
	while (envp_begin[x] != NULL)
	{
		envp[x] = ft_strdup(envp_begin[x]);
		x++;
	}
	return (envp);
}

static char		**remalloc_env_2(int after_size, int new_size,
		char **envp, char **new_env)
{
	int		x;

	free(envp);
	if ((envp = ft_memalloc(sizeof(char *) * (new_size + 1))) == NULL)
		return (NULL);
	x = 0;
	while (x < after_size)
	{
		envp[x] = ft_strdup(new_env[x]);
		free(new_env[x]);
		new_env[x] = NULL;
		x++;
	}
	free(new_env);
	return (new_env);
}

char			**remalloc_env(char **envp, int after_size, int new_size)
{
	int		x;
	char	**new_env;

	if ((new_env = ft_memalloc(sizeof(char *) * (new_size + 1))) == NULL)
		return (NULL);
	x = 0;
	while (x < after_size)
	{
		new_env[x] = ft_strdup(envp[x]);
		free(envp[x]);
		envp[x] = NULL;
		x++;
	}
	return (remalloc_env_2(after_size, new_size, envp, new_env));
}
