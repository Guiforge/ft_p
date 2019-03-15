/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 12:10:40 by guiforge          #+#    #+#             */
/*   Updated: 2019/03/15 15:40:41 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int		handle_debug(t_ftp_client *c, char *cmd)
{
	char	*buffer;

	buffer = ft_strnew(ft_strlen(cmd) + 2);
	if (!buffer)
		exit(over("ERROR MALLOC", EXIT_FAILURE));
	buffer = ft_strcpy(buffer, cmd);
	ft_strcat(buffer, "\n");
	ftp_send(c->sock, buffer, -1);
	ft_strdel(&buffer);
	if (ftp_recv(c->sock) < 400)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
