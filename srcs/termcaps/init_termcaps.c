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

static int		prepare_term_tgetent(char *name_term)
{
	int			succes;

	succes = tgetent(NULL, name_term);
	if (succes < 0)
	{
		write(2, "Could not access the termcap data base.\n", 40);
		return (1);
	}
	if (succes == 0)
	{
		write(2, "Terminal type \"", 15);
		write(2, name_term, ft_strlen(name_term));
		write(2, "\" is not defined.\n", 18);
		return (1);
	}
	return (0);
}

static int		modif_prepare_term(struct termios *term)
{
	if (tcgetattr(0, term) == -1)
		return (1);
	term->c_lflag &= ~ICANON;
	term->c_lflag &= ~ECHO;
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return (1);
	return (0);
}

int				init_termcaps(void)
{
	struct termios		term;
	char				*name_term;
	int					is_malloc;

	is_malloc = 0;
	ft_memset(&term, 0, sizeof(term));
//	if ((name_term = getenv("TERM")) == NULL)
//	{
		if ((name_term = ft_memalloc(sizeof(char) * 5)) == NULL)
			return (1);
		ft_memcpy(name_term, "vt100", 5);
		name_term[5] = '\0';
		is_malloc = 1;
//	}
	if (prepare_term_tgetent(name_term) != 0)
		return (1);
	if (modif_prepare_term(&term) != 0)
		return (1);
	if (is_malloc == 1)
		free(name_term);
	return (0);
}
