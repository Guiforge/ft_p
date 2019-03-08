/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 15:31:59 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/08 16:13:01 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int		handle_ls(t_ftp_client *c, char *cmd)
{
	char	*line;
	int		ret;

	line = NULL;
	if (ftp_c_create_dtp(c) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ftp_c_send(c, "LIST ", cmd);
	if (ftp_recv(c->sock) != 150)
	{
		close_reset(&c->dtp);
		return (EXIT_FAILURE);
	}
	while ((ret = get_next_line(c->dtp, &line)) && ret != -1)
	{
		ft_overwrite(line, '\r', '\n', -1);
		ft_putstr(line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close_reset(&c->dtp);
	if (ftp_recv(c->sock) == 226)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
