/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:24:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/27 17:51:23 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

int		creat_heredoc(t_redir *redir, t_history *history)
{
	char		buffer[4];
	char		tmp[2048];
	int			x;

	(void)redir;
	(void)history;
	if (init_termcaps() == 1)
		return (1);
	ft_memset(buffer, 0, sizeof(char) * 4);
	while (1)
	{
		x = 0;
		write(1, _PROMPT_ML, _PROMPT_LEN_WRITE_ML);
		ft_memset(tmp, 0, sizeof(char) * 2048);
		while (1)
		{
			ft_memset(buffer, 0, sizeof(char) * 4);
			read(0, buffer, 3);
			write(1, buffer, 1);
			if (buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0)
				break ;
			tmp[x] = buffer[0];
			tmp[x + 1] = '\0';
			x++;
		}
		if (ft_strcmp(tmp, redir->file_name) == 0)
			break ;
	}
	if (reset_termcaps() == 1)
		return (1);
	return (0);
}
