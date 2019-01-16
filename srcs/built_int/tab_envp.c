/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 12:45:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/25 16:56:00 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_int.h"
#include <stdio.h>

char	**creat_env(char **envp_begin, char **envp)
{
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

void	remalloc_env(char ***envp, int plus)
{
	int		x;
	int		size_envp;
	char	**new_envp;
	int		len_var;

	size_envp = 0;
	while (*envp[size_envp] != NULL)
		size_envp++;
	if ((new_envp = ft_memalloc((sizeof(char *) * (size_envp + plus + 1))
					+ 1)) == NULL)
		return ;
	x = 0;
	while (x < (size_envp + plus))
	{
		if (*envp[x] != NULL)
		{
			new_envp[x] = ft_strdup(*envp[x]);
			len_var = ft_strlen(*envp[x]);
			if((new_envp[x] = ft_memalloc(sizeof(char *) * (len_var) + 1))
						== NULL)
				return ;
			ft_memcpy(new_envp[x], *envp[x], len_var);
			new_envp[x][len_var] = '\0';
			free(*envp[x]);
		}
		else
			new_envp[x] = NULL;
		x++;
	}
	free(*envp);
	*envp = new_envp;
	return ;
}
