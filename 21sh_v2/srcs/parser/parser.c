/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 13:29:19 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/27 18:55:51 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

/*
 ** il me faut un char ** qui contien tous les cmd a exe dans le bonne ordre.
 */

int			add_token(char *cmd, int start, int end, t_token *token)
{
	if ((token->str = ft_memalloc(sizeof(char) * ((end - start) + 1))) == NULL)
		return (1);
	ft_memcpy(token->str, cmd + start, end - start);
	token->str[end - start] = '\0';
	token->type = _WORD;
	token->next = NULL;
	return (0);
}

int			is_type(char *cmd)
{
	if (ft_strcmp(cmd, "<") == 0)
		return (6);
	else if (ft_strcmp(cmd, ">") == 0)
		return (7);
	else if (ft_strcmp(cmd, "<<") == 0)
		return (8);
	else if (ft_strcmp(cmd, ">>") == 0)
		return (9);
	else if (ft_strcmp(cmd, "<&") == 0)
		return (10);
	else if (ft_strcmp(cmd, ">&") == 0)
		return (11);
	else if (ft_strcmp(cmd, "|") == 0)
		return (12);
	else if (ft_strcmp(cmd, ";") == 0)
		return (13);
	return (1);
}

int			test(char *cmd, t_len_cmd *len, char *delim, t_token **begin_token)
{
	int		x;
	int		y;
	int		start;
	int		end;
	int		start_token;
	t_token	*token;

	x = 0;
	start = 0;
	end = 0;
	start_token = 1;
	while (x < len->len)
	{
		y = 0;
		while (delim[y] != '\0')
		{
			if (cmd[x] == delim[y])
			{
				end = x;
				if (start_token == 1)
				{
					*begin_token = token_new(cmd + start, end - start, 0);
					token = *begin_token;
					token->type = is_type(token->str);
					start_token = 0;
				}
				else
				{
					token->next = token_new(cmd + start, end - start, 0);
					token->next->type = is_type(token->next->str);
					token = token->next;
				}
				start = x;
				x++;
				end = x;
				if (start_token == 1)
				{
					*begin_token = token_new(cmd + start, end - start, 0);
					token = *begin_token;
					token->type = is_type(token->str);
					start_token = 0;
				}
				else
				{
					token->next = token_new(cmd + start, end - start, 0);
					token->next->type = is_type(token->next->str);
					token = token->next;
				}
				start = x;
			}
			y++;
		}
		x++;
	}
	end = x;
	if (start_token == 1)
	{
		*begin_token = token_new(cmd + start, end - start, 0);
		token = *begin_token;
		token->type = is_type(token->str);
		start_token = 0;
	}
	else
	{
		token->next = token_new(cmd + start, end - start, 0);
		token->next->type = is_type(token->next->str);
		token = token->next;
	}
	start = x;
	return (0);
}

int			lexer_cmd(char *cmd, t_len_cmd *len, t_token **begin_token)
{
	int		x;
	int		start;
	int		end;
	int		start_token;
	int		is_char;
	t_token	*token;

	x = 0;
	start = 0;
	end = 0;
	is_char = 1;
	start_token = 1;
	token = *begin_token;
	while (x < len->len)
	{
		ft_printf("%c\n", cmd[x]);
		if (cmd[x] != ' ' && cmd[x] != '\t' && is_char == 1)
		{
			is_char = 0;
			start = x;
		}
		if (cmd[x] == '\'' && is_char == 0)
		{
			cmd[x] = '\0';
			x++;
			while (cmd[x] != '\'' && cmd[x] != '\0')
				x++;
			end = x;
			cmd[x] = '\0';
			x++;
		}
		else if (cmd[x] == '\"' && is_char == 0)
		{
			cmd[x] = '\0';
			x++;
			while (cmd[x] != '\"' && cmd[x] != '\0')
				x++;
			end = x;
			cmd[x] = '\0';
			x++;
		}
		else if (cmd[x] == '|' && is_char == 0)
		{
			if (cmd[x - 1] != ' ' && cmd[x - 1] != '\t')
			{
				end = x;
				if (start_token == 1)
				{
					*begin_token = token_new(cmd + start, end - start, 0);
					token = *begin_token;
					token->type = is_type(token->str);
					start_token = 0;
				}
				else
				{
					token->next = token_new(cmd + start, end - start, 0);
					token->type = is_type(token->str);
					token = token->next;
				}
				start = x;
			}
			x++;
			end = x;
			if (start_token == 1)
			{
				*begin_token = token_new(cmd + start, end - start, 0);
				token = *begin_token;
				token->type = is_type(token->str);
				start_token = 0;
			}
			else
			{
				token->next = token_new(cmd + start, end - start, 0);
				token->type = is_type(token->str);
				token = token->next;
			}
			ft_printf("cmd = %d\n", cmd[x]);
			start = x;
			while (cmd[x] != ' ' && cmd[x] != '\t')
				x++;
			ft_printf("cmd = %d\n", cmd[x]);
		}
		else if ((cmd[x] == ' ' || cmd[x] == '\t') && is_char == 0)
		{
			end = x;
			if (start_token == 1)
			{
				*begin_token = token_new(cmd + start, end - start, 0);
				token = *begin_token;
				token->type = is_type(token->str);
				start_token = 0;
			}
			else
			{
				token->next = token_new(cmd + start, end - start, 0);
				token->type = is_type(token->str);
				token = token->next;
			}
			while (cmd[x] == ' ' || cmd[x] == '\t')
				x++;
			start = x;
		}
		else
			x++;
	}
	if (cmd[x - 1] != ' ' && cmd[x - 1] != '\t')
	{
		end = x;
		if (start_token == 1)
		{
			*begin_token = token_new(cmd + start, end - start, 0);
			token = *begin_token;
			token->type = is_type(token->str);
			start_token = 0;
		}
		else
		{
			token->next = token_new(cmd + start, end - start, 0);
			token->type = is_type(token->str);
			token = token->next;
		}
	}
	return (0);
}

int			parser(char *cmd, t_len_cmd *len, t_struc_envp *struc_envp)
{
	t_token		*begin_token;
	t_lexer		s;
	int			first_call;
	int			first_call_1;

	ft_memset(&s, 0, sizeof(t_lexer));
	(void)struc_envp;
	if ((begin_token = ft_memalloc(sizeof(*begin_token))) == NULL)
		return (1);
	//lexer_cmd(cmd, len, &begin_token);
	test(cmd, len, ";", &begin_token);
//	tmp = begin_token;
//	while (tmp != NULL)
//	{
//		ft_printf("[%d], [%s]\n", tmp->type, tmp->str);
///		tmp = tmp->next;
//	}
	first_call = 1;
	while ((s.sep = creat_token(cmd, len->len, ";", first_call)) != NULL)
	{
		first_call_1 = 1;
		while ((s.pipe = creat_token_2(s.sep->str, ft_strlen(s.sep->str), "|", first_call_1)) != NULL)
		{
			s.pipe->type = is_type(s.pipe->str);
			ft_printf("[%d] [%s]\n", s.pipe->type, s.pipe->str);
			first_call_1 = 0;
		}
		first_call = 0;
	}
	return (0);
}
