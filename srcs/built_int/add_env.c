/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:34:40 by gsotty            #+#    #+#             */
/*   Updated: 2019/01/16 13:17:29 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_int.h"
#include <stdio.h>

static char	**envp_null(char *name_var, char *data_var)
{
	char	**envp;
	int		len_name;
	int		len_data;

	if ((envp = ft_memalloc(sizeof(char *) + 1)) == NULL)
		return (NULL);
	len_name = ft_strlen(name_var);
	if (data_var != NULL)
		len_data = ft_strlen(data_var);
	else
		len_data = 0;
	if((envp[0] = ft_memalloc((sizeof(char *) * (len_name + len_data + 1))
					+ 1)) == NULL)
		return (NULL);
	ft_memcpy(envp[0], name_var, len_name);
	ft_memcpy(envp[0] + len_name, "=", 1);
	ft_memcpy(envp[0] + len_name + 1, data_var, len_data);
	envp[0][len_name + len_data + 1] = '\0';
	return (envp);
}

int			envp_no_null(char *name_var, char *data_var, t_envp *my_envp)
{
	int		x;
	char	*p;
	int		len_name;
	int		len_data;

	x = 0;
	while (my_envp->envp[x] != NULL)
	{
		p = ft_strchr(my_envp->envp[x], '=');
		if (ft_memcmp(my_envp->envp[x], name_var, p - my_envp->envp[x]) == 0)
			break ;
		x++;
	}
	if (my_envp->envp[x] == NULL)
	{
		remalloc_env(my_envp, 1);
		len_name = ft_strlen(name_var);
		if (data_var != NULL)
			len_data = ft_strlen(data_var);
		else
			len_data = 0;
		if((my_envp->envp[x] = ft_memalloc((sizeof(char *) * (len_name + len_data + 1))
						+ 1)) == NULL)
			return (1);
		ft_memcpy(my_envp->envp[x], name_var, len_name);
		ft_memcpy(my_envp->envp[x] + len_name, "=", 1);
		ft_memcpy(my_envp->envp[x] + len_name + 1, data_var, len_data);
		my_envp->envp[x][len_name + len_data + 1] = '\0';
	}
	else
	{
		free(my_envp->envp[x]);
		len_name = ft_strlen(name_var);
		if (data_var != NULL)
			len_data = ft_strlen(data_var);
		else
			len_data = 0;
		if((my_envp->envp[x] = ft_memalloc((sizeof(char *) * (len_name + len_data + 1))
						+ 1)) == NULL)
			return (1);
		ft_memcpy(my_envp->envp[x], name_var, len_name);
		ft_memcpy(my_envp->envp[x] + len_name, "=", 1);
		ft_memcpy(my_envp->envp[x] + len_name + 1, data_var, len_data);
		my_envp->envp[x][len_name + len_data + 1] = '\0';
	}
	return (0);
}

int			add_env(char *name_var, char *data_var, t_envp *my_envp)
{
	if (my_envp->envp == NULL)
	{
		if ((my_envp->envp = envp_null(name_var, data_var)) == NULL)
			return (1);
	}
	else
	{
		if (envp_no_null(name_var, data_var, my_envp) == 1)
			return (1);
	}
	return (0);
}
