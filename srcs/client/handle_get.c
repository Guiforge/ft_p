/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:05:13 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/11 18:24:23 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

static void	static_handle_get_read_write_bin(t_ftp_client *c, int fd)
{
	char		line[2048];
	ssize_t		ret;

	while ((ret = read(c->dtp, line, sizeof(line))) && ret != -1)
		write(fd, line, ret);
}



static void	static_handle_get_read_write(t_ftp_client *c, int fd)
{
	char	*line;
	int		ret;

	line = NULL;
	while ((ret = get_next_line(c->dtp, &line)) && ret != -1)
	{
		ft_overwrite(line, '\r', '\n', -1);
		ft_putstr_fd(line, fd);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

int			handle_get(t_ftp_client *c, char *cmd)
{
	int		fd;

	if (ftp_c_create_dtp(c) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ftp_c_send(c, "RETR ", cmd);
	if (ftp_recv(c->sock) != 150)
		return (EXIT_FAILURE);
	fd = open(cmd, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
	{
		log_error("Cannot open %s", cmd);
		close_reset(&c->dtp);
		ftp_recv(c->sock);
		return (EXIT_FAILURE);
	}
	if (c->ascii)
		static_handle_get_read_write(c, fd);
	else
		static_handle_get_read_write_bin(c, fd);
	ftp_recv(c->sock);
	return (EXIT_SUCCESS);
}
