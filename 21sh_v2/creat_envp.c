/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 13:39:31 by gsotty            #+#    #+#             */
/*   Updated: 2017/07/26 13:48:18 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

char	**creat_envp(char **envp, int len_envp)
{
	int		x;
	int		len_envp_var;
	char	**new_envp;

	if ((new_envp = ft_memalloc(sizeof(char *) * len_envp + 1)) == NULL)
		return (NULL);
	x = 0;
	while (x < len_envp)
	{
		len_envp_var = ft_strlen(envp[x]);
		if ((new_envp[x] = ft_memalloc(sizeof(char *) * len_envp_var)) == NULL)
			return (NULL);
		ft_memcpy(new_envp[x], envp[x], len_envp_var);
		new_envp[x][len_envp_var] = '\0';
		x++;
	}
	return (new_envp);
}
