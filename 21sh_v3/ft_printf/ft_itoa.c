/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:31:39 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:31:47 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nb_len(int n)
{
	int		len;

	len = 1;
	if (n < 0)
		len++;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	int		len;
	char	*str_nb;

	len = nb_len(n);
	str_nb = ft_strnew(len);
	if (!str_nb)
		return (NULL);
	if (n < 0)
		str_nb[0] = '-';
	while (len > 0 && str_nb[len - 1] != '-')
	{
		if (n < 0)
			str_nb[--len] = -(n % 10) + '0';
		else
			str_nb[--len] = (n % 10) + '0';
		n = n / 10;
	}
	return (str_nb);
}
