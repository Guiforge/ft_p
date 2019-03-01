/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:05:13 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/01 17:53:39 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int		handle_get(t_ftp_client *c, char *cmd)
{
	char	*line;
	int		fd;
	int		ret;

	line = NULL;
	if (ftp_c_create_dtp(c) == EXIT_FAILURE)
		return(EXIT_FAILURE);
	ftp_c_send(c, "RETR ", cmd);
	if (ftp_recv(c->sock) != 150)
		return (EXIT_FAILURE);
	fd = open(cmd, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
	{
		log_error("Cannot open %s", cmd);
		close_reset(&c->dtp);
		return (EXIT_FAILURE);
	}
	while ((ret = get_next_line(c->dtp, &line)) && ret != -1)
	{
		if(c->ascii)
		{
			ft_overwrite(line, '\r', '\n', -1);
			ft_putstr_fd(line, fd);
		}
		else
			ft_putendl_fd(line, fd);
		ft_strdel(&line);
	}
	ftp_recv(c->sock);
	return (EXIT_SUCCESS);
}