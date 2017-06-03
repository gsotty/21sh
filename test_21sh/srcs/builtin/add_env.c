/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:34:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/03 15:29:04 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static int	find_var(char *tmp_data, char ***envp)
{
	int		x;
	char	*p;
	char	*tmp_env;

	x = 0;
	if (*envp == NULL || *envp[0] == NULL)
		return (0);
	while (envp[0][x] != NULL)
	{
		tmp_env = ft_strdup(envp[0][x]);
		p = ft_strchr(tmp_env, '=');
		*p = 0;
		if (ft_strcmp(tmp_env, tmp_data) == 0)
		{
			free(tmp_env);
			break ;
		}
		free(tmp_env);
		x++;
	}
	return (x);
}

static void	envp_null(char *data, char ***envp)
{
	if (*envp == NULL)
	{
		if ((*envp = ft_memalloc(sizeof(char *) * 2)) == NULL)
			return ;
		envp[0][0] = ft_strdup(data);
	}
	else
		envp[0][0] = ft_strdup(data);
	return ;
}

void		envp_no_null(char *data, char ***envp)
{
	int		x;
	char	*p;
	char	*tmp_data;

	if ((tmp_data = ft_strdup(data)) == NULL)
		return ;
	p = ft_strchr(tmp_data, '=');
	*p = '\0';
	x = find_var(tmp_data, envp);
	if (envp[0][x] == NULL)
	{
		remalloc_env(x, x + 1, envp);
		envp[0][x] = ft_strdup(data);
	}
	else
	{
		free(envp[0][x]);
		envp[0][x] = ft_strdup(data);
	}
	free(tmp_data);
	return ;
}

void		add_env(char *data, char ***envp)
{
	if (*envp == NULL || *envp[0] == NULL)
	{
		envp_null(data, envp);
		return ;
	}
	else
		envp_no_null(data, envp);
	return ;
}
