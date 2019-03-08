/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 13:30:22 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/08 16:21:27 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int	handle_quit(t_ftp_client *c, char *cmd)
{
	(void)cmd;
	ftp_send(c->sock, "QUIT\n", -1);
	ftp_recv(c->sock);
	close_reset(&(c->sock));
	exit(EXIT_SUCCESS);
}
