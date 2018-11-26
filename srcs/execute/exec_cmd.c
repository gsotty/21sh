#include "../../include/execute.h"

#include <stdio.h>

int		len_tab_exec(char **tableau)
{
	int		x;

	x = 0;
	while (tableau[x] != NULL)
		x++;
	return (x);
}

static int		is_char(char str, char *c)
{
	int		x;

	x = 0;
	while (c[x] != '\0')
	{
		if (c[x] == str)
			return (1);
		x++;
	}
	return (0);
}

static void		ft_while(char **tab_2, char const *buf, char *c, t_split *len)
{
	int		y;
	int		fin;
	int		debut;

	y = 0;
	fin = 0;
	debut = 0;
	while (is_char(buf[y + len->j], c) == 1 && buf[y + len->j] != '\0')
		y++;
	debut = y;
	while (is_char(buf[y + len->j], c) == 0 && buf[y + len->j] != '\0')
		y++;
	fin = y;
	if (!(tab_2[len->x] = ft_memalloc(sizeof(**tab_2) * ((fin - debut) + 1))))
		return ;
	ft_memcpy(tab_2[len->x], buf + len->j + debut, fin - debut);
	tab_2[len->x][fin - debut] = '\0';
	len->j += fin;
}

char			**ft_strsplit_space(char const *buf, char *c)
{
	t_split		len;
	char		**tab_2;

	tab_2 = NULL;
	ft_memset(&len, 0, sizeof(t_split));
	if ((tab_2 = ft_memalloc(sizeof(*tab_2) * (MAX_CANON))) == NULL)
		return (NULL);
	while (buf[len.j] != '\0' && len.x < MAX_CANON)
	{
		ft_while(tab_2, buf, c, &len);
		while (is_char(buf[len.j], c) == 1 && buf[len.j] != '\0')
			len.j++;
		len.x++;
	}
	if (len.x > MAX_CANON)
	{
		write(2, "21sh: command too long:", 23);
		return (NULL);
	}
	return (tab_2);
}

char	*find_var_envp(char *name, char **my_envp)
{
	int		x;
	int		len;
	char	*p;
	char	*tmp;

	x = 0;
	if (my_envp == NULL || my_envp[0] == NULL)
		return (NULL);
	while (my_envp[x] != NULL)
	{
		tmp = ft_strdup(my_envp[x]);
		p = ft_strchr(tmp, '=');
		*p = '\0';
		len = (p - tmp);
		if (ft_strcmp(tmp, name) == 0)
			break ;
		free(tmp);
		tmp = NULL;
		x++;
	}
	if (tmp != NULL)
		free(tmp);
	if (my_envp[x] == NULL)
		return (NULL);
	return (my_envp[x] + len + 1);
}

static int		ft_exe_path(char **path, int len_cmd, int my_argc, char **my_argv, char **my_envp)
{
	int			x;
	int			len_path;
	int			nbr_path;
	char		*new_cmd;

	x = 0;
	(void)my_argc;
	nbr_path = len_tab_exec(path);
	while (x < nbr_path)
	{
		len_path = ft_strlen(path[x]);
		if (!(new_cmd = ft_memalloc(sizeof(char) * (len_path + len_cmd + 2))))
			return (1);
		ft_memcpy(new_cmd, path[x], len_path);
		ft_memcpy(new_cmd + len_path, "/", 1);
		ft_memcpy(new_cmd + len_path + 1, my_argv[0], len_cmd);
		if (access(new_cmd, F_OK | X_OK) == 0)
		{
			free(my_argv[0]);
			my_argv[0] = ft_strdup(new_cmd);
			free(new_cmd);
			execve(my_argv[0], my_argv, my_envp);
			return (0);
		}
		free(new_cmd);
		x++;
	}
	return (1);
}


void			exec_cmd(int my_argc, char **my_argv, char **my_envp)
{
	int		len_cmd;

	my_argv[my_argc] = NULL;
	len_cmd = ft_strlen(my_argv[0]);
	if (access(my_argv[0], F_OK | X_OK) == 0)
		execve(my_argv[0], my_argv, my_envp);
	else
	{
		if (ft_exe_path(ft_strsplit_space(find_var_envp("PATH", my_envp), ":"), len_cmd, my_argc, my_argv, my_envp) == 1)
		{
			write(2, "21sh: command not found: ", 25);
			write(2, my_argv[0], len_cmd);
			write(2, "\n", 1);
		}
	}
}
