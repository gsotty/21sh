/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 08:41:21 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/05 15:41:06 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void			ft_free_copy_str(char **tmp_str, t_lenexec *lenexec)
{
	int		count;

	count = 0;
	while (count < lenexec->len)
	{
		if (lenexec->str != 0)
		{
			tmp_str[count] = lenexec->str[count];
		}
		count++;
	}
	free(lenexec->str);
}

static void			ft_free_copy_type(int *tmp_type, t_lenexec *lenexec)
{
	int		count;

	count = 0;
	while (count < lenexec->len)
	{
		if (lenexec->type != 0)
		{
			tmp_type[count] = lenexec->type[count];
		}
		count++;
	}
	free(lenexec->type);
}

static void			ft_free_copy_lenexec(t_lenexec **pipe_tmp, t_lenexec *lenexec)
{
	int		count;

	count = 0;
	while (count < lenexec->len)
	{
		if (lenexec->next[count] != NULL)
		{
			pipe_tmp[count] = lenexec->next[count];
		}
		count++;
	}
	free(lenexec->next);
}

static int			ft_remalloc_str(t_lenexec *lenexec)
{
	char	**tmp_str;

	if ((tmp_str = ft_memalloc(sizeof(char *) * (lenexec->len + 1))) == NULL)
		return (1);
	if (lenexec->str != NULL)
		ft_free_copy_str(tmp_str, lenexec);
	lenexec->str = tmp_str;
	return (0);
}

static int			ft_remalloc_type(t_lenexec *lenexec)
{
	int		*tmp_type;

	if ((tmp_type = ft_memalloc(sizeof(int) * (lenexec->len + 1))) == NULL)
		return (1);
	if (lenexec->type != NULL)
		ft_free_copy_type(tmp_type, lenexec);
	lenexec->type = tmp_type;
	return (0);
}

static int			ft_remalloc_lenexec(t_lenexec *lenexec)
{
	t_lenexec	**pipe_tmp;

	if ((pipe_tmp = ft_memalloc(sizeof(t_lenexec *) * (lenexec->len + 1))) == NULL)
		return (1);
	if (lenexec->next != NULL)
		ft_free_copy_lenexec(pipe_tmp, lenexec);
	lenexec->next = pipe_tmp;
	return (0);
}

/*
static int			ft_copy_str_lenexec(t_lenexec *lenexec, int start, int end,
		t_lchar **tab_split)
{
	int		count;

//	fprintf(stderr, "end - start = [%d]\n", end - start);
	lenexec->len_str = (end - start);
	if ((lenexec->str = ft_memalloc(sizeof(t_lchar *) * ((end - start) + 1))) == NULL)
		return (1);
	count = start;
	while (count < end)
	{
//		fprintf(stderr, "tab_split[%d] = [%s]\ncount - start = [%d]\n", count, tab_split[count]->c, count - start);
		if ((lenexec->str[count - start] = ft_memalloc(sizeof(t_lchar))) == NULL)
			return (1);
		ft_lchardup(lenexec->str[count - start], tab_split[count], 0);
		count++;
	}
	return (0);
}
*/

char				*ft_lcharstr(t_lchar *lchar)
{
	int		count;
	char	*new_str;

	if ((new_str = ft_memalloc(sizeof(char) * (lchar->len + 1))) == NULL)
		return (NULL);
	count = 0;
	while (count < lchar->len)
	{
		new_str[count] = lchar->c[count];
		count++;
	}
	new_str[count] = '\0';
	return (new_str);
}

t_parser_count		redir[] = {
	{"<<-", _APPROUT},
	{"<<", _HEREDOC},
	{">>", _APPROUT},
	{"<&", _DUPINT},
	{">&", _DUPOUT},
	{"<>", _RRDWR},
	{">|", _ROUT},
	{"<", _RINT},
	{">", _ROUT}
};

int					ft_nbrcmd(t_lenexec *lenexec, int start_tab, int end,
		t_lchar **tab_split)
{
	int		ret;
	int		count;
	int		start;
	int		count_redir;

	count = start_tab;
	start = start_tab;
	lenexec->len = 0;
	while (count < end && tab_split[count] != NULL)
	{
		fprintf(stderr, "\033[33mcmd\033[0mtab_split[%d] = [%s]\n",
				count, tab_split[count]->c);
		count_redir = 0;
		while (count_redir < 9)
		{
			if ((ret = ft_strmatch(tab_split[count]->c, redir[count_redir].str)) >= 0)
				break;
			count_redir++;
		}
		if (count_redir < 9)
		{
			fprintf(stderr, "count_redir = [%d]\n", count_redir);
			if (ft_remalloc_str(lenexec) == 1)
				return (-1);
			if (ft_remalloc_type(lenexec) == 1)
				return (-1);
			lenexec->str[lenexec->len] = ft_lcharstr(tab_split[count]);
			lenexec->type[lenexec->len] = redir[count_redir].redir;
			lenexec->len++;
		}
		else if (ft_onlydigit(tab_split[count]->type, tab_split[count]->len) == 1)
		{
			if (ft_remalloc_str(lenexec) == 1)
				return (-1);
			if (ft_remalloc_type(lenexec) == 1)
				return (-1);
			lenexec->str[lenexec->len] = ft_lcharstr(tab_split[count]);
			lenexec->type[lenexec->len] = _INTFD;
			lenexec->len++;
		}
		else if (ft_onlyspace(tab_split[count]->type, tab_split[count]->len) == 0)
		{
			if (ft_remalloc_str(lenexec) == 1)
				return (-1);
			if (ft_remalloc_type(lenexec) == 1)
				return (-1);
			lenexec->str[lenexec->len] = ft_lcharstr(tab_split[count]);
			lenexec->type[lenexec->len] = _WORD;
			lenexec->len++;
		}
		count++;
	}
	return (0);
}

int					ft_nbrpipe(t_lenexec *lenexec, int start_tab, int end,
		t_lchar **tab_split)
{
	int		ret;
	int		count;
	int		start;

	count = start_tab;
	start = start_tab;
	lenexec->len = 0;
	while (count < end && tab_split[count] != NULL)
	{
		fprintf(stderr, "\033[32mpipe\033[0mtab_split[%d] = [%s]\n",
				count, tab_split[count]->c);
		if ((ret = ft_strmatch(tab_split[count]->c, "|")) >= 0)
		{
			if (start == count)
				return (-1);
			if (ft_remalloc_lenexec(lenexec) == 1)
				return (-1);
			if ((lenexec->next[lenexec->len] = ft_memalloc(sizeof(t_lenexec))) == NULL)
				return (1);
			ft_nbrcmd(lenexec->next[lenexec->len], start, count, tab_split);
			lenexec->len++;
			count++;
			start = count;
			if (count < end && tab_split[count] == NULL)
				return (0);
		}
		else
			count++;
	}
	if (ft_remalloc_lenexec(lenexec) == 1)
		return (-1);
	if ((lenexec->next[lenexec->len] = ft_memalloc(sizeof(t_lenexec))) == NULL)
		return (1);
	ft_nbrcmd(lenexec->next[lenexec->len], start, count, tab_split);
	lenexec->len++;
	return (0);
}

int					ft_nbrsep(t_lenexec *lenexec, int end,
		t_lchar **tab_split)
{
	int		ret;
	int		count;
	int		start;

	count = 0;
	start = 0;
	lenexec->len = 0;
	while (count < end && tab_split[count] != NULL)
	{
		fprintf(stderr, "\033[31msep\033[0mtab_split[%d] = [%s]\n",
				count, tab_split[count]->c);
		if ((ret = ft_strmatch(tab_split[count]->c, ";")) >= 0)
		{
			if (start == count)
				return (-1);
			if (ft_remalloc_lenexec(lenexec) == 1)
				return (-1);
			if ((lenexec->next[lenexec->len] = ft_memalloc(sizeof(t_lenexec))) == NULL)
				return (1);
			ft_nbrpipe(lenexec->next[lenexec->len], start, count, tab_split);
			lenexec->len++;
			count++;
			start = count;
			if (count < end && tab_split[count] == NULL)
				return (0);
		}
		else
			count++;
	}
	if (ft_remalloc_lenexec(lenexec) == 1)
		return (-1);
	if ((lenexec->next[lenexec->len] = ft_memalloc(sizeof(t_lenexec))) == NULL)
		return (1);
	ft_nbrpipe(lenexec->next[lenexec->len], start, count, tab_split);
	lenexec->len++;


	int		count_print_sep;
	int		count_print_pipe;
	int		count_print_cmd;

	count_print_sep = 0;
	fprintf(stderr, "\t\033[31msep\033[0m = [%d]\n", lenexec->len);
	while (count_print_sep < lenexec->len)
	{
		count_print_pipe = 0;
		fprintf(stderr, "\t\t\033[32mpipe\033[0m = [%d]\n", lenexec->next[count_print_sep]->len);
		while (count_print_pipe < lenexec->next[count_print_sep]->len)
		{
			count_print_cmd = 0;
			fprintf(stderr, "\t\t\t\033[33mcmd\033[0m = [%d]\n", lenexec->next[count_print_sep]->next[count_print_pipe]->len);
			while (count_print_cmd < lenexec->next[count_print_sep]->next[count_print_pipe]->len)
			{
				fprintf(stderr, "\t\t\tstr = [%s]\n", lenexec->next[count_print_sep]->next[count_print_pipe]->str[count_print_cmd]);
				fprintf(stderr, "\t\t\ttype = [%d]\n", lenexec->next[count_print_sep]->next[count_print_pipe]->type[count_print_cmd]);
				count_print_cmd++;
			}
			count_print_pipe++;
		}
		count_print_sep++;
	}
	return (0);
}
