#ifndef BUILT_INT_H
# define BUILT_INT_H

#include "./vingt_et_un_sh.h"

typedef struct		s_flag_cd
{
	unsigned int	p_maj : 1;
	unsigned int	l_maj : 1;
	unsigned int	no_ag : 1;
	unsigned int	neg : 1;
}					t_flag_cd;

typedef struct		s_flag_env
{
	unsigned int	i_min : 1;
	unsigned int	u_min;
	char			*name;
}					t_flag_env;

typedef struct		s_intflag
{
	int				x;
	int				y;
}					t_intflag;

int					check_flag_env(char **cmd, t_flag_env *flag, char ***envp);
char				*find_var_env(char *name);
void				cd(char **argv);
void				ft_env(char **cmd, char ***envp);
void				add_env(char *name_data, char *data_var, char ***envp);
void				ft_setenv(char **cmd, char ***envp);
void				remove_env(char *name, char ***envp);
void				ft_unsetenv(char **cmd);
void				add_pwd(t_flag_cd *flag_cd, char *path);
void				add_oldpwd(t_flag_cd *flag_cd, char *path);
void				remalloc_env(char ***envp, int plus);

#endif
