/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:11:37 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/20 21:17:05 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

static void	send_file(t_ftp_server *serv, char *path)
{
	int		fd;
	char	buffer[1048];
	ssize_t	len;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ftp_send(serv->pi.cs, FTP_M_F_NOT_A);
		return (-1);
	}
	while((len = read(fd, buffer, 1047)) && len != -1)
	{
		buffer[len - 1] = 0;
		ftp_serv_send_data(serv, buffer, len);
	}
	ftp_serv_send_data(serv, "\n", 1);
}

int		handle_get(t_ftp_server *serv, char *cmd)
{
	if (!ftp_serv_check(serv, cmd))
	{
		ftp_send(serv->pi.cs, FTP_M_F_NOT_A);
		return (-1);
	}
	ftp_serv_accept_dtpcs(serv);
	ftp_send(serv->pi.cs, FTP_M_OK_ODATA);
	send_file(serv, cmd);
	ftp_serv_close_dtp(serv);
	return (EXIT_SUCCESS);
}
