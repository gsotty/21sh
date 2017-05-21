/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 16:26:09 by gsotty            #+#    #+#             */
/*   Updated: 2017/05/21 12:04:36 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vingt_et_un_sh.h"

int			main(int argc, char **argv, char **envp_begin)
{
	if (argc == 0)
		return (1);
	if (!argv)
		return (1);
	return (vingt_et_un_sh(envp_begin));
}
