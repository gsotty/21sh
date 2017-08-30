/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 11:10:50 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/30 11:43:25 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_token	*token_new(void const *content, size_t content_size, int nbr_token)
{
	t_token	*new;

	if ((new = (t_token *)malloc(sizeof(*new))) == NULL)
		return (0);
	new->type = nbr_token;
	if (content != NULL)
	{
		if ((new->str = malloc(sizeof(*content) * (content_size + 1))) == NULL)
			return (0);
		ft_memcpy_modif(new->str, content, content_size);
		new->str[content_size] = '\0';
		new->type = is_type(new->str);
	}
	else
	{
		new->str = NULL;
	}
	new->next = NULL;
	return (new);
}
