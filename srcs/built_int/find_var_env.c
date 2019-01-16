/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:32:24 by gsotty            #+#    #+#             */
/*   Updated: 2019/01/16 13:52:26 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vingt_et_un_sh.h"

char	*find_var_env(char *name, t_envp *my_envp)
{
	int		x;
	int		len;
	char	*p;
	char	*tmp;

	x = 0;
	if (my_envp->envp == NULL || my_envp->envp[0] == NULL)
		return (NULL);
	while (my_envp->envp[x] != NULL)
	{
		tmp = ft_strdup(my_envp->envp[x]);
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
	if (my_envp->envp[x] == NULL)
		return (NULL);
	return (my_envp->envp[x] + len + 1);
}
