/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:14:05 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/10 13:49:23 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

/*
** len path is MAX_PATH + len("257 \n\r")
*/

int		handle_pwd(t_ftp_server *serv, char *cmd)
{
	char	path[PATH_MAX + 11];
	char	pwd[PATH_MAX + 1];

	(void)cmd;
	if (!*(serv->pwd))
	{
		ftp_serv_send(serv, FTP_M_F_NOT_F);
		return (1);
	}
	ft_strcpy(path, FTP_C_OK_PWD);
	ftp_serv_get_pwd_secure(serv, pwd);
	ft_strcat(path, " \"");
	ft_strcat(path, pwd);
	ft_strcat(path, "\" \n");
	ftp_serv_send(serv, path);
	return (EXIT_SUCCESS);
}
