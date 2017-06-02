/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 12:45:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/02 10:25:43 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void			creat_env(char **envp_begin, char ***envp)
{
	int		x;

	x = 0;
	if (envp_begin == NULL || envp_begin[0] == NULL)
		return ;
	while (envp_begin[x] != NULL)
		x++;
	if ((*envp = ft_memalloc(sizeof(char *) * (x + 1))) == NULL)
		return ;
	x = 0;
	while (envp_begin[x] != NULL)
	{
		*envp[x] = ft_strdup(envp_begin[x]);
		x++;
	}
	return ;
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
		*envp[x] = ft_strdup(new_env[x]);
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
		new_env[x] = ft_strdup(*envp[x]);
		free(*envp[x]);
		*envp[x] = NULL;
		x++;
	}
	remalloc_env_2(after_size, new_size, new_env, envp);
}
