/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:19:04 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/27 16:07:42 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

char				**g_envp;

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

typedef struct		s_split
{
	int				j;
	int				x;
}					t_split;

typedef struct		s_intflag
{
	int				x;
	int				y;
}					t_intflag;

int					minishell(char **envp_begin);
int					echo(char **argv);
int					check_flag_env(char **cmd, t_flag_env *flag);
char				*find_var_env(char *name);
char				**ft_strsplit_space(char const *s, char *c);
char				**creat_env(char **envp_begin);
void				while_minishell(int x);
void				exe(char *buf);
void				cd(char **argv);
void				add_shlvl(void);
void				print_prompt(void);
void				ft_env(char **cmd);
void				add_env(char *data);
void				free_tab(char **tab);
void				traite_signal(int s);
void				exe_cmd_no_fork(void);
void				ft_setenv(char **cmd);
void				remove_env(char *name);
void				ft_unsetenv(char **cmd);
void				traite_signal_fork(int s);
void				exe_cmd(int argc, char **argv);
void				exe_fork(int argc, char **argv);
void				add_pwd(t_flag_cd *flag_cd, char *path);
void				add_oldpwd(t_flag_cd *flag_cd, char *path);
void				remalloc_env(int after_size, int new_size);

#endif
