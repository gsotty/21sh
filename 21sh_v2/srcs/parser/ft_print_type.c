/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 11:44:39 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/06 13:58:55 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static char		*ft_print_type_2(int x)
{
	if (x == _FILE)
		return ("_FILE");
	else if (x == _FD)
		return ("_FD");
	else if (x == _HEREDOC)
		return ("_HEREDOC");
	else if (x == _APPROUT)
		return ("_APPROUT");
	else if (x == _PIPE)
		return ("_PIPE");
	else if (x == _SEP)
		return ("_SEP");
	return (0);
}

char			*ft_print_type(int x)
{
	if (x == _SPACE)
		return ("_SPACE");
	else if (x == _WORD)
		return ("_WORD");
	else if (x == _DUP_OUTPUT)
		return ("_DUP_OUTPUT");
	else if (x == _DUP_INPUT)
		return ("_DUP_INPUT");
	else if (x == _ROUTERR)
		return ("_ROUTERR");
	else if (x == _ROUT)
		return ("_ROUT");
	else if (x == _RINT)
		return ("_RINT");
	else
		return (ft_print_type_2(x));
	return (NULL);
}
