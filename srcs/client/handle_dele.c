/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dele.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:47:48 by guiforge          #+#    #+#             */
/*   Updated: 2019/03/12 17:13:35 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int	handle_dele(t_ftp_client *c, char *cmd)
{
	ftp_c_send(c, "DELE ", cmd);
	if (ftp_recv(c->sock) == 250)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
