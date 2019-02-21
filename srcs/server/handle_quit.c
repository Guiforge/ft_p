/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:18:10 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/21 16:23:46 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

int		handle_quit(t_ftp_server *serv, char *cmd)
{
	(void)cmd;
	ftp_serv_send(serv, FTP_M_QUIT);
	close_reset(&(serv->pi.cs));
	close_reset(&(serv->dtp.cs));
	close_reset(&(serv->dtp.sock));
	exit(EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
