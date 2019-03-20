/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:51:01 by gsotty            #+#    #+#             */
/*   Updated: 2019/01/16 18:27:55 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_termcaps.h"
#include <stdio.h>

int				init_termcaps(void)
{
	char			*termtype = getenv("TERM");
	int				success;
	char			*name_term;
	struct termios	term;
//	char			term_buffer[4096];
	char			*term_buffer;

	if (termtype == NULL)
	{
		write(2, "Specify a terminal type with `setenv TERM <yourtype>'.\n", 55);
		exit(0);
	}
	if ((term_buffer = ft_memalloc(sizeof(char) * 4096)) == NULL)
		return (1);
	success = tgetent (term_buffer, termtype);
	if (success < 0)
	{
		write(2, "Could not access the termcap data base.\n", 40);
		return (1);
	}
	if (success == 0)
	{
		write(2, "Terminal type \"", 15);
		write(2, name_term, ft_strlen(name_term));
		write(2, "\" is not defined.\n", 18);
		return (1);
	}
	if (tcgetattr(0, &term) == -1)
		return (1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
//	free(term_buffer);
//	if (termtype != NULL)
//		free(termtype);
	return (0);
}
