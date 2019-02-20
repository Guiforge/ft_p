/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:24:57 by guiforge          #+#    #+#             */
/*   Updated: 2019/02/18 22:39:28 by guiforge         ###   ########.fr       */
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
		ftp_send(serv->pi.cs, FTP_M_SYTXERR);
		return (EXIT_FAILURE);
	}
	ftp_send(serv->pi.cs, FTP_M_OK);
	return (EXIT_SUCCESS);
}