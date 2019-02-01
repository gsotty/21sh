#include "../include/vingt_et_un_sh.h"
#include "../include/lchar.h"

int				ft_history_copy(t_history *history_first, t_history *history_copy)
{
	int			count;

	history_copy->len_buf = history_first->len_buf + 1;
	history_copy->malloc_buf = history_first->len_buf + 1;
	history_copy->pos_buf = history_first->pos_buf + 1;
	if ((history_copy->len = ft_memalloc(sizeof(int) * (history_copy->malloc_buf + 1))) == NULL)
		return (1);
	if ((history_copy->len_malloc = ft_memalloc(sizeof(int) * (history_copy->malloc_buf + 1))) == NULL)
		return (1);
	if ((history_copy->pos = ft_memalloc(sizeof(int) * (history_copy->malloc_buf + 1))) == NULL)
		return (1);
	if ((history_copy->buf = ft_memalloc(sizeof(char *) * (history_copy->malloc_buf + 1))) == NULL)
		return (1);
	count = 0;
	while (count <= history_first->len_buf)
	{
		history_copy->len[count] = history_first->len[count];
		history_copy->len_malloc[count] = history_first->len_malloc[count];
		history_copy->pos[count] = history_first->pos[count];
		if ((history_copy->buf[count] = ft_memalloc(sizeof(char) * (history_copy->len_malloc[count] + 1))) == NULL)
			return (1);
		ft_memcpy(history_copy->buf[count], history_first->buf[count], history_first->len[count]);
		count++;
	}
	history_copy->len[count] = 0;
	history_copy->len_malloc[count] = 0;
	history_copy->pos[count] = 0;
	history_copy->buf[count] = NULL;
	return (0);
}

int				add_new_history(t_history *history_first, t_history *history_copy)
{
	int		count;
	int		*tmp_len;
	int		*tmp_len_malloc;
	int		*tmp_pos;
	char	**tmp_buf;

	if (history_copy->len_buf >= history_first->malloc_buf)
	{
		history_first->malloc_buf += REMALLOC_HISTORY;
		if ((tmp_len = ft_memalloc(sizeof(int) * (history_first->malloc_buf + 1))) == NULL)
			return (1);
		if ((tmp_len_malloc = ft_memalloc(sizeof(int) * (history_first->malloc_buf + 1))) == NULL)
			return (1);
		if ((tmp_pos = ft_memalloc(sizeof(int) * (history_first->malloc_buf + 1))) == NULL)
			return (1);
		if ((tmp_buf = ft_memalloc(sizeof(char *) * (history_first->malloc_buf + 1))) == NULL)
			return (1);
		count = 0;
		while (count <= history_first->len_buf)
		{
			tmp_len[count] = history_first->len[count];
			tmp_len_malloc[count] = history_first->len_malloc[count];
			tmp_pos[count] = history_first->pos[count];
			if ((tmp_buf[count] = ft_memalloc(sizeof(char) * (history_first->len_malloc[count] + 1))) == NULL)
				return (1);
			ft_memcpy(tmp_buf[count], history_first->buf[count], history_first->len[count]);
			tmp_buf[count][history_first->len[count]] = '\0';
			free(history_first->buf[count]);
			count++;
		}
		tmp_len[history_copy->len_buf] = history_copy->len[history_copy->pos_buf];
		tmp_len_malloc[history_copy->len_buf] = history_copy->len_malloc[history_copy->pos_buf];
		tmp_pos[history_copy->len_buf] = history_copy->pos[history_copy->pos_buf];
		if ((tmp_buf[history_copy->len_buf] = ft_memalloc((sizeof(char) *
							history_copy->len_malloc[history_copy->pos_buf]) + 1)) == NULL)
			return (1);
		ft_memcpy(tmp_buf[history_copy->len_buf], history_copy->buf[history_copy->pos_buf], history_copy->len[history_copy->pos_buf]);
		tmp_buf[history_copy->len_buf][history_copy->len[history_copy->pos_buf]] = '\0';
		history_first->len_buf = history_copy->len_buf;
		count = 0;
		while (count <= history_copy->len_buf)
		{
			free(history_copy->buf[count]);
			count++;
		}
		free(history_copy->len);
		free(history_copy->len_malloc);
		free(history_copy->pos);
		free(history_copy->buf);
		free(history_first->len);
		free(history_first->len_malloc);
		free(history_first->pos);
		free(history_first->buf);
		history_first->len = tmp_len;
		history_first->len_malloc = tmp_len_malloc;
		history_first->pos = tmp_pos;
		history_first->buf = tmp_buf;
	}
	else
	{
		history_first->len_buf = history_copy->len_buf;
		history_first->len[history_first->len_buf] = history_copy->len[history_copy->pos_buf];
		history_first->len_malloc[history_first->len_buf] = history_copy->len_malloc[history_copy->pos_buf];
		history_first->pos[history_first->len_buf] = history_copy->pos[history_copy->pos_buf];
		free(history_first->buf[history_first->len_buf]);
		if ((history_first->buf[history_first->len_buf] = ft_memalloc(sizeof(char) *
						(history_copy->len_malloc[history_copy->pos_buf] + 1))) == NULL)
			return (1);
		ft_memcpy(history_first->buf[history_first->len_buf], history_copy->buf[history_copy->pos_buf],
				history_copy->len[history_copy->pos_buf]);
		history_first->buf[history_first->len_buf][history_copy->len[history_copy->pos_buf]] = '\0';

		count = 0;
		while (count <= history_copy->len_buf)
		{
			free(history_copy->buf[count]);
			count++;
		}
		free(history_copy->len);
		free(history_copy->len_malloc);
		free(history_copy->pos);
		free(history_copy->buf);
	}
	history_first->pos_buf = history_first->len_buf;
	return (0);
}

int				free_history(t_history *history)
{
	int		count;

	count = 0;
	while (count <= history->len_buf)
	{
		free(history->buf[count]);
		count++;
	}
	free(history->len);
	free(history->len_malloc);
	free(history->pos);
	free(history->buf);
	return (0);
}

/*
**
** 0 = normal exit
** 1 = normal error
** 2 = exit for quit the term (like ctrl-D)
** 3 = exit for clean the buff and add a new ligne (ctrl-C)
**
*/

int				while_main(int type, t_history *history_first, t_history *history_copy)
{
	int		err;

	if ((ft_history_copy(history_first, history_copy)) == 1)
		return (1);
	while (1)
	{
		err = line_edition(type, history_copy);
		if (err == 1)
		{
			free_history(history_copy);
			return (1);
		}
		else if (err == 2)
		{
			if ((add_new_history(history_first, history_copy)) == 1)
				return (1);
			return (2);
		}
		else if (err == 3)
		{
			free_history(history_copy);
			if ((ft_history_copy(history_first, history_copy)) == 1)
				return (1);
		}
		if (history_copy->len[history_copy->pos_buf] != 0)
			break ;
		write(1, "\n", 1);
	}
	if ((add_new_history(history_first, history_copy)) == 1)
		return (1);
	return (0);
}

int				free_envp(t_envp *my_envp)
{
	int		x;

	x = 0;
	while (my_envp->envp[x] != NULL)
	{
		free(my_envp->envp[x]);
		x++;
	}
	free(my_envp->envp);
	return (0);
}

#include <stdio.h>

int				main(int argc, char **argv, char **envp)
{
	int			error;
	int			exit_err;
	t_envp		my_envp;
	t_lchar		buf;
	t_history	history_first;
	t_history	history_copy;

	(void)argc;
	(void)argv;
	(void)buf;
	/* ** recuper l'envp ** */
	if ((creat_envp(envp, &my_envp)) == 1)
		return (1);
	/* ** inporter l'history ** */
	if (inport_history(&history_first) == 1)
		return (1);
	/* ** edition de ligne ** */
	while (1)
	{
		error = 0;
		ft_signal(SIGINT, SA_SIGINFO);
		exit_err = while_main(0, &history_first, &history_copy);
		if (exit_err == 1)
			return (1);
		else if (exit_err == 2 || ft_memcmp("exit\n",
					history_first.buf[history_first.pos_buf],
					history_first.len[history_first.pos_buf]) == 0)
		{
			error = 1;
			break ;
		}
		write(1, "\n", 1);
		/* ** parser ** */
		buf.len = history_first.len[history_first.pos_buf];
		buf.c = ft_strdup(history_first.buf[history_first.pos_buf]);
		if ((buf.type = ft_memalloc(sizeof(char *) * buf.len)) == NULL)
			return (1);
		if (parser(&buf, &my_envp, &history_first) == 1)
			return (1);
		free(buf.c);
		free(buf.type);
		buf.len = 0;
	}
	/* ** exporter l'history ** */
	if (export_history(&history_first, error) == 1)
		return (1);
	if (free_envp(&my_envp) == 1)
		return (1);
	return (0);
}
