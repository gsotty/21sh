/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 12:15:45 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/11 10:55:49 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int		x;

	x = 0;
	if (tab == NULL || tab[0] == NULL)
		return ;
	while (tab[x] != NULL)
	{
		free(tab[x]);
		x++;
	}
	if (tab != NULL)
		free(tab);
}
