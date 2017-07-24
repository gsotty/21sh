/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:32:24 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/25 15:22:14 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var_env(char *name)
{
	int		x;
	int		len;
	char	*p;
	char	*tmp;

	x = 0;
	if (g_envp == NULL || g_envp[0] == NULL)
		return (NULL);
	while (g_envp[x] != NULL)
	{
		tmp = ft_strdup(g_envp[x]);
		p = ft_strchr(tmp, '=');
		*p = '\0';
		len = (p - tmp);
		if (ft_strcmp(tmp, name) == 0)
			break ;
		free(tmp);
		tmp = NULL;
		x++;
	}
	if (tmp != NULL)
		free(tmp);
	if (g_envp[x] == NULL)
		return (NULL);
	return (g_envp[x] + len + 1);
}
