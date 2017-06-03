/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:02:26 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/03 14:42:52 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/stat.h>

/*
** tools
*/

char				*find_var_env(char *name, char ***envp);
void				free_tab(char **tab_1);
char				***creat_env(char **envp_begin, char ***envp);
void				remalloc_env(int after_size, int new_size, char ***envp);

/*
** echo
*/

int					ft_echo(char **argv);

/*
** setenv
*/

void				ft_setenv(char **cmd, char ***envp);
void				add_env(char *data, char ***envp);

/*
** unsetenv
*/

void				ft_unsetenv(char **cmd, char ***envp);
void				remove_env(char *data, char ***envp);

/*
** cd
*/

typedef struct		s_flag_cd
{
	unsigned int	p_maj : 1;
	unsigned int	l_maj : 1;
	unsigned int	no_ag : 1;
	unsigned int	neg : 1;
}					t_flag_cd;

void				ft_cd(char **argv, char ***envp);
void				add_oldpwd(t_flag_cd *flag_cd, char *path, char ***envp);
void				add_pwd(t_flag_cd *flag_cd, char *path, char ***envp);

/*
** env
*/

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

void				ft_env(char **cmd, char ***envp);
int					check_flag_env(char **cmd, t_flag_env *flag, char ***envp);

/*
** exec
*/

void				exe_cmd(int argc, char **argv, char ***envp);
void				exe_fork(int argc, char **argv, char ***envp);

#endif
