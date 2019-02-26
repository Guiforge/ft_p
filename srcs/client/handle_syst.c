/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:40:30 by guiforge          #+#    #+#             */
/*   Updated: 2019/02/26 11:40:57 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int handle_syst(t_ftp_client *c, char *cmd)
{
	(void)cmd;
	ftp_send(c->sock, "SYST\n", -1);
	ftp_recv(c->sock);
	return (-1);
}