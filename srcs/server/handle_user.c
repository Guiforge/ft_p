/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:20:35 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/04 16:01:50 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

static t_ftp_user	g_users[] = {
	{"toto", "toto", False},
	{"admin", "admin", True},
	{NULL, NULL, False}
};

static	t_ftp_user	*g_user = NULL;

static void			reset_user(t_ftp *context)
{
	log_debug("Reset user");
	g_user = NULL;
	context->user_log.user = NULL;
	context->user_log.pass = NULL;
	context->user_log.admin = False;
}

int					handle_user(t_ftp *context, int cs, char *cmd)
{
	size_t	i;
	char	*user_name;
	size_t	len_tmp;
	size_t	len_user;

	i = 0;
	user_name = &cmd[5];
	len_user = ft_strlen(user_name);
	reset_user(context);
	while (g_users[i].user)
	{
		len_tmp = ft_strlen(g_users[i].user);
		if (len_tmp + 1 == len_user && !ft_strncmp(g_users[i].user,\
														user_name, len_tmp))
		{
			g_user = &g_users[i];
			break ;
		}
		i++;
	}
	ftp_send(cs, FTP_MSG_NEED_PASS);
	return (0);
}

int					handle_pass(t_ftp *context, int cs, char *cmd)
{
	size_t	i;
	size_t	len;
	char	*pass;

	i = 0;
	if (!g_user)
	{
		reset_user(context);
		ftp_send(cs, FTP_MSG_KO_LOG);
		return (1);
	}
	pass = &cmd[5];
	len = ft_strlen(g_user->pass);
	if (len + 1 == ft_strlen(pass) && !ft_strncmp(g_user->pass, pass, len))
	{
		context->user_log = *g_user;
		ftp_send(cs, FTP_MSG_OK_LOG);
		return (0);
	}
	sleep(5);
	ftp_send(cs, FTP_MSG_KO_LOG);
	return (0);
}
