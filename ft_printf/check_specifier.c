/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_specifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:29:12 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/28 10:40:01 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_specifier_4(t_struc *struc, const char *str, int z,
		int *verif)
{
	if (str[z] == 'X')
	{
		struc->specifier.xm = 1;
		*verif = 1;
	}
	else if (str[z] == 'p')
	{
		struc->specifier.p = 1;
		*verif = 1;
	}
	else if (str[z] == '%')
	{
		struc->specifier.pourcent = 1;
		*verif = 1;
	}
	else if ((struc->specifier.no_specifier = ft_verif_char(str[z])) == 1)
	{
		struc->specifier.c_str = str[z];
		*verif = 1;
	}
	return (z);
}

static int	check_specifier_3(t_struc *struc, const char *str, int z,
		int *verif)
{
	if (str[z] == 'U')
	{
		struc->specifier.um = 1;
		*verif = 1;
	}
	else if (str[z] == 'O')
	{
		struc->specifier.om = 1;
		*verif = 1;
	}
	else if (str[z] == 'x')
	{
		struc->specifier.x = 1;
		*verif = 1;
	}
	z = check_specifier_4(struc, str, z, verif);
	return (z);
}

static int	check_specifier_2(t_struc *struc, const char *str, int z,
		int *verif)
{
	if (str[z] == 's')
	{
		struc->specifier.s = 1;
		*verif = 1;
	}
	else if (str[z] == 'S')
	{
		struc->specifier.sm = 1;
		*verif = 1;
	}
	else if (str[z] == 'u')
	{
		struc->specifier.u = 1;
		*verif = 1;
	}
	z = check_specifier_3(struc, str, z, verif);
	return (z);
}

static int	check_specifier_1(t_struc *struc, const char *str, int z,
		int *verif)
{
	if (str[z] == 'd')
	{
		struc->specifier.d = 1;
		*verif = 1;
	}
	else if (str[z] == 'D')
	{
		struc->specifier.dm = 1;
		*verif = 1;
	}
	else if (str[z] == 'i')
	{
		struc->specifier.i = 1;
		*verif = 1;
	}
	else if (str[z] == 'o')
	{
		struc->specifier.o = 1;
		*verif = 1;
	}
	z = check_specifier_2(struc, str, z, verif);
	return (z);
}

int			check_specifier(t_struc *struc, const char *str, int z)
{
	int		tmp_z;
	int		verif;

	verif = 0;
	tmp_z = z;
	while (str[z] != '\0')
	{
		if (str[z] == 'c')
		{
			struc->specifier.c = 1;
			verif = 1;
		}
		else if (str[z] == 'C')
		{
			struc->specifier.cm = 1;
			verif = 1;
		}
		z = check_specifier_1(struc, str, z, &verif);
		if (verif == 1)
			return (z);
		z++;
	}
	return (tmp_z - 1);
}
