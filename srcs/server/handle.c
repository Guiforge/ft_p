/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:03:24 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/15 14:38:51 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

/*
.
get _file_ : récupère le fichier _file_ du serveur vers le client
•
put _file_ : envoi le fichier _file_ du client vers le serveur
*/
// RETR
static void	handle_quit(t_ftp_server *context, char *cmd);

static t_ftp_cmd	g_hands[] = {
	{"CWD", (int (*)(void *, char *))&handle_cwd, True},
	{"QUIT", (int (*)(void *, char *))&handle_quit, False},
	{"PASV", (int (*)(void *, char *))&handle_pasv, True},
	{"PWD", (int (*)(void *, char *))&handle_pwd, True},
	{"LS", (int (*)(void *, char *))&handle_ls, True},
	{"LIST", (int (*)(void *, char *))&handle_ls, True},
	{"SYST", (int (*)(void *, char *))&handle_syst, True},
	{"USER", (int (*)(void *, char *))&handle_user, False},
	{"PASS", (int (*)(void *, char *))&handle_pass, False},
	{NULL, NULL, False}
};

static void	handle_quit(t_ftp_server *serv, char *cmd)
{
	(void)cmd;
	ftp_send(serv->pi.cs, FTP_MSG_QUIT);
	close_reset(&(serv->pi.cs));
	close_reset(&(serv->dtp.cs));
	close_reset(&(serv->dtp.sock));
	exit(EXIT_SUCCESS);
}

static void	exec_handler(t_ftp_server *serv, char *cmd)
{
	size_t	i;
	char	*param;

	i = 0;
	//TODO: Void mode carriage return !!
	ft_overwrite(cmd, 13, '\0', -1);
	log_debug("received: %s", cmd);
	if (ft_strlen_max(cmd, FTP_MAX_LEN_CMD + 1) >= FTP_MAX_LEN_CMD)
	{
		ftp_send(serv->pi.cs, FTP_MSG_TOO_LONG);
		return ;
	}
	while(g_hands[i].cmd && ft_strncmpi(g_hands[i].cmd, cmd, ft_strlen(g_hands[i].cmd) - 1))
		i++;
	if(g_hands[i].cmd)
	{
		param = ft_strchr(cmd, ' ');
		if (param)
			param++;
		if (!g_hands[i].need_log || ftp_serv_is_log(serv))
			g_hands[i].handler(serv, param);
		else
			ftp_send(serv->pi.cs, FTP_MSG_NEED_ACC);
	}
	else
		ftp_send(serv->pi.cs, FTP_MSG_CMD_NOT);
}

void		ftp_handle_cmd(t_ftp_server *serv)
{
	char			*line;
	int				ret;

	while((ret = get_next_line(serv->pi.cs, &line)) && ret != -1)
		exec_handler(serv, line);
	free(line);
}