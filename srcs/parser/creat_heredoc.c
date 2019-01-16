#include "../../include/parser.h"

int				ft_history_copy_heredoc(t_history *history_first, t_history *history_copy)
{
	int			count;

	history_copy->len_buf = history_first->len_buf;
	history_copy->malloc_buf = history_first->len_buf;
	history_copy->pos_buf = history_first->pos_buf;
	if ((history_copy->len = ft_memalloc(sizeof(int) * (history_copy->malloc_buf + 1))) == NULL)
		return (1);
	if ((history_copy->len_malloc = ft_memalloc(sizeof(int) * (history_copy->malloc_buf + 1))) == NULL)
		return (1);
	if ((history_copy->pos = ft_memalloc(sizeof(int) * (history_copy->malloc_buf + 1))) == NULL)
		return (1);
	if ((history_copy->buf = ft_memalloc(sizeof(char *) * (history_copy->malloc_buf + 1))) == NULL)
		return (1);
	count = 0;
	while (count < history_first->len_buf)
	{
		history_copy->len[count] = history_first->len[count];
		history_copy->len_malloc[count] = history_first->len_malloc[count];
		history_copy->pos[count] = history_first->pos[count];
		if ((history_copy->buf[count] = ft_memalloc(sizeof(char) * (history_copy->len_malloc[count] + 1))) == NULL)
			return (1);
		ft_memcpy(history_copy->buf[count], history_first->buf[count], history_first->len[count]);
		count++;
	}
	return (0);
}

int		creat_heredoc(t_pipelines pipel, t_history *history_first, int z)
{
	int			exit_err;
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
					history_heredoc.len[history_heredoc.pos_buf]) == 0)
		{
			write(1, "\n", 1);
			break ;
		}
		write(1, "\n", 1);
	}
	count_heredoc = start_heredoc;
	len_heredoc = 0;
	while (count_heredoc < history_heredoc.len_buf)
	{
		len_heredoc += history_heredoc.len[count_heredoc];
		len_heredoc++;
		count_heredoc++;
	}
	if ((pipel.redir[z].heredoc = ft_memalloc((sizeof(char) * (len_heredoc + 1)))) == NULL)
		return (1);
	pipel.redir[z].len_heredoc = 0;
	count_heredoc = 0;
	//count_heredoc = start_heredoc;
	while (count_heredoc < start_heredoc)
	{
		free(history_heredoc.buf[count_heredoc]);
		count_heredoc++;
	}
	while (count_heredoc < history_heredoc.len_buf)
	{
		ft_memcpy(pipel.redir[z].heredoc + pipel.redir[z].len_heredoc, history_heredoc.buf[count_heredoc], history_heredoc.len[count_heredoc]);
		pipel.redir[z].len_heredoc += history_heredoc.len[count_heredoc];
		free(history_heredoc.buf[count_heredoc]);
		ft_memcpy(pipel.redir[z].heredoc + pipel.redir[z].len_heredoc, "\n", 1);
		pipel.redir[z].len_heredoc++;
		count_heredoc++;
	}
	free(history_heredoc.len);
	free(history_heredoc.len_malloc);
	free(history_heredoc.pos);
	free(history_heredoc.buf);
	return (0);
}


