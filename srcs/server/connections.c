/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:50:15 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/05 13:45:11 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

void		ftp_serv_new_connect(t_ftp_server *serv)
{
	int		pid;

	if (!serv || serv->pi.cs < 0)
	{
		log_error("accept error");
		return ;
	}
	if ((pid = fork()) < 0)
		return ((void)ftp_over_cconnect(serv->pi.cs, "Error fork", 0));
	else if (pid > 0)
	{
		close_reset(&(serv->pi.cs));
		return ;
	}
	close_reset(&(serv->pi.sock));
	ftp_send(serv->pi.cs, FTP_MSG_WELCOM);
	ftp_handle_cmd(serv);
	exit(EXIT_SUCCESS);
}
