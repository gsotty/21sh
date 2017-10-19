/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:46:09 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/17 17:42:05 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*ret;
	int		i;

	if (!(ret = (char *)malloc(sizeof(*ret) * ft_strlen(s) + 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
