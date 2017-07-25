/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:32:24 by gsotty            #+#    #+#             */
/*   Updated: 2017/07/25 14:04:15 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

char	*find_var_env(char *name, t_struc_envp *struc_envp)
{
	int		x;
	int		len;
	char	*p;
	char	*tmp;

	x = 0;
	if (struc_envp->envp == NULL || struc_envp->envp[0] == NULL)
		return (NULL);
	while (struc_envp->envp[x] != NULL)
	{
		tmp = ft_strdup(struc_envp->envp[x]);
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
	if (struc_envp->envp[x] == NULL)
		return (NULL);
	return (struc_envp->envp[x] + len + 1);
}
