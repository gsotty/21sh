/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 16:44:41 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/29 16:45:42 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

char	*find_var_envp(char *name)
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
