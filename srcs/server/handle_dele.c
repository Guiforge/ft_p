/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dele.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:14:05 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/12 17:17:40 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

int		handle_dele(t_ftp_server *serv, char *cmd)
{
	if (!*(serv->pwd))
	{
		ftp_serv_send(serv, FTP_M_F_NOT_F);
		return (1);
	}
	if (!ftp_serv_check(serv, cmd) || unlink(cmd))
	{
		ftp_serv_send(serv, FTP_M_F_NOT_A);
		return (1);
	}
	ftp_serv_send(serv, FTP_M_REQUF_OK);
	return (EXIT_SUCCESS);
}
