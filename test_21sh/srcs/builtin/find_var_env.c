/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:32:24 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/03 14:43:25 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

char	*find_var_env(char *name, char ***envp)
{
	int		x;
	int		len;
	char	*p;
	char	*tmp;

	x = 0;
	if (*envp == NULL || envp[0][0] == NULL)
		return (NULL);
	while (envp[0][x] != NULL)
	{
		tmp = ft_strdup(envp[0][x]);
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
	if (envp[0][x] == NULL)
		return (NULL);
	return (envp[0][x] + len + 1);
}
