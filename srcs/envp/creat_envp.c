/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:22:39 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 14:23:24 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/envp.h"
#include "../../include/vingt_et_un_sh.h"

int		len_tab(char **tab)
{
	int		x;

	x = 0;
	while (tab[x] != NULL)
		x++;
	return (x);
}

int		creat_envp(char **envp, t_envp *my_envp)
{
	int		len_arg;
	int		cont;

	my_envp->envp = NULL;
	if (envp != NULL)
	{
		my_envp->len = len_tab(envp);
		my_envp->len_malloc = my_envp->len;
		if ((my_envp->envp = ft_memalloc(sizeof(char *) *
						(my_envp->len + 1))) == NULL)
			return (1);
		cont = 0;
		while (envp[cont] != NULL)
		{
			len_arg = ft_strlen(envp[cont]);
			if ((my_envp->envp[cont] = ft_memalloc(sizeof(char) *
							(len_arg + 1))) == NULL)
				return (1);
			ft_memcpy(my_envp->envp[cont], envp[cont], len_arg);
			my_envp->envp[cont][len_arg] = '\0';
			cont++;
		}
		my_envp->envp[cont] = NULL;
	}
	return (0);
}
