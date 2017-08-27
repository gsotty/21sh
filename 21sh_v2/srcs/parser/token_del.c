/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 11:08:47 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/27 11:09:02 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void	token_del(t_token **alst)
{
	t_token		*tmp;

	if (alst == NULL)
		return ;
	while (*alst)
	{
		tmp = (*alst)->next;
		free((*alst)->str);
		free(*alst);
		*alst = tmp;
	}
	*alst = NULL;
}
