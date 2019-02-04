/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:14:05 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/04 17:01:24 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"
/*
** len path is MAX_PATH + len(257 "" \n)
*/
int		handle_pwd(t_ftp *context, int cs, char *cmd)
{
	char path[PATH_MAX + 10];

	(void)cmd;
	if (!*(context->pwd))
	{
		ftp_send(cs, FTP_MSG_F_NOT_F);
		return (1);
	}
	ft_strcpy(path, FTP_CODE_OK_PWD);
	ft_strcat(path, " \"");
	ft_strcat(path, context->pwd);
	ft_strcat(path, "\" \n");
	ftp_send(cs, path);
	return(EXIT_SUCCESS);
}