/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 11:44:39 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/16 11:52:08 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static char		*ft_print_type_2(int x)
{
	if (x == _FILE_NAME)
		return ("_FILE_NAME");
	else if (x == _FD)
		return ("\033[35m_FD\033[0m");
	else if (x == _HEREDOC)
		return ("_HEREDOC");
	else if (x == _APPROUT)
		return ("_APPROUT");
	else if (x == _PIPE)
		return ("\033[34m_PIPE\033[0m");
	else if (x == _SEP)
		return ("\033[31m_SEP\033[0m");
	else if (x == _TIRET)
		return ("_TIRET");
	else if (x == _OR)
		return ("_OR");
	else if (x == _AND)
		return ("_AND");
	else if (x == _DIGIT)
		return ("\033[35m_DIGIT\033[0m");
	else if (x == _CMD)
		return ("\033[1;32m_CMD\033[0m");
	else if (x == _ARGV)
		return ("\033[32m_ARGV\033[0m");
	else if (x == _NEW_LINE)
		return ("_NEW_LINE");
	return (ft_itoa(x));
}

char			*ft_print_type(int x)
{
	if (x == _SPACE)
		return ("\033[36m_SPACE\033[0m");
	else if (x == _WORD)
		return ("_WORD");
	else if (x == _DUP_ROUT)
		return ("_DUP_ROUT");
	else if (x == _DUP_RINT)
		return ("_DUP_RINT");
	else if (x == _ROUTERR)
		return ("_ROUTERR");
	else if (x == _ROUT)
		return ("\033[33m_ROUT\033[0m");
	else if (x == _RINT)
		return ("\033[33m_RINT\033[0m");
	else
		return (ft_print_type_2(x));
	return (NULL);
}
