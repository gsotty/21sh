#include "../../include/envp.h"

int		len_tab(char **tab)
{
	int		x;

	x = 0;
	while (tab[x] != NULL)
		x++;
	return (x);
}

char	**creat_envp(char **true_envp)
{
	int		len;
	int		len_arg;
	int		cont;
	char	**new_envp;

	new_envp = NULL;
	if (true_envp != NULL)
	{
		len = len_tab(true_envp);
		if ((new_envp = ft_memalloc(sizeof(char *) * (len + 1))) == NULL)
			return (NULL);
		cont = 0;
		while (true_envp[cont] != NULL)
		{
			len_arg = ft_strlen(true_envp[cont]);
			if ((new_envp[cont] = ft_memalloc(sizeof(char) * (len_arg + 1))) == NULL)
				return (NULL);
			ft_memcpy(new_envp[cont], true_envp[cont], len_arg);
			new_envp[cont][len_arg] = '\0';
			cont++;
		}
		new_envp[cont] = NULL;
	}
	return (new_envp);
}
