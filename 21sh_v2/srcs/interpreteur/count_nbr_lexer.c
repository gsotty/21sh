/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_nbr_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 12:53:03 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/07 19:10:04 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		count_nbr_lexer(t_nbr_lexer *nbr, t_token *token)
{
	while (token != NULL)
	{
		if (nbr->to_sep == 0)
			nbr->to_sep = 1;
		else if (token->type == _SEP)
			nbr->to_sep++;
		else if (token->type == _PIPE)
			nbr->to_pipe++;
		else if (token->type == _APPROUT)
			nbr->to_approut++;
		else if (token->type == _HEREDOC)
			nbr->to_heredoc++;
		else if (token->type == _ROUT)
			nbr->to_rout++;
		else if (token->type == _RINT)
			nbr->to_rint++;
		else if (token->type == _ROUTERR)
			nbr->to_routerr++;
		else if (token->type == _DUP_INPUT)
			nbr->to_dup_input++;
		else if (token->type == _DUP_OUTPUT)
			nbr->to_dup_output++;
		token = token->next;
	}
	nbr->to_redir = (nbr->to_approut + nbr->to_heredoc + nbr->to_rout +
			nbr->to_rint + nbr->to_routerr + nbr->to_dup_input +
			nbr->to_dup_output);
	return (0);
}
