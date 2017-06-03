/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 16:26:09 by gsotty            #+#    #+#             */
/*   Updated: 2017/06/03 15:21:52 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vingt_et_un_sh.h"
#include "../includes/builtin.h"

int			main(int argc, char **argv, char **envp_begin)
{
	char	***envp;

	if (argc == 0)
		return (1);
	if (!argv)
		return (1);
	envp = creat_env(envp_begin, envp);
	return (vingt_et_un_sh(argc, argv, envp));
}
