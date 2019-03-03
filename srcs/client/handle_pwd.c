/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:47:48 by guiforge          #+#    #+#             */
/*   Updated: 2019/03/03 21:24:19 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int handle_pwd(t_ftp_client *c, char *cmd)
{
	(void)cmd;
	ftp_send(c->sock, "PWD\n", -1);
	if (ftp_recv(c->sock) == 257)
		return (EXIT_SUCCESS);
	return(EXIT_FAILURE);
}
