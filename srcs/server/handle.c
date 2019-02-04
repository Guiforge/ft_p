/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:03:24 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/04 17:12:30 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

/*
ls : liste le répertoire courant du serveur
•
cd : change le répertoire courant du serveur
•
get _file_ : récupère le fichier _file_ du serveur vers le client
•
put _file_ : envoi le fichier _file_ du client vers le serveur
*/

static void	handle_quit(t_ftp *context, int cs, char *cmd);

static t_ftp_cmd	g_hands[] = {
	{"QUIT", (int (*)(void *, int, char *))&handle_quit},
	{"PWD", (int (*)(void *, int, char *))&handle_pwd},
	{"LS", (int (*)(void *, int, char *))&handle_ls},
	{"LIST", (int (*)(void *, int, char *))&handle_ls},
	{"SYST", (int (*)(void *, int, char *))&handle_syst},
	{"USER", (int (*)(void *, int, char *))&handle_user},
	{"PASS", (int (*)(void *, int, char *))&handle_pass},
	{NULL, NULL}
};

static void	handle_quit(t_ftp *context, int cs, char *cmd)
{
	(void)cmd;
	(void)context;
	ftp_send(cs, FTP_MSG_QUIT);
	close(cs);
	exit(EXIT_SUCCESS);
}

static void	exec_handler(t_ftp context, int cs, char *cmd)
{
	size_t	i;

	i = 0;
	log_debug("received: %s", cmd);
	if (ft_strlen_max(cmd, FTP_MAX_LEN_CMD) == FTP_MAX_LEN_CMD)
	{
		ftp_send(cs, FTP_MSG_TOO_LONG);
		return ;
	}
	while(g_hands[i].cmd && ft_strncmpi(g_hands[i].cmd, cmd, ft_strlen(g_hands[i].cmd) - 1))
	{
		i++;
	}
	if(g_hands[i].cmd)
		g_hands[i].handler(&context, cs, cmd);
	else
		ftp_send(cs, FTP_MSG_CMD_NOT);
}

void		ftp_handle_cmd(t_ftp context, int cs)
{
	char			*line;
	int				ret;

	while((ret = get_next_line(cs, &line)) && ret != -1)
		exec_handler(context, cs, line);
	free(line);
}