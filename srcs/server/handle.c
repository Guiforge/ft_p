/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:03:24 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/15 14:54:44 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

static t_ftp_cmd	g_hands[] = {
	{"TYPE", (int (*)(void *, char *))&handle_type, True},
	{"STOR", (int (*)(void *, char *))&handle_stor, True},
	{"CWD", (int (*)(void *, char *))&handle_cwd, True},
	{"RETR", (int (*)(void *, char *))&handle_get, True},
	{"QUIT", (int (*)(void *, char *))&handle_quit, False},
	{"PASV", (int (*)(void *, char *))&handle_pasv, True},
	{"PWD", (int (*)(void *, char *))&handle_pwd, True},
	{"LS", (int (*)(void *, char *))&handle_ls, True},
	{"LIST", (int (*)(void *, char *))&handle_ls, True},
	{"SYST", (int (*)(void *, char *))&handle_syst, True},
	{"USER", (int (*)(void *, char *))&handle_user, False},
	{"PASS", (int (*)(void *, char *))&handle_pass, False},
	{"EPSV", (int (*)(void *, char *))&handle_epsv, True},
	{"DELE", (int (*)(void *, char *))&handle_dele, True},
	{"UNLINK", (int (*)(void *, char *))&handle_dele, True},
	{NULL, NULL, False}
};

static void	check_cmd(t_ftp_server *serv, char *cmd)
{
	ft_overwrite(cmd, '\r', '\0', -1);
	log_debug("received: %s", cmd);
	if (ft_strlen_max(cmd, FTP_MAX_LEN_CMD + 1) >= FTP_MAX_LEN_CMD)
	{
		ftp_serv_send(serv, FTP_M_TOO_LONG);
		return ;
	}
}

static void	exec_handler(t_ftp_server *serv, char *cmd)
{
	size_t	i;
	char	*param;

	i = 0;
	check_cmd(serv, cmd);
	while (g_hands[i].cmd && ft_strncmpi(g_hands[i].cmd, cmd, \
												ft_strlen(g_hands[i].cmd) - 1))
		i++;
	if (g_hands[i].cmd)
	{
		param = ft_strchr(cmd, ' ');
		if (param)
			param++;
		if (!g_hands[i].need_log || ftp_serv_is_log(serv))
			g_hands[i].handler(serv, param);
		else
			ftp_serv_send(serv, FTP_M_NEED_ACC);
	}
	else
		ftp_serv_send(serv, FTP_M_CMD_NOT);
}

void		ftp_handle_cmd(t_ftp_server *serv)
{
	char			*line;
	int				ret;

	line = NULL;
	while ((ret = get_next_line(serv->pi.cs, &line)) && ret != -1)
	{
		exec_handler(serv, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}
