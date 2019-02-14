/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:20:35 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/14 17:29:58 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

/*
** There is no protection or check for wrong username:
**	- same username
**	- username with special char (\n . .. / )
**	- username too long
*/

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

t_bool ftp_serv_is_log(t_ftp_server *serv)
{
	if(serv && ft_strlen(serv->user_log.user))
		return (True);
	return (False);
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

static			t_bool static_init_user(t_ftp_server *serv)
{
	char home[PATH_MAX + 1];

	if (serv->user_log.admin)
		return (True);
	ftp_serv_get_home(serv, home);
	return (ftp_serv_mv(serv, home));
}

int					handle_pass(t_ftp_server *serv, char *cmd)
{
	size_t	i;
	size_t	len;
	char	*pass;

	i = 0;
	if (!g_user || !(cmd && cmd[0] && cmd[1] && cmd[2] && cmd[3] && cmd[4]))
	{
		reset_user(serv);
		sleep(3);
		ftp_send(serv->pi.cs, FTP_MSG_KO_LOG);
		return (-1);
	}
	pass = &cmd[5];
	len = ft_strlen(g_user->pass);
	if (len == ft_strlen(pass) && !ft_strncmp(g_user->pass, pass, len))
	{
		serv->user_log = *g_user;
		if (static_init_user(serv))
			ftp_send(serv->pi.cs, FTP_MSG_OK_LOG);
		else
		{
			log_error("Can't mouv into of user: %s", serv->user_log.user);
			reset_user(serv);
			ftp_send(serv->pi.cs, FTP_MSG_KO_LOG);
		}
		return (0);
	}
	sleep(3);
	ftp_send(serv->pi.cs, FTP_MSG_KO_LOG);
	return (-1);
}
