/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:42:07 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 18:41:27 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vingt_et_un_sh.h"
#include "../include/lchar.h"
#include "../include/parser.h"
#include "../include/envp.h"
#include <stdio.h>

int				ft_strmatch(char *str1, char *str2)
{
	int		x;

	x = 0;
	while (str1[x] == str2[x] && str1[x] != '\0' && str2[x] != '\0')
		x++;
	if (str1[x] == '\0' && str2[x] == '\0')
		return (1);
	return (0);
}

t_history		*add_new_history(t_history *history, t_lchar *buf)
{
	t_history	*tmp_history;

	if (ft_strmatch(history->buf[history->len]->c, buf->c) == 0)
	{
		if ((tmp_history = ft_memalloc(sizeof(t_history) + 1)) == NULL)
			return (NULL);
		ft_historycpy(history, tmp_history, 1);
		ft_freehistory(history);
		ft_lchardup(tmp_history->buf[tmp_history->len], buf, 0);
		ft_historycpy(tmp_history, history, 0);
		ft_freehistory(tmp_history);
	}
	return (history);
}

t_lchar			*while_main(int type, t_history *history)
{
	t_lchar		*buf;
	t_history	history_cpy;

	ft_signal(SIGINT, SA_SIGINFO);
	if ((ft_historycpy(history, &history_cpy, 1)) == NULL)
		return (NULL);
	history_cpy.pos_buf = history_cpy.len;
	buf = line_edition(type, &history_cpy);
	ft_freehistory(&history_cpy);
	return (buf);
}

int				ft_loop_for_line(t_history *history, t_envp *my_envp)
{
	t_lchar		*buf;

	if ((buf = while_main(0, history)) == NULL)
		return (1);
	if (buf->len > 0)
	{
		if (ft_strmatch("exit\n", buf->c) == 1 ||
					(buf->type[0] == _EOT && buf->len == 1))
		{
			free(buf->c);
			free(buf->type);
			free(buf);
			return (1);
		}
		parser(buf, history, my_envp);
		if ((add_new_history(history, buf)) == NULL)
			return (2);
	}
	free(buf->c);
	free(buf->type);
	free(buf);
	return (0);
}

int				main(int argc, char **argv, char **envp)
{
	int			ret;
	t_envp		my_envp;
	t_history	history;

	(void)argc;
	(void)argv;
	if ((creat_envp(envp, &my_envp)) == 1)
		return (1);
	if (inport_history(&history) == 1)
		return (1);
	while (1)
	{
		ret = ft_loop_for_line(&history, &my_envp);
		if (ret == 1)
			break ;
		else if (ret == 2)
			return (1);
	}
	if (export_history(&history) == 1)
		return (1);
	if (free_envp(&my_envp) == 1)
		return (1);
	return (0);
}
