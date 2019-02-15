/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:20:35 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/15 15:42:50 by gpouyat          ###   ########.fr       */
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

int					handle_user(t_ftp_server *serv, char *cmd)
{
	size_t			i;
	size_t			len_tmp;
	size_t			len_user;

	i = 0;
	len_user = ft_strlen(cmd);
	reset_user(serv);
	while (g_users[i].user)
	{
		len_tmp = ft_strlen(g_users[i].user);
		if (len_tmp == len_user && !ft_strncmp(g_users[i].user,\
														cmd, len_tmp))
		{
			g_user = &g_users[i];
			break ;
		}
		i++;
	}
	ftp_send(serv->pi.cs, FTP_M_NEED_PASS);
	return (0);
}

static t_bool		static_init_user(t_ftp_server *serv)
{
	char			home[PATH_MAX + 1];

	if (serv->user_log.admin)
		return (True);
	ftp_serv_get_home(serv, home);
	return (ftp_serv_mv(serv, home));
}

static int			static_handle_pass_err(t_ftp_server *serv)
{
	sleep(3);
	reset_user(serv);
	ftp_send(serv->pi.cs, FTP_M_KO_LOG);
	return (-1);
}

int					handle_pass(t_ftp_server *serv, char *cmd)
{
	size_t			i;
	size_t			len;

	i = 0;
	if (!g_user)
		return (static_handle_pass_err(serv));
	len = ft_strlen(g_user->pass);
	if (len == ft_strlen(cmd) && !ft_strncmp(g_user->pass, cmd, len))
	{
		serv->user_log = *g_user;
		if (static_init_user(serv))
			ftp_send(serv->pi.cs, FTP_M_OK_LOG);
		else
		{
			log_error("Can't mouv into of user: %s", serv->user_log.user);
			reset_user(serv);
			ftp_send(serv->pi.cs, FTP_M_KO_LOG);
		}
		return (0);
	}
	return (static_handle_pass_err(serv));
}
