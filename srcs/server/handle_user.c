/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:20:35 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/01 18:54:19 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"


int		handle_user(t_ftp *context, int cs, char *cmd)
{
	(void)context;
	log_info("HELLO %s!", cmd + 4);
	// ftp_send(cs, FTP_MSG_NEED_PASS);
	ftp_send(cs, FTP_MSG_OK_LOG);
	return(0);
}