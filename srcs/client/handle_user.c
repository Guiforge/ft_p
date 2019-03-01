/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 12:00:18 by guiforge          #+#    #+#             */
/*   Updated: 2019/03/01 17:29:46 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int		handle_user(t_ftp_client *c, char *cmd)
{
	// char	*buffer;

	if (!cmd)
	{
		log_error("No user");
		return (-1);
	}
	// buffer = build_msg("USER ", cmd, NULL);
	// ftp_send(c->sock, buffer, -1);
	// ft_memdel((void **)&buffer);
	ftp_c_send(c, "USER ", cmd);
	return(ftp_recv(c->sock));
}