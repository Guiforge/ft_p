/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:18:10 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/15 15:42:50 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

int		handle_quit(t_ftp_server *serv, char *cmd)
{
	(void)cmd;
	ftp_send(serv->pi.cs, FTP_M_QUIT);
	close_reset(&(serv->pi.cs));
	close_reset(&(serv->dtp.cs));
	close_reset(&(serv->dtp.sock));
	exit(EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
