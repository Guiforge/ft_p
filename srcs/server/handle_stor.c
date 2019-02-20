/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:31:04 by guiforge          #+#    #+#             */
/*   Updated: 2019/02/20 21:07:38 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

//TODO: test if it is a dir
static int	static_handle_stor(t_ftp_server *serv, char *path)
{
	int		fd;
	ssize_t	len;
	char	buffer[2048];

	fd = open(path, O_CREAT);
	if (fd == -1)
	{
		ftp_send(serv->pi.cs, FTP_M_F_NOT_A);
		return (-1);
	}
	ftp_send(serv->pi.cs, FTP_M_OK_ODATA);
	while ((len = read(serv->dtp.cs, buffer, 2047)) && len != -1)
	{
		buffer[len - 1] = 0;
		log_debug("REC: %s -- len:%lld", buffer, len);
		if (serv->ascii)
			write(fd, ftp_newline_end(buffer), len);
		else
			write(fd, buffer, len);
	}
	close(fd);
	return (len);
}

int		handle_stor(t_ftp_server *serv, char *cmd)
{
	int		ret;

	ret = EXIT_FAILURE;
	if (ftp_serv_check(serv, cmd) && ftp_serv_accept_dtpcs(serv) != -1)
	{
		ret = static_handle_stor(serv, cmd);
		ftp_serv_close_dtp(serv);
	}
	return (ret);
}