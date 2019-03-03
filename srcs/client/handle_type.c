/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 12:00:18 by guiforge          #+#    #+#             */
/*   Updated: 2019/03/02 14:49:31 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int		handle_bin(t_ftp_client *c, char *cmd)
{
	(void)cmd;
	return (handle_type(c, "I"));
}

int		handle_ascii(t_ftp_client *c, char *cmd)
{
	(void)cmd;
	return (handle_type(c, "A"));
}

int		handle_type(t_ftp_client *c, char *cmd)
{
	char	c_type[2];

	if (!cmd)
		return (EXIT_FAILURE);
	c_type[0] = ft_toupper(cmd[0]);
	c_type[1] = 0;
	ftp_c_send(c, "TYPE ", c_type);
	if (ftp_recv(c->sock) != 200)
		return (EXIT_FAILURE);
	if (cmd && *cmd == 'A')
		c->ascii = True;
	else if (cmd && *cmd == 'I')
		c->ascii = False;
	return (EXIT_SUCCESS);
}