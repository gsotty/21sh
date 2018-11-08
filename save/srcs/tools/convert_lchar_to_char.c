/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_lchar_to_char.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 15:11:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/10/04 17:50:58 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

char	*convert_lchar_to_char(t_lchar *lchar)
{
	int		len;
	int		x;
	char	*str;

	x = 0;
	len = ft_strlen_lchar(lchar);
	if ((str = ft_memalloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (lchar[x].c != '\0')
	{
		str[x] = lchar[x].c;
		x++;
	}
	str[x] = '\0';
	return (str);
}
