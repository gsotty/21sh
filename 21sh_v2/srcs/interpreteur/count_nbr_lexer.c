/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_nbr_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 12:53:03 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/01 12:54:00 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		count_nbr_lexer(t_nbr_lexer *nbr, t_token *token)
{
	while (token != NULL)
	{
		if (nbr->_sep == 0)
			nbr->_sep = 1;
		else if (token->type == _SEP)
			nbr->_sep++;
		else if (token->type == _OR_IF)
			nbr->_or++;
		else if (token->type == _AND_IF)
			nbr->_and++;
		else if (token->type == _PIPE)
			nbr->_pipe++;
		else if (token->type == _DGREAT)
			nbr->_dgreat++;
		else if (token->type == _DLESS)
			nbr->_dless++;
		else if (token->type == _GREAT)
			nbr->_great++;
		else if (token->type == _LESS)
			nbr->_less++;
		token = token->next;
	}
	return (0);
}
