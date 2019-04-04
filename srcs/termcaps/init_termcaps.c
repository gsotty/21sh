/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:51:01 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 14:06:20 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_termcaps.h"
#include <stdio.h>
#include <curses.h>
#include <term.h>

static void		ft_add_value_key(t_key *key, t_sequence *sequence)
{
	key[0].str = sequence->buffer;
	key[0].str[0] = 10;
	key[0].str[1] = '\0';
	sequence->buffer = &key[0].str[2];
	key[1].str = sequence->buffer;
	key[1].str[0] = 4;
	key[1].str[1] = '\0';
	sequence->buffer = &key[1].str[2];
	key[2].str = tgetstr("kl", &sequence->buffer);
	key[3].str = tgetstr("kr", &sequence->buffer);
	key[4].str = tgetstr("ku", &sequence->buffer);
	key[5].str = tgetstr("kd", &sequence->buffer);
	key[6].str = tgetstr("kh", &sequence->buffer);
	key[7].str = tgetstr("kH", &sequence->buffer);
	if (key[7].str == NULL)
	{
		key[7].str = sequence->buffer;
		key[7].str[0] = 27;
		key[7].str[1] = 79;
		key[7].str[2] = 70;
		key[7].str[3] = '\0';
		sequence->buffer = &key[7].str[4];
	}
	key[8].str = tgetstr("kb", &sequence->buffer);
	key[9].str = tgetstr("ka", &sequence->buffer);
	key[10].str = tgetstr("kt", &sequence->buffer);
	key[11].str = tgetstr("kC", &sequence->buffer);
	key[12].str = tgetstr("kD", &sequence->buffer);
	key[13].str = tgetstr("kL", &sequence->buffer);
	key[14].str = tgetstr("kM", &sequence->buffer);
	key[15].str = tgetstr("kE", &sequence->buffer);
	key[16].str = tgetstr("kS", &sequence->buffer);
	key[17].str = tgetstr("kI", &sequence->buffer);
	key[18].str = tgetstr("kA", &sequence->buffer);
	key[19].str = tgetstr("kN", &sequence->buffer);
	key[20].str = tgetstr("kP", &sequence->buffer);
	key[21].str = tgetstr("kF", &sequence->buffer);
	key[22].str = tgetstr("kT", &sequence->buffer);
	key[23].str = tgetstr("ko", &sequence->buffer);
	fprintf(stderr, "ko= [%s]\n", key[23].str);
}

static int		ft_add_value_sequence(int len_term, t_key *key,
		t_sequence *sequence)
{
	if ((sequence->buffer = ft_memalloc(sizeof(char) * len_term)) == NULL)
		return (1);
	sequence->start_buf = sequence->buffer;
	sequence->reset = tgetstr("rs", &sequence->buffer);
	sequence->start = tgetstr("ks", &sequence->buffer);
	sequence->end = tgetstr("ke", &sequence->buffer);
	sequence->left_cursor = tgetstr("le", &sequence->buffer);
	sequence->right_cursor = tgetstr("nd", &sequence->buffer);
	sequence->up_scroll = tgetstr("sf", &sequence->buffer);
	sequence->down_scroll = tgetstr("sr", &sequence->buffer);
	sequence->go_start_line = tgetstr("cr", &sequence->buffer);
	sequence->clear_rest_screen = tgetstr("cd", &sequence->buffer);
	tputs(sequence->reset, 0, f_putchar);
	tputs(sequence->start, 0, f_putchar);
	ft_add_value_key(key, sequence);
	return (0);
}

static void		ft_change_var_term(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return ;
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return ;
}

static void		ft_error_getenv(void)
{
	write(2, "Specify a terminal type with `setenv TERM <yourtype>'.\n", 55);
	exit(0);
}

int				ft_init_termcaps(t_key *key, t_sequence *sequence)
{
	int		success;
	char	*termtype;

	if ((termtype = getenv("TERM")) == NULL)
		ft_error_getenv();
	fprintf(stderr, "termtype = [%s]\n", termtype);
	success = tgetent(NULL, termtype);
	if (success < 0)
	{
		write(2, "Could not access the termcap data base.\n", 40);
		return (1);
	}
	else if (success == 0)
	{
		write(2, "Terminal type \"", 15);
		write(2, termtype, ft_strlen(termtype));
		write(2, "\" is not defined.\n", 18);
		return (1);
	}
	ft_change_var_term();
	if ((ft_add_value_sequence(4096 + 4, key, sequence)) == 1)
		return (1);
	return (0);
}
