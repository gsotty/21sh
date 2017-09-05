/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 11:44:39 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/30 11:45:58 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static char		*ft_print_type_2(int x)
{
	if (x == _DGREAT)
		return ("_DGREAT");
	else if (x == _DUP_OUTPUT)
		return ("_DUP_OUTPUT");
	else if (x == _DUP_INPUT)
		return ("_DUP_INPUT");
	else if (x == _PIPE)
		return ("_PIPE");
	else if (x == _SEP)
		return ("_SEP");
	else if (x == _OR_IF)
		return ("_OR_IF");
	else if (x == _AND_IF)
		return ("_AND_IF");
	else if (x == _SPACE)
		return ("_SPACE");
	return (0);
}

char			*ft_print_type(int x)
{
	if (x == _WORD)
		return ("_WORD");
	else if (x == _ASSIGNEMENT_WORD)
		return ("_ASSIGNEMENT_WORD");
	else if (x == _NAME)
		return ("_NAME");
	else if (x == _NEWLINE)
		return ("_NEWLINE");
	else if (x == _IO_NUMBER)
		return ("_IO_NUMBER");
	else if (x == _LESS)
		return ("_LESS");
	else if (x == _REDIR)
		return ("_REDIR");
	else if (x == _DLESS)
		return ("_DLESS");
	else
		return (ft_print_type_2(x));
	return (NULL);
}
