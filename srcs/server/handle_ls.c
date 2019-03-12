/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:27:02 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/12 17:23:36 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

static void		ftp_send_cmd(t_ftp_server *serv, int fdin)
{
	char	buffer[2048];
	ssize_t	len;

	ft_bzero(buffer, 2048);
	ftp_serv_send(serv, FTP_M_OK_ODATA);
	while ((len = read(fdin, buffer, sizeof(buffer) - 1)) && len != -1)
	{
		buffer[len] = 0;
		ftp_serv_send_data(serv, buffer, len);
	}
}

static int		ftp_run_ls_father(t_ftp_server *serv, int *pipes, pid_t pid)
{
	int		status;

	status = 0;
	close_reset(&pipes[1]);
	ftp_send_cmd(serv, pipes[0]);
	close_reset(&pipes[0]);
	if (wait4(pid, &status, 0, NULL) == -1)
	{
		log_fatal("Error wait4");
		return (-1);
	}
	if (WEXITSTATUS(status))
	{
		ftp_serv_close_dtp(serv, 1);
		return (WEXITSTATUS(status));
	}
	ftp_serv_close_dtp(serv, 0);
	return (0);
}

static void		ftp_run_ls_child(int *pipes, char *opt)
{
	close_reset(&pipes[0]);
	if (dup2(pipes[1], 2) != -1 && dup2(pipes[1], 1) != -1)
		execl("/bin/ls", "ls", opt, ".", NULL);
	else
		log_fatal("Dup2 Fail");
	perror("exec:");
	log_fatal("Execv fail !!");
	exit(EXIT_FAILURE);
}

static int		ftp_run_ls(t_ftp_server *serv, char *cmd)
{
	int		pipes[2];
	pid_t	pid;

	if (cmd && *cmd != '-')
		cmd = NULL;
	if (pipe(pipes) == -1)
		return (over_log(-1, LOG_LVL_ERROR, "pipes fail"));
	if ((pid = fork()) == -1)
	{
		log_error("Fork fail!");
		close_reset(&pipes[0]);
		close_reset(&pipes[1]);
		return (EXIT_FAILURE);
	}
	else if (pid)
		return (ftp_run_ls_father(serv, pipes, pid));
	else
		ftp_run_ls_child(pipes, cmd);
	return (EXIT_FAILURE);
}

int				handle_ls(t_ftp_server *serv, char *cmd)
{
	if (ftp_serv_accept_dtpcs(serv) != -1)
		log_debug("code return ls : %d", ftp_run_ls(serv, cmd));
	return (0);
}
