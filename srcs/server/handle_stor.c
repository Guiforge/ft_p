/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:31:04 by guiforge          #+#    #+#             */
/*   Updated: 2019/03/04 18:50:42 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

static int	static_handle_stor(t_ftp_server *serv, char *path)
{
	int		fd;
	char	*buffer;
	int		ret;

	buffer = NULL;
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
	{
		ftp_serv_send(serv, FTP_M_F_NOT_A);
		return (-1);
	}
	ftp_serv_send(serv, FTP_M_OK_ODATA);
	while ((ret = get_next_str(serv->dtp.cs, &buffer, FTP_CRLF)) && ret != -1)
	{
		if (!buffer)
			exit(over("Error Malloc", EXIT_FAILURE));
		if (serv->ascii)
			write(fd, ftp_newline_end(buffer), ft_strlen(buffer));
		else
			write(fd, buffer, ft_strlen(buffer));
		log_debug("RECV: Write: len:%lld", ft_strlen(buffer));
		ft_strdel(&buffer);
	}
	ft_strdel(&buffer);
	close(fd);
	return (ret);
}

int		handle_stor(t_ftp_server *serv, char *cmd)
{
	int		ret;

	ret = EXIT_FAILURE;
	if (ftp_serv_check(serv, cmd) && ftp_serv_accept_dtpcs(serv) != -1)
	{
		ret = static_handle_stor(serv, cmd);
		ftp_serv_close_dtp(serv, ret == -1 ? ret : 0);
	}
	return (ret);
}