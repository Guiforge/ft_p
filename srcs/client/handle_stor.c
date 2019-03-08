/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:42:13 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/08 16:21:48 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

static void	stat_read_send(t_ftp_client *c, int fd)
{
	char	line[2048];
	ssize_t	len;
	char	*buffer;

	buffer = NULL;
	while ((len = read(fd, line, 2047)) && len != -1)
	{
		line[len] = 0;
		if (c->ascii)
		{
			buffer = ftp_cr_end(line, len);
			send(c->dtp, buffer, ft_strlen(buffer), 0);
			ft_strdel(&buffer);
		}
		else
			send(c->dtp, line, len, 0);
	}
	ft_strdel(&buffer);
}

int			handle_stor(t_ftp_client *c, char *cmd)
{
	int		fd;

	fd = open(cmd, O_RDWR, 0666);
	if (fd == -1)
	{
		log_error("Cannot open %s", cmd);
		close_reset(&c->dtp);
		return (EXIT_FAILURE);
	}
	if (ftp_c_create_dtp(c) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ftp_c_send(c, "STOR ", cmd);
	if (ftp_recv(c->sock) != 150)
		return (EXIT_FAILURE);
	stat_read_send(c, fd);
	close_reset(&c->dtp);
	if (ftp_recv(c->sock) == 226)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
