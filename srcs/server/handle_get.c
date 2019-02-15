/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:11:37 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/15 18:20:48 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

static void	send_file(t_ftp_server *serv, char *path)
{
	int		fd;
	char	buffer[1048];
	ssize_t	len;
	char	*msg;

	fd = open(path, O_RDONLY);
	while((len = read(fd, buffer, 1047)) && len != -1)
	{
		buffer[len - 1] = 0;
		msg = ftp_cr_end(buffer, len);
		// TODO: CSR MODE ASCII ?
		send(serv->dtp.cs, msg, ft_strlen(msg), 0);
		free(msg);
	}
	send(serv->dtp.cs, "\r\n", 2, 0);
}

int		handle_get(t_ftp_server *serv, char *cmd)
{
	if (!ftp_serv_check(serv, cmd))
	{
		ftp_send(serv->pi.cs, FTP_M_F_NOT_A);
		return (-1);
	}
	ftp_serv_accept_dtpcs(serv);
	send_file(serv, cmd);
	ftp_serv_close_dtp(serv);
	return (EXIT_SUCCESS);
}
