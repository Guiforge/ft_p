/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:25:51 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/30 18:02:32 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

static pid_t	g_forks[FTP_MAC_NPROC] = {0};
static int		g_len = 0;

static int get_index_by_pid(pid_t pid)
{
	int		index;

	index = -1;
	while(index++ != FTP_MAC_NPROC)
		if (g_forks[index] == pid)
			return(index);
	return(-1);
}

void		kill_fork(pid_t pid)
{
	int		index;

	index = get_index_by_pid(pid);
	if (index == -1)
		return ;
	kill(pid, SIGTERM);
	fork_supp(pid);
}

pid_t		new_fork(void)
{
	int		ret;

	if (FTP_MAC_NPROC - 1 == g_len)
		return(-1);
	if ((ret = fork()) == -1)
		return(-1);
	g_forks[g_len] = ret;
	g_len++;
	return(ret);
}

void	fork_supp(pid_t pid)
{
	int		index;

	index = get_index_by_pid(pid);
	ft_memcpy(&g_forks[index], &g_forks[index + 1], FTP_MAC_NPROC - index);
}

void	fork_exit(pid_t pid, int ret)
{
	fork_supp(pid);
	exit(ret);
}