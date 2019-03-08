/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:40:30 by guiforge          #+#    #+#             */
/*   Updated: 2019/03/08 16:22:14 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int	handle_syst(t_ftp_client *c, char *cmd)
{
	(void)cmd;
	ftp_send(c->sock, "SYST\n", -1);
	if (ftp_recv(c->sock) == 215)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
