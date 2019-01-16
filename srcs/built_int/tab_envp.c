/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 12:45:18 by gsotty            #+#    #+#             */
/*   Updated: 2019/01/16 13:30:12 by gsotty           ###   ########.fr       */
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

int		remalloc_env(t_envp *my_envp, int plus)
{
	int		x;
	char	**new_envp;
	int		len_var;

	if ((new_envp = ft_memalloc((sizeof(char *) * (my_envp->len + plus + 1))
					+ 1)) == NULL)
		return (1);
	x = 0;
	while (x < (my_envp->len + plus))
	{
		if (my_envp->envp[x] != NULL)
		{
			new_envp[x] = ft_strdup(my_envp->envp[x]);
			len_var = ft_strlen(my_envp->envp[x]);
			if((new_envp[x] = ft_memalloc(sizeof(char *) * (len_var) + 1))
						== NULL)
				return (1);
			ft_memcpy(new_envp[x], my_envp->envp[x], len_var);
			new_envp[x][len_var] = '\0';
			free(my_envp->envp[x]);
		}
		else
			new_envp[x] = NULL;
		x++;
	}
	free(my_envp->envp);
	my_envp->envp = new_envp;
	my_envp->len += plus;
	my_envp->len_malloc = my_envp->len;
	return (0);
}
