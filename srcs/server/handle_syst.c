/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:18:23 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/15 15:42:50 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

int		handle_syst(t_ftp_server *serv, char *cmd)
{
	(void)cmd;
	(void)serv;
	ftp_send(serv->pi.cs, FTP_M_SYST);
	return (EXIT_SUCCESS);
}
