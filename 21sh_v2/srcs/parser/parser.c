/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 13:29:19 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/29 17:42:28 by gsotty           ###   ########.fr       */
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
	if (cmd == NULL)
		return (_SPACE);
	else if (ft_strcmp(cmd, "<") == 0)
		return (_LESS);
	else if (ft_strcmp(cmd, ">") == 0)
		return (_GREAT);
	else if (ft_strcmp(cmd, "<<") == 0)
		return (_DLESS);
	else if (ft_strcmp(cmd, ">>") == 0)
		return (_DGREAT);
	else if (ft_strcmp(cmd, "<&") == 0)
		return (_DUP_OUTPUT);
	else if (ft_strcmp(cmd, ">&") == 0)
		return (_DUP_INPUT);
	else if (ft_strcmp(cmd, "|") == 0)
		return (_PIPE);
	else if (ft_strcmp(cmd, ";") == 0)
		return (_SEP);
	else if (ft_strcmp(cmd, "||") == 0)
		return (_OR_IF);
	else if (ft_strcmp(cmd, "&&") == 0)
		return (_AND_IF);
	else if (ft_strchr(cmd, ' ') != NULL)
		return (_SPACE);
	else if (cmd[0] == '\0')
		return (_SPACE);
	return (_WORD);
}

/*
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
*/
int			parser(char *cmd, t_len_cmd *len, t_struc_envp *struc_envp)
{
	t_token		*begin_token;
	t_lexer		s;

	ft_memset(&s, 0, sizeof(t_lexer));
	(void)struc_envp;
	if ((begin_token = ft_memalloc(sizeof(*begin_token))) == NULL)
		return (1);
	//lexer_cmd(cmd, len, &begin_token);
//	test(cmd, len, ";", &begin_token);
//	tmp = begin_token;
//	while (tmp != NULL)
//	{
//		ft_printf("[%d], [%s]\n", tmp->type, tmp->str);
///		tmp = tmp->next;
//	}
	s.first_call_sep = 1;
	while ((s.sep = creat_token_sep(cmd, len->len, s.first_call_sep)) != NULL)
	{
		s.sep->type = is_type(s.sep->str);
		s.first_call_and_or = 1;
	//	printf("sep = [%d] [%s]\n", s.sep->type, s.sep->str);
		while ((s.and_or = creat_token_and_or(s.sep->str, ft_strlen(s.sep->str),
						s.first_call_and_or)) != NULL)
		{
			s.and_or->type = is_type(s.and_or->str);
			s.first_call_pipe = 1;
	//		printf("and_or = [%d] [%s]\n", s.and_or->type, s.and_or->str);
			while ((s.pipe = creat_token_pipe(s.and_or->str,
							ft_strlen(s.and_or->str), s.first_call_pipe,
							s.and_or->type)) != NULL)
			{
				s.pipe->type = is_type(s.pipe->str);
				s.first_call_dg_dl = 1;
	//			ft_printf("pipe = [%d] [%s]\n", s.pipe->type, s.pipe->str);
				while ((s.dg_dl = creat_token_dg_dl(s.pipe->str,
								ft_strlen(s.pipe->str), s.first_call_dg_dl)))
				{
					s.dg_dl->type = is_type(s.dg_dl->str);
					s.first_call_gr_le = 1;
	//				ft_printf("dg_dl = [%d] [%s]\n", s.dg_dl->type, s.dg_dl->str);
					while ((s.gr_le = creat_token_gr_le(s.dg_dl->str,
									ft_strlen(s.dg_dl->str), s.first_call_gr_le
									, s.dg_dl->type)))
					{
						s.gr_le->type = is_type(s.gr_le->str);
						s.first_call_space = 1;
	//					ft_printf("gr_le = [%d] [%s]\n", s.gr_le->type,
	//							s.gr_le->str);
						while ((s.space = creat_token_space(s.gr_le->str,
									ft_strlen(s.gr_le->str),
									s.first_call_space)))
						{
							s.space->type = is_type(s.space->str);
							ft_printf("space = [%d] [%s]\n", s.space->type,
									s.space->str);
							s.first_call_space = 0;
						}
						s.first_call_gr_le = 0;
					}
					s.first_call_dg_dl = 0;
				}
				s.first_call_pipe = 0;
			}
			s.first_call_and_or = 0;
		}
		s.first_call_sep = 0;
	}
	return (0);
}
