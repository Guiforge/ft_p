/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:24:57 by guiforge          #+#    #+#             */
/*   Updated: 2019/03/15 15:54:20 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

int		handle_type(t_ftp_server *serv, char *cmd)
{
	if (cmd && *cmd == 'A')
		serv->ascii = True;
	else if (cmd && *cmd == 'I')
		serv->ascii = False;
	else
	{
		ftp_serv_send(serv, FTP_M_SYTXERR);
		return (EXIT_FAILURE);
	}
	ftp_serv_send(serv, FTP_M_OK);
	return (EXIT_SUCCESS);
}
