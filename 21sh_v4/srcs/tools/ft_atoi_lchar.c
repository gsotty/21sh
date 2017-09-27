/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_lchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 14:44:01 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/27 14:45:17 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		ft_atoi_lchar(t_lchar *str)
{
	int		i;
	int		ret_atoi;
	int		sign;

	i = 0;
	sign = 0;
	ret_atoi = 0;
	while (str[i].c == ' ' || str[i].c == '\n' || str[i].c == '\t' ||
			str[i].c == '\v' || str[i].c == '\f' || str[i].c == '\r')
		i++;
	if (str[i].c == '-' || str[i].c == '+')
	{
		if (str[i].c == '-')
			sign = -1;
		i++;
	}
	while (str[i].c >= '0' && str[i].c <= '9')
	{
		ret_atoi *= 10;
		ret_atoi += (str[i].c - 48);
		i++;
	}
	if (sign < 0)
		ret_atoi *= -1;
	return (ret_atoi);
}
