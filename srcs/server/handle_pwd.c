/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:14:05 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/05 13:43:37 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"
/*
** len path is MAX_PATH + len(257 "" \n)
*/
int		handle_pwd(t_ftp_server *serv, char *cmd)
{
	char path[PATH_MAX + 10];

	(void)cmd;
	if (!*(serv->pwd))
	{
		ftp_send(serv->pi.cs, FTP_MSG_F_NOT_F);
		return (1);
	}
	ft_strcpy(path, FTP_CODE_OK_PWD);
	ft_strcat(path, " \"");
	ft_strcat(path, serv->pwd);
	ft_strcat(path, "\" \n");
	ftp_send(serv->pi.cs, path);
	return(EXIT_SUCCESS);
}