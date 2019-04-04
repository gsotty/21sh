/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:29:50 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 16:29:51 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INT_H
# define BUILT_INT_H

# include "./vingt_et_un_sh.h"

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

typedef struct		s_builtin
{
	char			*exec;
	int				(*founction)(char **, t_envp *);
}					t_builtin;

int					cd(char **argv, t_envp *my_envp);
int					ft_env(char **cmd, t_envp *my_envp);
int					ft_setenv(char **cmd, t_envp *my_envp);
int					ft_unsetenv(char **cmd, t_envp *my_envp);
int					ft_echo(char **argv, t_envp *my_envp);

int					check_flag_env(char **cmd, t_flag_env *flag,
		t_envp *my_envp);
char				*find_var_env(char *name, t_envp *my_envp);
int					add_env(char *name_data, char *data_var, t_envp *my_envp);
int					remove_env(char *name, t_envp *my_envp);
int					add_pwd(t_flag_cd *flag_cd, char *path, t_envp *my_envp);
int					add_oldpwd(t_flag_cd *flag_cd, char *path, t_envp *my_envp);
int					remalloc_env(t_envp *my_envp, int plus);

#endif
