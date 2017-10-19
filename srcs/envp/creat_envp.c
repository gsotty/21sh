/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:22:54 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/18 14:44:42 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int			creat_envp(char **envp)
{
	int		x;
	int		len_envp;
	int		len_argv;

	if (g_envp == NULL && envp != NULL)
	{
		x = 0;
		len_envp = len_tab(envp);
		if (!(g_envp = ft_memalloc(sizeof(char *) * (len_envp + 1))))
			return (1);
		while (envp[x] != NULL)
		{
			len_argv = ft_strlen(envp[x]);
			if (!(g_envp[x] = ft_memalloc(sizeof(char) * (len_argv + 1))))
				return (1);
			ft_memcpy(g_envp[x], envp[x], len_argv);
			g_envp[x][len_argv] = '\0';
			x++;
		}
		g_envp[x] = NULL;
	}
	return (0);
}
