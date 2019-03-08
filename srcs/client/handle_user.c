/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 12:00:18 by guiforge          #+#    #+#             */
/*   Updated: 2019/03/08 16:22:34 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int		handle_user(t_ftp_client *c, char *cmd)
{
	if (!cmd)
	{
		log_error("No user");
		return (-1);
	}
	ftp_c_send(c, "USER ", cmd);
	if (ftp_recv(c->sock) == 331)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
