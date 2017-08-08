/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historique.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 14:11:05 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/08 16:21:59 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

/*
**
** le int act est un repaire pour savoir se que doit faire mon historique
** il y a 3 cas :
**  1 = entre une nouvelle valeur a mon historique;
**  2 = remonter dans mon historique;
**  3 = desendre dans mon historique;
**
*/

int		historique(int act, char *cmd, int len_cmd)
{
	int				ret;
	int				fd;
	int				x;
	char			*nbr_ligne_char;
	char			*history_ligne;
	static int		nbr_ligne;

	x = 0;
	ret = 0;
	if (act == 1)
	{
		if ((fd = open(".21sh_history", O_WRONLY | O_CREAT | O_EXCL,
						S_IRUSR | S_IWUSR)) != -1)
			nbr_ligne = 0;
		close(fd);
		if ((fd = open(".21sh_history", O_RDWR | O_APPEND)) == -1)
			return (1);
		if (nbr_ligne == 0)
		{
			while ((ret = get_next_line(fd, &history_ligne)) > 0)
			{
				if (ret == -1)
					return (1);
				if (ret == 0)
					break ;
			//	free(history_ligne);
			}
			if (history_ligne != NULL)
			{
				nbr_ligne = (ft_atoi(history_ligne) + 1);
			//	free(history_ligne);
			}
		}
		if (len_cmd > 0)
		{
			nbr_ligne_char = ft_itoa(nbr_ligne);
			write(fd, nbr_ligne_char, ft_strlen(nbr_ligne_char));
			write(fd, " ", 1);
			write(fd, cmd, len_cmd);
			write(fd, "\n", 1);
			nbr_ligne++;
		}
		close(fd);
	}
	else if (act == 2)
	{
		
	}
	else if (act == 3)
	{
		
	}
	return (0);
}
