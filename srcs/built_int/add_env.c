/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:34:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/03 10:18:41 by gsotty           ###   ########.fr       */
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

void		envp_no_null(char *name_var, char *data_var, char ***envp)
{
	int		x;
	int		y;
	char	*p;
	int		len_name;
	int		len_data;

	x = 0;
	while (*envp[x] != NULL)
	{
		p = ft_strchr(*envp[x], '=');
		if (ft_memcmp(*envp[x], name_var, p - *envp[x]) == 0)
			break ;
		x++;
	}
	if (*envp[x] == NULL)
	{
		y = 0;
		while (*envp[y] != NULL)
		{
			printf("envp[%d] = {%s}\n", y, *envp[y]);
			y++;
		}
		remalloc_env(envp, 1);
		y = 0;
		while (envp[y] != NULL)
		{
			printf("envp[%d] = {%s}\n", y, *envp[y]);
			y++;
		}
		len_name = ft_strlen(name_var);
		if (data_var != NULL)
			len_data = ft_strlen(data_var);
		else
			len_data = 0;
		if((*envp[x] = ft_memalloc((sizeof(char *) * (len_name + len_data + 1))
						+ 1)) == NULL)
			return ;
		ft_memcpy(*envp[x], name_var, len_name);
		ft_memcpy(*envp[x] + len_name, "=", 1);
		ft_memcpy(*envp[x] + len_name + 1, data_var, len_data);
		*envp[x][len_name + len_data + 1] = '\0';
	}
	else
	{
		free(*envp[x]);
		len_name = ft_strlen(name_var);
		if (data_var != NULL)
			len_data = ft_strlen(data_var);
		else
			len_data = 0;
		if((*envp[x] = ft_memalloc((sizeof(char *) * (len_name + len_data + 1))
						+ 1)) == NULL)
			return ;
		ft_memcpy(*envp[x], name_var, len_name);
		ft_memcpy(*envp[x] + len_name, "=", 1);
		ft_memcpy(*envp[x] + len_name + 1, data_var, len_data);
		*envp[x][len_name + len_data + 1] = '\0';
	}
	return ;
}

void		add_env(char *name_var, char *data_var, char ***envp)
{
	if (*envp == NULL)
		*envp = envp_null(name_var, data_var);
	else
		envp_no_null(name_var, data_var, envp);
	return ;
}
