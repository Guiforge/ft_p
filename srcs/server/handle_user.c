/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:20:35 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/11 16:54:45 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

static t_ftp_user	g_users[] = {
	{"a", "a", False},
	{"toto", "toto", False},
	{"admin", "admin", True},
	{NULL, NULL, False}
};

static	t_ftp_user	*g_user = NULL;

static void			reset_user(t_ftp_server *serv)
{
	log_debug("Reset user");
	g_user = NULL;
	serv->user_log.user = NULL;
	serv->user_log.pass = NULL;
	serv->user_log.admin = False;
}

int					handle_user(t_ftp_server *serv, char *cmd)
{
	size_t	i;
	char	*user_name;
	size_t	len_tmp;
	size_t	len_user;

	i = 0;
	user_name = &cmd[5];
	len_user = ft_strlen(user_name);
	reset_user(serv);
	while (g_users[i].user)
	{
		len_tmp = ft_strlen(g_users[i].user);
		if (len_tmp == len_user && !ft_strncmp(g_users[i].user,\
														user_name, len_tmp))
		{
			g_user = &g_users[i];
			break ;
		}
		i++;
	}
	ftp_send(serv->pi.cs, FTP_MSG_NEED_PASS);
	return (0);
}

int					handle_pass(t_ftp_server *serv, char *cmd)
{
	size_t	i;
	size_t	len;
	char	*pass;

	i = 0;
	if (!g_user)
	{
		reset_user(serv);
		ftp_send(serv->pi.cs, FTP_MSG_KO_LOG);
		sleep(3);
		return (1);
	}
	pass = &cmd[5];
	len = ft_strlen(g_user->pass);
	if (len == ft_strlen(pass) && !ft_strncmp(g_user->pass, pass, len))
	{
		serv->user_log = *g_user;
		ftp_send(serv->pi.cs, FTP_MSG_OK_LOG);
		return (0);
	}
	sleep(3);
	ftp_send(serv->pi.cs, FTP_MSG_KO_LOG);
	return (0);
}
