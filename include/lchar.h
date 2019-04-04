/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lchar.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:32:36 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 16:32:47 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCHAR_H
# define LCHAR_H

typedef struct		s_lchar
{
	int				len;
	char			*c;
	int				*type;
}					t_lchar;

t_lchar				*ft_lchardup(t_lchar *dest, t_lchar *srs, int n);
t_lchar				*ft_lcharndup(t_lchar *src, int start, int n);
int					ft_addtype(t_lchar *buf, int start, int end);
t_lchar				*add_lchar(t_lchar *buf_start, t_lchar *buf_add);
t_lchar				**ft_lcharsplit(t_lchar *buf, char **token);

#endif
