/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:27:02 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/11 16:43:30 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

static void ftp_send_cmd(t_ftp_server *serv, int fdin)
{
	char	buffer[2048];
	ssize_t	len;

	ft_bzero(buffer, 2048);
	ftp_send(serv->pi.cs, FTP_MSG_OK_ODATA);
	while((len = read(fdin, buffer, 2047)) && len != -1)
	{
		buffer[len - 1] = 0;
		log_debug("Send: '%s' -- %u", buffer, len);
		send(serv->dtp.cs, buffer, len, 0);
	}
	send(serv->dtp.cs, "\r", 1, 0);
	close_reset(&serv->dtp.cs);
	close_reset(&serv->dtp.sock);
	ftp_send(serv->pi.cs, FTP_MSG_CLOSE_ODATA);
}

static int ftp_run_ls_father(t_ftp_server *sev, int *pipes, pid_t pid)
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

static void ftp_run_ls_child(int *pipes, char *cmd)
{
	char **argv;

	close_reset(&pipes[0]);
	if (!(argv = ft_strsplit(cmd, ' ')) && *argv)
	{
		log_fatal("Error malloc split");
		exit(EXIT_FAILURE);
	} 
	ft_strcpy(argv[0], "ls");
	if (dup2(pipes[1], 2) !=-1 && dup2(pipes[1], 1) != -1)
		execv("/bin/ls", argv);
	else
		log_fatal("Dup2 Fail");
	ft_strdblfree(argv);
	log_fatal("Execv fail !!");
	exit(EXIT_FAILURE);
}

static int ftp_run_ls(t_ftp_server *serv, char *cmd)
{
	int		pipes[2];
	pid_t	pid;
 
	if (pipe(pipes) == -1)
		return(over_log(-1, LOG_LVL_ERROR, "pipes fail"));
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
		ftp_run_ls_child(pipes, cmd);
	return (-1);
}

int		handle_ls(t_ftp_server *serv, char *cmd)
{
	unsigned int		cslen;
	struct	sockaddr_in	csin;

	if (serv->dtp.sock == -1)
	{
		ftp_send(serv->pi.cs, FTP_MSG_ABRT);
		return (-1);
	}
	cslen = sizeof(csin);
	serv->dtp.cs = accept(serv->dtp.sock, (struct sockaddr *)&csin, &cslen);
	if (serv->dtp.cs == -1)
	{
		ftp_send(serv->pi.sock, FTP_MSG_KO_ODATA);
		close_reset(&serv->dtp.sock);
	}
	ftp_run_ls(serv, cmd);
	return(0);
}