#include "../include/vingt_et_un_sh.h"
#include "../include/lchar.h"
#include "../include/parser.h"

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

/*
**
** 0 = normal exit
** 1 = normal error
** 2 = exit for quit the term (like ctrl-D)
** 3 = exit for clean the buff and add a new ligne (ctrl-C)
**
*/

/*
static int		ft_printhistory(t_history *history)
{
	int		x;
	int		y;

	x = 0;
	printf("len = \"%d\", malloc = \"%d\"\n", history->len, history->malloc);
	printf("pos_buf = \"%d\"\n", history->pos_buf);
	while (x <= history->len)
	{
		printf("pos[%d] = \"%d\"\n", x, history->pos[x]);
		printf("	buf[%d]->len = \"%d\"\n", x, history->buf[x]->len);
		printf("	buf[%d]->c = \"%s\"\n", x, history->buf[x]->c);
		printf("	buf[%d]->type = \"", x);
		y = 0;
		while (y < history->buf[x]->len)
		{
			printf("%d,", history->buf[x]->type[y]);
			y++;
		}
		printf("\"\n");
		x++;
	}
	return (0);
}
*/

t_lchar			*while_main(int type, t_history *history)
{
	int			err;
	t_lchar		*buf;
	t_history	history_cpy;

	if ((ft_historycpy(history, &history_cpy, 1)) == NULL)
		return (NULL);
	history_cpy.pos_buf = history_cpy.len;
	buf = line_edition(type, &history_cpy);
	if (buf->len == -1)
		return (buf);
	if ((add_new_history(history, buf)) == NULL)
		return (NULL);
	return (buf);
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
	t_lchar		*buf;
	t_envp		my_envp;
	t_history	history;

	(void)argc;
	(void)argv;
	/* ** recuper l'envp ** */
	if ((creat_envp(envp, &my_envp)) == 1)
		return (1);
	/* ** inporter l'history ** */
	if (inport_history(&history) == 1)
		return (1);
	/* ** edition de ligne ** */
	while (1)
	{
		error = 0;
		ft_signal(SIGINT, SA_SIGINFO);
		if ((buf = while_main(0, &history)) == NULL)
			return (1);
		if (buf->len != -1)
		{
			if (ft_strmatch("exit", buf->c) == 1 ||
						(buf->type[0] == _EOT && buf->len == 1))
			{
				error = 1;
				break ;
			}
			/* ** parser ** */
			if (parser(buf, &history, &my_envp) == 1)
				return (1);
		}
		free(buf);
	}
	/* ** exporter l'history ** */
//	if (export_history(&history_first, error) == 1)
//		return (1);
	ft_freehistory(&history);
	if (free_envp(&my_envp) == 1)
		return (1);
	return (0);
}
