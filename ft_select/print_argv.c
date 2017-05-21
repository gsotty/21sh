/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 14:40:29 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/20 12:41:48 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_select.h"

void			print_sur(t_buf *buf, int pos, int len)
{
	char	*tmp;

	if ((tmp = ft_memalloc(sizeof(char) * (8 + len))) == NULL)
		ft_exit(-1, buf, NULL);
	ft_memcpy(tmp, "\033[7m", 4);
	ft_memcpy(tmp + 4, buf->tab_arg[pos], len);
	ft_memcpy(tmp + 4 + len, "\033[0m", 4);
	write(0, tmp, 8 + len);
	free(tmp);
}

void			print_sou(t_buf *buf, int pos, int len)
{
	char	*tmp;

	if ((tmp = ft_memalloc(sizeof(char) * (8 + len))) == NULL)
		ft_exit(-1, buf, NULL);
	ft_memcpy(tmp, "\033[4m", 4);
	ft_memcpy(tmp + 4, buf->tab_arg[pos], len);
	ft_memcpy(tmp + 4 + len, "\033[0m", 4);
	write(0, tmp, 8 + len);
	free(tmp);
}

void			print_sur_et_sou(t_buf *buf, int pos, int len)
{
	char	*tmp;

	if ((tmp = ft_memalloc(sizeof(char) * (15 + len))) == NULL)
		ft_exit(-1, buf, NULL);
	ft_memcpy(tmp, "\033[37;4;5;7m", 11);
	ft_memcpy(tmp + 11, buf->tab_arg[pos], len);
	ft_memcpy(tmp + 11 + len, "\033[0m", 4);
	write(0, tmp, 15 + len);
	free(tmp);
}
