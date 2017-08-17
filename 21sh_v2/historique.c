/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historique.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 14:11:05 by gsotty            #+#    #+#             */
/*   Updated: 2017/08/17 08:54:14 by gsotty           ###   ########.fr       */
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

int		nbr_ligne_of_file(void)
{
	int		x;
	int		fd;
	int		ret;
	char	*ligne;

	x = 0;
	ret = 0;
	if ((fd = open(".21sh_history", O_RDONLY)) == -1)
		return (-1);
	while ((ret = get_next_line(fd, &ligne)) > 0)
	{
		if (ret == -1)
			return (-1);
		x++;
	}
	return (x);
}

int		historique(int act, char **cmd, t_len_cmd *len)
{
	int				x;
	int				ret;
	int				fd;
	int				nbr_ligne;
	char			*ligne;
	static char		**history;
	static int		verif;
	static int		pos_history;

	x = 0;
	ret = 0;
	if (act == 1)
	{
		if (verif == 1)
		{
			verif = 0;
			while (history[x] != NULL)
			{
			//	free(history[x]);
				x++;
			}
			//free(history);
			x = 0;
		}
		if ((fd = open(".21sh_history", O_RDWR | O_CREAT | O_APPEND,
						S_IRUSR | S_IWUSR)) == -1)
			return (1);
		if (len->len > 0)
		{
			write(fd, *cmd, len->len);
			write(fd, "\n", 1);
		}
		close(fd);
		nbr_ligne = nbr_ligne_of_file();
		if ((history = ft_memalloc(sizeof(char *) * nbr_ligne)) == NULL)
			return (1);
		if ((fd = open(".21sh_history", O_RDONLY)) == -1)
			return (-1);
		while ((ret = get_next_line(fd, &ligne)) > 0)
		{
			if (ret == -1)
				return (1);
			history[x] = ft_strdup(ligne);
			x++;
		}
		pos_history = (nbr_ligne - 1);
		close(fd);
		verif = 1;
	}
	else if (act == 2)
	{
		nbr_ligne = nbr_ligne_of_file();
		if (verif == 0)
		{
			if ((fd = open(".21sh_history", O_RDWR | O_CREAT | O_APPEND,
							S_IRUSR | S_IWUSR)) == -1)
				return (1);
			close(fd);
			if ((history = ft_memalloc(sizeof(char *) * nbr_ligne)) == NULL)
				return (1);
			if ((fd = open(".21sh_history", O_RDONLY)) == -1)
				return (-1);
			while ((ret = get_next_line(fd, &ligne)) > 0)
			{
				if (ret == -1)
					return (1);
				history[x] = ft_strdup(ligne);
				x++;
			}
			pos_history = (nbr_ligne - 1);
			close(fd);
			verif = 1;
		}
		x = 0;
		while (history[x] != NULL)
		{
			if (x == pos_history)
			{
			//	ft_printf("%s", history[x]);
				*cmd = ft_strdup(history[x]);
				len->len = ft_strlen(history[x]);
			}
			x++;
		}
		if (pos_history > 0)
			pos_history = pos_history - 1;
	}
	else if (act == 3)
	{
		nbr_ligne = nbr_ligne_of_file();
		if (verif == 0)
		{
			if ((fd = open(".21sh_history", O_RDWR | O_CREAT | O_APPEND,
							S_IRUSR | S_IWUSR)) == -1)
				return (1);
			close(fd);
			if ((history = ft_memalloc(sizeof(char *) * nbr_ligne)) == NULL)
				return (1);
			if ((fd = open(".21sh_history", O_RDONLY)) == -1)
				return (-1);
			while ((ret = get_next_line(fd, &ligne)) > 0)
			{
				if (ret == -1)
					return (1);
				history[x] = ft_strdup(ligne);
				x++;
			}
			pos_history = (nbr_ligne - 1);
			close(fd);
			verif = 1;
		}
		x = 0;
		while (history[x] != NULL)
		{
			if (x == pos_history)
			{
			//	ft_printf("%s", history[x]);
				*cmd = ft_strdup(history[x]);
				len->len = ft_strlen(history[x]);
			}
			x++;
		}
		if ((pos_history) < nbr_ligne)
			pos_history = pos_history + 1;
	}
	return (0);
}
