#include "../include/vingt_et_un_sh.h"
#include "../include/lchar.h"

int				ft_history_copy(t_history *history_first, t_history *history_copy)
{
	int			count;

	history_copy->len_buf = history_first->len_buf + 1;
	history_copy->malloc_buf = history_first->malloc_buf + 1;
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
	while (count <= history_first->malloc_buf)
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

	(void)history_copy;
	if (history_first->len_buf >= history_first->malloc_buf)
	{
		history_first->malloc_buf += REMALLOC_HISTORY;
		if ((tmp_len = ft_memalloc(sizeof(int) * (history_first->malloc_buf))) == NULL)
			return (1);
		if ((tmp_len_malloc = ft_memalloc(sizeof(int) * (history_first->malloc_buf))) == NULL)
			return (1);
		if ((tmp_pos = ft_memalloc(sizeof(int) * (history_first->malloc_buf))) == NULL)
			return (1);
		if ((tmp_buf = ft_memalloc(sizeof(char *) * (history_first->malloc_buf))) == NULL)
			return (1);
		count = 0;
		while (count < history_first->len_buf)
		{
			printf("pos_buf_copy: %d, count: %d", history_copy->pos_buf, count);
			if (history_copy->pos_buf == count)
			{
				tmp_len[count] = history_first->len[count];
				tmp_len_malloc[count] = history_first->len_malloc[count];
				tmp_pos[count] = history_first->pos[count];
				//tmp_buf[count] = history_first->buf[count];
				if ((tmp_buf[count] = ft_memalloc(sizeof(char) * (history_first->len_malloc[count]))) == NULL)
					return (1);
				ft_memcpy(tmp_buf[count], history_first->buf[count], history_first->len[count]);
				tmp_buf[count][history_first->len[count]] = '\0';
				free(history_first->buf[count]);
			}
			else
			{
				tmp_len[count] = history_copy->len[count];
				tmp_len_malloc[count] = history_copy->len_malloc[count];
				tmp_pos[count] = history_copy->pos[count];
				//tmp_buf[count] = history_copy->buf[count];
				if ((tmp_buf[count] = ft_memalloc(sizeof(char) * (history_copy->len_malloc[history_copy->pos_buf]))) == NULL)
					return (1);
				ft_memcpy(tmp_buf[count], history_copy->buf[history_copy->pos_buf], history_copy->len[history_copy->pos_buf]);
				tmp_buf[count][history_copy->len[count]] = '\0';
			}
			/*
			if (history_first->buf[count] != NULL)
			{
				tmp_len[count] = history_first->len[count];
				tmp_len_malloc[count] = history_first->len_malloc[count];
				tmp_pos[count] = history_first->pos[count];
				if ((tmp_buf[count] = ft_memalloc(sizeof(char) * (history_first->len_malloc[count]))) == NULL)
					return (1);
				ft_memcpy(tmp_buf[count], history_first->buf[count], history_first->len[count]);
				tmp_buf[count][history_first->len[count]] = '\0';
				free(history_first->buf[count]);
			}
			else if (history_first->malloc_buf > count)
			{
				tmp_len[count] = history_copy->len[history_copy->pos_buf];
				tmp_len_malloc[count] = history_copy->len_malloc[history_copy->pos_buf];
				tmp_pos[count] = history_copy->pos[history_copy->pos_buf];
				if ((tmp_buf[count] = ft_memalloc(sizeof(char) *
								(history_copy->len_malloc[history_copy->pos_buf]))) == NULL)
					return (1);
				ft_memcpy(tmp_buf[count], history_copy->buf[history_copy->pos_buf], history_copy->len[history_copy->pos_buf]);
				tmp_buf[count][history_copy->len[history_copy->pos_buf]] = '\0';
			}
			*/
			count++;
		}
//		free(history_first->len);
//		free(history_first->len_malloc);
//		free(history_first->pos);
//		free(history_first->buf);
		history_first->len = tmp_len;
		history_first->len_malloc = tmp_len_malloc;
		history_first->pos = tmp_pos;
		history_first->buf = tmp_buf;
	}
	history_first->pos_buf = history_first->len_buf;
	return (0);
}

int				while_main(t_history *history_first, t_history *history_copy)
{
	if ((ft_history_copy(history_first, history_copy)) == 1)
		return (1);


	printf("\nfirst %d, %d, %d\n", history_first->len_buf,  history_first->malloc_buf, history_first->pos_buf);
	int x = 0;
	while (x <= history_first->len_buf)
	{
		printf("%d, %d, %d, %d, %s\n", x, history_first->len[x], history_first->len_malloc[x], history_first->pos[x], history_first->buf[x]);
		x++;
	}
	printf("exit first\n");
	printf("\ncopy %d, %d, %d\n", history_copy->len_buf,  history_copy->malloc_buf, history_copy->pos_buf);
	int y = 0;
	while (y <= history_copy->len_buf)
	{
		printf("%d, %d, %d, %d, %s\n", y, history_copy->len[y], history_copy->len_malloc[y], history_copy->pos[y], history_copy->buf[y]);
		y++;
	}
	printf("exit copy\n");


	if ((line_edition(history_copy)) == 1)
		return (1);
	history_first->len_buf++;
	if ((add_new_history(history_first, history_copy)) == 1)
		return (1);

	printf("\nfirst after add %d, %d, %d\n", history_first->len_buf,  history_first->malloc_buf, history_first->pos_buf);
	int x1 = 0;
	while (x1 <= history_first->len_buf)
	{
		printf("%d, %d, %d, %d, %s\n", x1, history_first->len[x1], history_first->len_malloc[x1], history_first->pos[x1], history_first->buf[x1]);
		x1++;
	}
	printf("exit first after add\n");
	printf("\ncopy after add %d, %d, %d\n", history_copy->len_buf,  history_copy->malloc_buf, history_copy->pos_buf);
	int y1 = 0;
	while (y1 <= history_copy->len_buf)
	{
		printf("%d, %d, %d, %d, %s\n", y1, history_copy->len[y1], history_copy->len_malloc[y1], history_copy->pos[y1], history_copy->buf[y1]);
		y1++;
	}
	printf("exit copy after add\n");

	return (0);
}

int				main(int argc, char **argv, char **envp)
{
	char		**new_envp;
	t_lchar		buf;
	t_history	history_first;
	t_history	history_copy;

	(void)argc;
	(void)argv;
	(void)buf;
	/* ** recuper l'envp ** */
	if ((new_envp = creat_envp(envp)) == NULL)
		return (1);
	/* ** inporter l'history ** */
	if (inport_history(&history_first) == 1)
		return (1);
	/* ** edition de ligne ** */
	while (1)
	{
		if ((while_main(&history_first, &history_copy)) == 1)
			return (1);
		if (ft_memcmp("exit", history_first.buf[history_first.pos_buf], history_first.len[history_first.pos_buf]) == 0)
		{
			history_first.len_buf--;
			break ;
		}
		write(0, "\n", 1);
		/* ** parser ** */
		buf.len = history_first.len[history_first.pos_buf];
		buf.c = history_first.buf[history_first.pos_buf];
		if ((buf.type = ft_memalloc(sizeof(char *) * buf.len)) == NULL)
			return (1);
//		if (parser(&buf) == 1)
//			return (1);
	}
	/* ** exporter l'history ** */
	if (export_history(&history_first) == 1)
		return (1);
	return (0);
}
