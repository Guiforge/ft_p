/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:22:24 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/12 16:33:02 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"
//TODO: check header
      #include <sys/types.h>
       #include <sys/time.h>
       #include <sys/resource.h>
       #include <sys/wait.h>

static void		ftp_send_cmd(int fdin)
{
	char	buffer[2048];
	ssize_t	len;

	while ((len = read(fdin, buffer, sizeof(buffer))) && len != -1)
	{
		if (write(STDOUT_FILENO, buffer, len) == -1)
			log_error("Syscall error: write");
	}
}

static int		ftp_run_ls_father(int *pipes, pid_t pid)
{
	int		status;

	status = 0;
	close_reset(&pipes[1]);
	ftp_send_cmd(pipes[0]);
	close_reset(&pipes[0]);
	if (wait4(pid, &status, 0, NULL) == -1)
	{
		log_fatal("Error wait4");
		return (-1);
	}
	if (WEXITSTATUS(status))
		return (WEXITSTATUS(status));
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

static int		ftp_run_ls(char *cmd)
{
	int		pipes[2];
	pid_t	pid;

	if (cmd && *cmd != '-')
		cmd = NULL;
	if (pipe(pipes) == -1)
		return (over_log(1, LOG_LVL_ERROR, "pipes fail"));
	if ((pid = fork()) == -1)
	{
		log_error("Fork fail!");
		close_reset(&pipes[0]);
		close_reset(&pipes[1]);
		return (EXIT_FAILURE);
	}
	else if (pid)
		return (ftp_run_ls_father(pipes, pid));
	else
		ftp_run_ls_child(pipes, cmd);
	return (EXIT_FAILURE);
}

int				handle_lls(t_ftp_client *c, char *cmd)
{
	(void)c;
	return (ftp_run_ls(cmd));
}
