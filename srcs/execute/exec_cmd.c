#include "../../include/execute.h"

char			*find_var_envp(char *name, char **my_envp)
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

static int		access_is_good(char **my_argv, char **my_envp, char *new_cmd)
{
	free(my_argv[0]);
	my_argv[0] = ft_strdup(new_cmd);
	free(new_cmd);
	execve(my_argv[0], my_argv, my_envp);
	return (0);
}

static int		ft_exe_path(char **path, int len_cmd, char **my_argv,
		char **my_envp)
{
	int			x;
	int			len_path;
	int			nbr_path;
	char		*new_cmd;

	x = 0;
	nbr_path = ft_tablen((const char **)path);
	while (x < nbr_path)
	{
		len_path = ft_strlen(path[x]);
		if (!(new_cmd = ft_memalloc(sizeof(char) * (len_path + len_cmd + 2))))
			return (1);
		ft_memcpy(new_cmd, path[x], len_path);
		ft_memcpy(new_cmd + len_path, "/", 1);
		ft_memcpy(new_cmd + len_path + 1, my_argv[0], len_cmd);
		if (access(new_cmd, F_OK | X_OK) == 0)
			return (access_is_good(my_argv, my_envp, new_cmd));
		free(new_cmd);
		x++;
	}
	return (1);
}

int				free_tab(char **tab)
{
	int		x;

	x = 0;
	while (tab[x] != NULL)
	{
		free(tab[x]);
		x++;
	}
	free(tab);
	return (0);
}


void			exec_cmd(int my_argc, char **my_argv, char **my_envp)
{
	int		len_cmd;
	char	**tab_path;

	my_argv[my_argc] = NULL;
	len_cmd = ft_strlen(my_argv[0]);
	if (access(my_argv[0], F_OK | X_OK) == 0)
		execve(my_argv[0], my_argv, my_envp);
	else
	{
		tab_path = ft_strsplit_space(find_var_envp("PATH", my_envp), ":");
		if (ft_exe_path(tab_path, len_cmd, my_argv, my_envp) == 1)
		{
			write(2, "21sh: command not found: ", 25);
			write(2, my_argv[0], len_cmd);
			write(2, "\n", 1);
		}
		free_tab(tab_path);
	}
}
