/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_itoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:38:32 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:38:34 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_unsigned_itoa(unsigned int n)
{
	unsigned int	nbr;
	int				i;
	char			*tab;

	i = 2;
	nbr = n;
	while (nbr /= 10)
		i++;
	if ((tab = (char *)malloc(sizeof(char) * i)) == NULL)
		return (NULL);
	tab[--i] = '\0';
	while (i--)
	{
		tab[i] = ((n % 10) + '0');
		n = n / 10;
	}
	return (tab);
}
