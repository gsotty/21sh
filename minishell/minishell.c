/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 10:31:31 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/03 08:48:40 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <stdio.h>

static char	*creat_buf(char *buf)
{
	int		x;
	int		ret;
	int		cont;
	char	c;

	x = 0;
	cont = 0;
	ft_memset(buf, '\0', MAX_CANON);
	while (((ret = read(0, &c, 1)) && c != '\n') && cont < MAX_CANON - 1)
	{
		buf[cont] = c;
		cont++;
	}
	if (ret == 0)
	{
		write(1, "\n", 1);
		exit(0);
	}
	buf[cont] = '\0';
	while ((buf[x] == ' ' || buf[x] == '\t') && buf[x] != '\0')
		x++;
	if (buf[x] == '\0')
		return (NULL);
	return (buf);
}

void		add_shlvl(void)
{
	char	*tmp;
	char	*p;
	int		n;

	if (g_envp == NULL || g_envp[0] == NULL)
		n = 2;
	else
	{
		n = 0;
		p = find_var_env("SHLVL");
		n = ft_atoi(p);
		n = n + 1;
	}
	tmp = ft_strjoin("=", ft_itoa(n));
	add_env(ft_strjoin("SHLVL", tmp));
	free(tmp);
}

void		while_minishell(int x)
{
	char	buf[MAX_CANON];

	print_prompt();
	if (creat_buf(buf) != NULL)
	{
		while ((buf[x] == ' ' || buf[x] == '\t') && buf[x] != '\0')
			x++;
		if (ft_strstr(buf, "exit") != NULL)
		{
			if (buf[4] == ' ' || buf[4] == '\t' || buf[4] == '\0')
			{
				free_tab(g_envp);
				exit(0);
			}
		}
		if (buf[0] != '\0')
			exe(buf);
	}
	return ;
}

int			minishell(char **envp_begin)
{
	g_envp = creat_env(envp_begin);
	while (1)
		while_minishell(0);
	free_tab(g_envp);
	return (0);
}
