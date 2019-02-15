/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:27:02 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/15 17:36:01 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

static void		ftp_send_cmd(t_ftp_server *serv, int fdin)
{
	char	buffer[2048];
	char	*msg;
	ssize_t	len;

	ft_bzero(buffer, 2048);
	ftp_send(serv->pi.cs, FTP_M_OK_ODATA);
	while ((len = read(fdin, buffer, 2047)) && len != -1)
	{
		buffer[len - 1] = 0;
		msg = ftp_cr_end(buffer, len);
		// TODO: CSR MODE ASCII ?
		send(serv->dtp.cs, msg, ft_strlen(msg), 0);
		free(msg);
	}
	send(serv->dtp.cs, "\r\n", 2, 0);
	ftp_serv_close_dtp(serv);
}

static int		ftp_run_ls_father(t_ftp_server *sev, int *pipes, pid_t pid)
{
	int		status;

	status = 0;
	close_reset(&pipes[1]);
	ftp_send_cmd(sev, pipes[0]);
	close_reset(&pipes[0]);
	if (wait4(pid, &status, 0, NULL) == -1)
	{
		log_fatal("Error wait4");
		return (-1);
	}
	return (WEXITSTATUS(status));
}

static void		ftp_run_ls_child(t_ftp_server *serv, int *pipes, char *cmd)
{
	char *path;

	close_reset(&pipes[0]);
	if (cmd)
		path = ft_secu_add(ft_exp_path(cmd, serv->pwd), M_LVL_FUNCT);
	else
		path = ft_secu_add(ft_exp_path(".", serv->pwd), M_LVL_FUNCT);
	if (ftp_serv_check(serv, path) == False)
	{
		ftp_send(serv->dtp.cs, FTP_M_F_NOT_A);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipes[1], 2) != -1 && dup2(pipes[1], 1) != -1)
		execl("/bin/ls", "ls", "-la", path, NULL);
	else
		log_fatal("Dup2 Fail");
	perror("exec:");
	log_fatal("Execv fail !!");
	ft_secu_free(path);
	exit(EXIT_FAILURE);
}

static int		ftp_run_ls(t_ftp_server *serv, char *cmd)
{
	int		pipes[2];
	pid_t	pid;

	if (pipe(pipes) == -1)
		return (over_log(-1, LOG_LVL_ERROR, "pipes fail"));
	if ((pid = fork()) == -1)
	{
		log_error("Fork fail!");
		close_reset(&pipes[0]);
		close_reset(&pipes[1]);
		return (-1);
	}
	else if (pid)
		return (ftp_run_ls_father(serv, pipes, pid));
	else
		ftp_run_ls_child(serv, pipes, cmd);
	return (-1);
}

int				handle_ls(t_ftp_server *serv, char *cmd)
{
	if (ftp_serv_accept_dtpcs(serv) != -1)
		log_debug("code return ls : %d", ftp_run_ls(serv, cmd));
	return (0);
}
