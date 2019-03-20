#include "../../include/parser.h"

/*int				ft_history_copy_heredoc(t_history *history_first,
		t_history *history_copy)
{
	int			count;

	history_copy->len = history_first->len;
	history_copy->malloc = history_first->len;
	history_copy->pos_buf = history_first->pos_buf;
	if ((history_copy->pos = ft_memalloc(sizeof(int) *
					(history_copy->malloc + 1))) == NULL)
		return (1);
	if ((history_copy->buf = ft_memalloc(sizeof(char *) *
					(history_copy->malloc + 1))) == NULL)
		return (1);
	count = 0;
	while (count < history_first->len)
	{
		history_copy->pos[count] = history_first->pos[count];
		history_copy->buf[count]->len = history_first->buf[count]->len;
		if ((history_copy->buf[count]->c = ft_memalloc(sizeof(char) *
						(history_copy->buf[count]->len + 1))) == NULL)
			return (1);
		ft_memcpy(history_copy->buf[count]->c,
				history_first->buf[count]->c, history_first->buf[count]->len);
		if ((history_copy->buf[count]->type = ft_memalloc(sizeof(int) *
						(history_copy->buf[count]->len + 1))) == NULL)
		ft_memcpy(history_copy->buf[count]->type,
				history_first->buf[count]->type, history_first->buf[count]->len);
		count++;
	}
	return (0);
}
*/
int		creat_heredoc(t_pipelines pipel, t_history *history_first, int z)
{
/*	int			exit_err;
	int			len_heredoc;
	int			count_heredoc;
	int			start_heredoc;
	t_history	history_heredoc;
	t_history	history_copy;

	if (ft_history_copy_heredoc(history_first, &history_heredoc) == 1)
		return (1);
	start_heredoc = history_heredoc.pos_buf + 1;
	while (1)
	{
		exit_err = while_main(1, &history_heredoc, &history_copy);
		if (exit_err == 1)
			return (1);
		else if (exit_err == 2 || ft_memcmp(pipel.redir[z].file_int,
					history_heredoc.buf[history_heredoc.pos_buf],
					history_heredoc.buf[history_heredoc.pos_buf]->len) == 0)
		{
			write(1, "\n", 1);
			break ;
		}
		write(1, "\n", 1);
	}
	count_heredoc = start_heredoc;
	len_heredoc = 0;
	while (count_heredoc < history_heredoc.len)
	{
		len_heredoc += history_heredoc.buf[count_heredoc]->len;
		len_heredoc++;
		count_heredoc++;
	}
	if ((pipel.redir[z].heredoc = ft_memalloc((sizeof(char) *
						(len_heredoc + 1)))) == NULL)
		return (1);
	pipel.redir[z].len_heredoc = 0;
	count_heredoc = 0;
	//count_heredoc = start_heredoc;
	while (count_heredoc < start_heredoc)
	{
		free(history_heredoc.buf[count_heredoc]);
		count_heredoc++;
	}
	while (count_heredoc < history_heredoc.len)
	{
		ft_memcpy(pipel.redir[z].heredoc + pipel.redir[z].len_heredoc,
				history_heredoc.buf[count_heredoc],
				history_heredoc.buf[count_heredoc]->len);
		pipel.redir[z].len_heredoc += history_heredoc.buf[count_heredoc]->len;
		free(history_heredoc.buf[count_heredoc]);
		ft_memcpy(pipel.redir[z].heredoc +
				pipel.redir[z].len_heredoc, "\n", 1);
		pipel.redir[z].len_heredoc++;
		count_heredoc++;
	}
	free(history_heredoc.pos);
	free(history_heredoc.buf);*/
	return (0);
}
