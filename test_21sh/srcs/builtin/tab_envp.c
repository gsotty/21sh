/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 12:45:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/03 15:31:21 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

#include <stdio.h>

char			***creat_env(char **envp_begin, char ***envp)
{
	int		x;
	int		len;

	x = 0;
	if (envp_begin == NULL || envp_begin[0] == NULL)
		return (NULL);
	if ((envp = ft_memalloc(sizeof(envp))) == NULL)
		return (NULL);
	while (envp_begin[x] != NULL)
		x++;
	if ((*envp = ft_memalloc(sizeof(envp[0]) * (x + 1))) == NULL)
		return (NULL);
	x = 0;
	while (envp_begin[x] != NULL)
	{
		len = ft_strlen(envp_begin[x]);
		if ((envp[0][x] = ft_memalloc(sizeof(envp[0][x]) * (len + 1))) == NULL)
			return (NULL);
		ft_memcpy(envp[0][x], envp_begin[x], len);
		envp[0][x][len] = '\0';
		x++;
		envp[0][x] = NULL;
	}
	return (envp);
}

static void		remalloc_env_2(int after_size, int new_size, char **new_env,
		char ***envp)
{
	int		x;

	free(*envp);
	if ((*envp = ft_memalloc(sizeof(char *) * (new_size + 1))) == NULL)
		return ;
	x = 0;
	while (x < after_size)
	{
		envp[0][x] = ft_strdup(new_env[x]);
		free(new_env[x]);
		new_env[x] = NULL;
		x++;
	}
	free(new_env);
	return ;
}

void			remalloc_env(int after_size, int new_size, char ***envp)
{
	int		x;
	char	**new_env;

	if ((new_env = ft_memalloc(sizeof(char *) * (new_size + 1))) == NULL)
		return ;
	x = 0;
	while (x < after_size)
	{
		new_env[x] = ft_strdup(envp[0][x]);
		free(envp[0][x]);
		envp[0][x] = NULL;
		x++;
	}
	remalloc_env_2(after_size, new_size, new_env, envp);
}
