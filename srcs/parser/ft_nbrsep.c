/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 08:41:21 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/05 11:55:26 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

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
//	free(lenexec->next);
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
		fprintf(stderr, "count_redir = [%d]\n", count_redir);
		if (count_redir < 9)
		{
	//		if (start == count)
	//			return (-1);
			lenexec->len++;
			//lenexec->type = redir[count_redir].redir;
	//		lenexec->len++;
	//		count++;
	//		start = count;
	//		if (count < end && tab_split[count] == NULL)
	//			return (0);
		}
		else if (ft_onlydigit(tab_split[count]->type, tab_split[count]->len) == 1)
		{
			lenexec->len++;
		}
		else if (ft_onlyspace(tab_split[count]->type, tab_split[count]->len) == 0)
		{
			lenexec->len++;
		}
		count++;
	}
//	lenexec->len++;
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
	fprintf(stderr, "\tsep = [%d]\n", lenexec->len);
	while (count_print_sep < lenexec->len)
	{
		count_print_pipe = 0;
		fprintf(stderr, "\t\tpipe = [%d]\n", lenexec->next[count_print_sep]->len);
		while (count_print_pipe < lenexec->next[count_print_sep]->len)
		{
			count_print_cmd = 0;
			fprintf(stderr, "\t\t\tcmd = [%d]\n", lenexec->next[count_print_sep]->next[count_print_pipe]->len);
			while (count_print_cmd < lenexec->next[count_print_sep]->next[count_print_pipe]->len)
			{
			//	fprintf(stderr, "\t\t\tstr = \033[34m[%s]\033[0m\n", lenexec->next[count_print_sep]->next[count_print_pipe]->str[count_print_cmd]->c);
				count_print_cmd++;
			}
			count_print_pipe++;
		}
		count_print_sep++;
	}
	return (0);
}
