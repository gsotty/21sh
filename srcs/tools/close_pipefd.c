/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipefd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 11:26:25 by gsotty            #+#    #+#             */
/*   Updated: 2017/09/30 11:36:11 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../vingt_et_un_sh.h"

void	close_all(int *pipefd_int, int *pipefd_out)
{
	close(pipefd_int[0]);
	close(pipefd_out[0]);
	close(pipefd_int[1]);
	close(pipefd_out[1]);
}

void	close_tow_fd(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}
