/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 13:07:19 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/03 13:26:03 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <limits.h>

typedef struct		s_split
{
	int				j;
	int				x;
}					t_split;

char				**ft_strsplit_space(char const *buf, char *c);
int					f_putchar(int c);

#endif
