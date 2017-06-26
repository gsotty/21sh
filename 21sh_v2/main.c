/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 10:53:29 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/26 16:53:16 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** **************************************************************************
*/

void	print_tab(char **tableau, int len_tab)
{
	int		x;

	x = 0;
	while (x < len_tab)
	{
		write(0, tableau[x], ft_strlen(tableau[x]));
		write(0, "\n", 1);
		x++;
	}
}

/*
** **************************************************************************
*/

char	**creat_envp(char **envp, int len_envp)
{
	int		x;
	int		len_envp_var;
	char	**new_envp;

	if ((new_envp = ft_memalloc(sizeof(char *) * len_envp + 1)) == NULL)
		return (NULL);
	x = 0;
	while (x < len_envp)
	{
		len_envp_var = ft_strlen(envp[x]);
		if ((new_envp[x] = ft_memalloc(sizeof(char *) * len_envp_var)) == NULL)
			return (NULL);
		ft_memcpy(new_envp[x], envp[x], len_envp_var);
		new_envp[x][len_envp_var] = '\0';
		x++;
	}
	return (new_envp);
}

int		len_tab(char **tableau)
{
	int		x;

	x = 0;
	while (tableau[x] != NULL)
	{
		x++;
	}
	return (x);
}

void	free_tab(char **tableau, int len_tab)
{
	int		x;

	x = 0;
	while (x < len_tab)
	{
		free(tableau[x]);
		tableau[x] = NULL;
		x++;
	}
	free(tableau);
}

int		f_putchar(int c)
{
	return (write(0, &c, 1));
}

int		prepare_term_tgetent(char *name_term)
{
	int				success;

	success = tgetent(NULL, name_term);
	if (success < 0)
	{
		write(2, "Could not access the termcap data base.\n", 40);
		return (1);
	}
	if (success == 0)
	{
		write(2, "Terminal type \"", 15);
		write(2, name_term, ft_strlen(name_term));
		write(2, "\" is not defined.\n", 18);
		return (1);
	}
	return (0);
}

int		modif_prepare_term(struct termios term)
{
	if (tcgetattr(0, &term) == -1)
		return (1);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (1);
	tputs(tgetstr("im", NULL), 0, f_putchar);
	return (0);
}

int		prepare_term(void)
{
	struct termios	term;
	char			*name_term;
	int				is_malloc;

	is_malloc = 0;
	if ((name_term = getenv("TERM")) == NULL)
	{
		if ((name_term = ft_memalloc(sizeof(char) * 5)) == NULL)
			return (1);
		ft_memcpy(name_term, "vt100", 5);
		name_term[5] = '\0';
		is_malloc = 1;
	}
	if (prepare_term_tgetent(name_term) != 0)
		return (1);
	if (modif_prepare_term(term) != 0)
		return (1);
	if (is_malloc == 1)
		free(name_term);
	return (0);
}

int		modif_reset_term(struct termios term)
{
	tputs(tgetstr("ei", NULL), 0, f_putchar);
	if (tcgetattr(0, &term) == -1)
		return (1);
	term.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (1);
	return (0);
}

int		reset_term(void)
{
	struct termios	term;
	char			*name_term;
	int				is_malloc;

	is_malloc = 0;
	if ((name_term = getenv("TERM")) == NULL)
	{
		if ((name_term = ft_memalloc(sizeof(char) * 5)) == NULL)
			return (1);
		ft_memcpy(name_term, "vt100", 5);
		name_term[5] = '\0';
		is_malloc = 1;
	}
	if (prepare_term_tgetent(name_term) != 0)
		return (1);
	if (modif_reset_term(term) != 0)
		return (1);
	if (is_malloc == 1)
		free(name_term);
	return (0);
	}

char	*creat_buf(char *buffer)
{
	int		x;
	int		len;
	int		pos;
	int		len_cmd_malloc;
	char	*cmd;
	char	*tmp;
	char	tmp_cmd;
	char	tmp_buf;

	len = 0;
	pos = 0;
	len_cmd_malloc = 0;
	if ((cmd = ft_memalloc(sizeof(char *) * len_cmd_malloc)) == NULL)
		return (NULL);
	ft_memset(buffer, 0, 3);
	while (!(buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0))
	{
		ft_memset(buffer, 0, 3);
		read(0, buffer, 3);
		if (len == len_cmd_malloc)
		{
			if ((tmp = ft_memalloc(sizeof(char *) * len_cmd_malloc)) == NULL)
				return (NULL);
			ft_memcpy(tmp, cmd, len_cmd_malloc);
			len_cmd_malloc += LEN_REMALLOC;
			free(cmd);
			if ((cmd = ft_memalloc(sizeof(char *) * len_cmd_malloc)) == NULL)
				return (NULL);
			ft_memcpy(cmd, tmp, (len_cmd_malloc - LEN_REMALLOC));
			free(tmp);
		}
	//	printf("%d, %d, %d\n", buffer[0], buffer[1], buffer[2]);
	//	ft_putstr(buffer);
	//	write(0, "\n", 1);
		if (buffer[0] == 4 && buffer[1] == 0 && buffer[2] == 0)
			return (NULL);
		else if (buffer[0] == 27 && buffer[1] == 0 && buffer[2] == 0)
			return (NULL);
		else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 68)
		{
			if (pos > 0)
			{
				tputs(tgetstr("le", NULL), 0, f_putchar);
				pos--;
			}
		}
		else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 67)
		{
			if (pos < len)
			{
				tputs(tgetstr("nd", NULL), 0, f_putchar);
				pos++;
			}
		}
		if (ft_isprint(buffer[0]) == 1)
		{
			if (cmd[pos] == '\0')
			{
				cmd[pos] = buffer[0];
			}
			else
			{
				x = pos;
				tmp_buf = buffer[0];
				while (x < len)
				{
					tmp_cmd = cmd[x + 1];
					cmd[x + 1] = cmd[x];
					if (tmp_buf != '\0')
						cmd[x] = tmp_buf;
					tmp_buf = tmp_cmd;
					x++;
				}
			}
			len++;
			pos++;
			write(0, buffer, 1);
		/*
			tputs(tgetstr("sc", NULL), 0, f_putchar);
			tputs(tgetstr("dl", NULL), 0, f_putchar);
			tputs(tgetstr("cr", NULL), 0, f_putchar);
			write(0, cmd, ft_strlen(cmd));
			tputs(tgetstr("rc", NULL), 0, f_putchar);
		*/
		}
	}
//	tputs(tgetstr("dl", NULL), 0, f_putchar);
//	tputs(tgetstr("cr", NULL), 0, f_putchar);
	write(0, "\n", 1);
	write(0, cmd, ft_strlen(cmd));
	write(0, "\n", 1);
	free(cmd);
	return (buffer);
}

int		main(int argc, char **argv, char **envp)
{
	int		len_envp;
	char	**tab_envp;
	char	buffer[3];

	len_envp = len_tab(envp);
	if ((tab_envp = creat_envp(envp, len_envp)) == NULL)
		return (1);
	while (1)
	{
		if (prepare_term() != 0)
			break ;
		if (creat_buf(buffer) == NULL)
			break ;
	}
	free_tab(tab_envp, len_envp);
	if (reset_term() != 0)
		return (1);
	return (0);
}
