/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 12:00:18 by guiforge          #+#    #+#             */
/*   Updated: 2019/02/26 19:49:54 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int		handle_user(t_ftp_client *c, char *cmd)
{
	char	*buffer;

	if (!cmd)
	{
		log_error("No user");
		return (-1);
	}
	buffer = build_msg("USER ", cmd, NULL);
	ftp_send(c->sock, buffer, -1);
	ft_memdel((void **)&buffer);
	return(ftp_recv(c->sock));
}