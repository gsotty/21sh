/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 11:32:38 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/31 11:24:25 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

static int		only_space(char *cmd)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (cmd[x] != '\0')
	{
		if (cmd[x] == ' ')
			y++;
		x++;
	}
	if (y - x == 0)
		return (1);
	else
		return (0);
}

static int		is_type_2(char *cmd)
{
	if (ft_strstr(cmd, "||") != NULL)
		return (_OR_IF);
	else if (ft_strstr(cmd, "&&") != NULL)
		return (_AND_IF);
	else if (ft_strstr(cmd, "|") != NULL)
		return (_PIPE);
	else if (ft_strstr(cmd, ";") != NULL)
		return (_SEP);
	else if (only_space(cmd) == 1)
		return (_SPACE);
	else if (cmd[0] == '\0')
		return (_SPACE);
	return (_WORD);
}

int				is_type(char *cmd)
{
	if (cmd == NULL)
		return (_SPACE);
	else if (ft_strstr(cmd, "<<") != NULL)
		return (_DLESS);
	else if (ft_strstr(cmd, ">>") != NULL)
		return (_DGREAT);
	else if (ft_strstr(cmd, "<&") != NULL)
		return (_DUP_OUTPUT);
	else if (ft_strstr(cmd, ">&") != NULL)
		return (_DUP_INPUT);
	else if (ft_strstr(cmd, "<") != NULL)
		return (_LESS);
	else if (ft_strstr(cmd, ">") != NULL)
		return (_GREAT);
	else
		return (is_type_2(cmd));
}
