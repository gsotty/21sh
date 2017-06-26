/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_term.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 17:02:31 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/25 17:05:54 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

#ifdef unix
static char term_buffer[2048];
#else
#define term_buffer 0
#endif

void		init_terminal_data ()
{
	char	*termtype = getenv ("TERM");
	int		success;

	if (termtype == 0)
	{
		printf("Specify a terminal type with `setenv TERM <yourtype>'.\n");
		exit(0);
	}
	success = tgetent (term_buffer, termtype);
	if (success < 0)
	{
		printf("Could not access the termcap data base.\n");
		exit(0);
	}
	if (success == 0)
	{
		printf("Terminal type `%s' is not defined.\n", termtype);
		exit(0);
	}
}
