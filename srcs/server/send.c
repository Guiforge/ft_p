/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 22:25:04 by guiforge          #+#    #+#             */
/*   Updated: 2019/02/21 16:28:23 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

ssize_t     ftp_serv_send_data(t_ftp_server *serv, char *buffer, size_t len_buffer)
{
	char	*msg;
	ssize_t	ret;

	if (serv->ascii)
	{
		msg = ftp_cr_end(buffer, len_buffer);
		ret = send(serv->dtp.cs, msg, ft_strlen(msg), 0);
		free(msg);
	}
	else
	{
		if (len_buffer)
			ret = send(serv->dtp.cs, buffer, len_buffer, 0);
		else
			ret = send(serv->dtp.cs, buffer, ft_strlen(buffer), 0);
		
	}
	return (ret);
}

void	ftp_serv_send(t_ftp_server *serv, char *msg)
{
	ftp_send(serv->pi.cs, msg, serv->id);
}

void	ftp_serv_send_msg(t_ftp_server *serv, char *code, char *msg)
{
	ftp_send_msg(serv->pi.cs, code, msg, serv->id);
}