/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:31:23 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 16:31:24 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "../lib/libft/libft.h"
# include "lchar.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define PATH_HIST ".21sh_history"
# define REMALLOC_HISTORY 10

typedef struct		s_history
{
	int				len;
	int				malloc;
	int				pos_buf;
	int				*pos;
	t_lchar			**buf;
}					t_history;

int					ft_freehistory(t_history *history);
t_history			*ft_historycpy(t_history *history_first,
		t_history *history_copy, int n);
int					ft_remallochistory(t_history *history_first);

#endif
