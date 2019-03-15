/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:31:04 by guiforge          #+#    #+#             */
/*   Updated: 2019/03/15 15:53:57 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

static int	static_handle_stor_open(t_ftp_server *serv, char *path)
{
	int		fd;

	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
	{
		ftp_serv_send(serv, FTP_M_F_NOT_A);
		return (-1);
	}
	ftp_serv_send(serv, FTP_M_OK_ODATA);
	return (fd);
}

static int	static_handle_stor_ascii(t_ftp_server *serv, char *path)
{
	int		fd;
	char	*buffer;
	int		ret;

	buffer = NULL;
	if ((fd = static_handle_stor_open(serv, path)) == -1)
		return (-1);
	while ((ret = get_next_str(serv->dtp.cs, &buffer, FTP_CRLF)) && ret != -1)
	{
		if (!buffer)
			exit(over("Error Malloc", EXIT_FAILURE));
		if (serv->ascii)
			write(fd, ftp_newline_end(buffer), ft_strlen(buffer));
		ft_strdel(&buffer);
	}
	ft_strdel(&buffer);
	close(fd);
	return (ret);
}

static int	static_handle_stor_bin(t_ftp_server *serv, char *path)
{
	int			fd;
	char		buffer[2048];
	ssize_t		ret;

	ret = 0;
	if ((fd = static_handle_stor_open(serv, path)) == -1)
		return (-1);
	while ((ret = read(serv->dtp.cs, buffer, sizeof(buffer))) && ret != -1)
		write(fd, buffer, ret);
	close(fd);
	return (ret == -1 ? -1 : 0);
}

int			handle_stor(t_ftp_server *serv, char *cmd)
{
	int		ret;

	ret = EXIT_FAILURE;
	if (ftp_serv_check(serv, cmd) && ftp_serv_accept_dtpcs(serv) != -1)
	{
		if (serv->ascii)
			ret = static_handle_stor_ascii(serv, cmd);
		else
			ret = static_handle_stor_bin(serv, cmd);
		ftp_serv_close_dtp(serv, ret == -1 ? ret : 0);
	}
	return (ret);
}
