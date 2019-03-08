/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:11:37 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/08 16:04:27 by gpouyat          ###   ########.fr       */
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
		ftp_serv_send(serv, FTP_M_F_NOT_A);
		return ;
	}
	while ((len = read(fd, buffer, sizeof(buffer) - 1)) && len != -1)
	{
		buffer[len] = 0;
		ftp_serv_send_data(serv, buffer, len);
	}
}

int		handle_get(t_ftp_server *serv, char *cmd)
{
	if (!ftp_serv_check(serv, cmd))
	{
		ftp_serv_send(serv, FTP_M_F_NOT_A);
		return (-1);
	}
	ftp_serv_accept_dtpcs(serv);
	ftp_serv_send(serv, FTP_M_OK_ODATA);
	send_file(serv, cmd);
	ftp_serv_close_dtp(serv, 0);
	return (EXIT_SUCCESS);
}
