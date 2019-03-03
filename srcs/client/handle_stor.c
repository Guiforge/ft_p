/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:42:13 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/03 21:22:39 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int		handle_stor(t_ftp_client *c, char *cmd)
{
	char	line[1048];
	int		fd;
	ssize_t len;

	if (ftp_c_create_dtp(c) == EXIT_FAILURE)
		return(EXIT_FAILURE);
	ftp_c_send(c, "STOR ", cmd);
	if (ftp_recv(c->sock) != 150)
		return (EXIT_FAILURE);
	fd = open(cmd, O_RDWR, 0666);
	if (fd == -1)
	{
		log_error("Cannot open %s", cmd);
		close_reset(&c->dtp);
		return (EXIT_FAILURE);
	}
	char *buffer;
	while((len = read(fd, line, 1047)) && len != -1)
	{
		line[len - 1] = 0;
		if (c->ascii)
		{
			buffer = ftp_cr_end(line, len);
			send(c->dtp, buffer, ft_strlen(buffer), 0);
		}
		else
			send(c->dtp, buffer, ft_strlen(buffer), 0);
	}
	send(c->dtp, "\r\n", 2, 0);
	// send(c->dtp, line, len, 0);
	close_reset(&c->dtp);
	if (ftp_recv(c->sock) == 226)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}