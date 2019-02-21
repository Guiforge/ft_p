/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:18:23 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/21 16:23:46 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

int		handle_syst(t_ftp_server *serv, char *cmd)
{
	(void)cmd;
	(void)serv;
	ftp_serv_send(serv, FTP_M_SYST);
	return (EXIT_SUCCESS);
}
