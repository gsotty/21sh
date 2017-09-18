/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_lchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 09:17:12 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/18 15:44:52 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

t_lchar		*ft_strdup_lchar(const t_lchar *s)
{
	t_lchar		*ret;
	int			i;

	if (!(ret = ft_memalloc(sizeof(t_lchar) * (ft_strlen_lchar(s) + 1))))
		return (NULL);
	i = 0;
	while (s[i].c)
	{
		ret[i].c = s[i].c;
		ret[i].type = s[i].type;
		i++;
	}
	ret[i].c = '\0';
	return (ret);
}
