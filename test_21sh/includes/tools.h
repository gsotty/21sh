/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 13:07:19 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/05 12:10:38 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <term.h>
# include <curses.h>

typedef struct		s_split
{
	int				j;
	int				x;
}					t_split;

char				**ft_strsplit_space(char const *buf, char *c);
int					f_putchar(int c);
int					prepare_term(void);
int					reset_term(void);

#endif
