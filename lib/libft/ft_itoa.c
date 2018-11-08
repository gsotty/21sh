/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 09:58:58 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/11 17:12:56 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_signe(int *n, int *signe)
{
	if (*n < 0)
	{
		*n *= -1;
		*signe = 1;
	}
}

char		*ft_itoa(int n)
{
	int		nbr;
	int		i;
	int		signe;
	char	*tab;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = 2;
	nbr = n;
	signe = 0;
	ft_signe(&n, &signe);
	while (nbr /= 10)
		i++;
	i += signe;
	if ((tab = (char *)malloc(sizeof(char) * i)) == NULL)
		return (NULL);
	tab[--i] = '\0';
	while (i--)
	{
		tab[i] = ((n % 10) + '0');
		n = n / 10;
	}
	if (signe)
		tab[0] = '-';
	return (tab);
}
