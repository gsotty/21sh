/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:43:31 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 15:48:07 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/envp.h"

int				free_envp(t_envp *my_envp)
{
	int		x;

	x = 0;
	while (my_envp->envp[x] != NULL)
	{
		free(my_envp->envp[x]);
		x++;
	}
	free(my_envp->envp);
	return (0);
}
