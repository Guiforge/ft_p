/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 15:31:59 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/15 15:41:58 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

static void	static_handle_ls_ascii(t_ftp_client *c)
{
	char	*line;
	int		ret;

	line = NULL;
	while ((ret = get_next_line(c->dtp, &line)) && ret != -1)
	{
		ft_overwrite(line, '\r', '\n', -1);
		ft_putstr(line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

static void	static_handle_ls_bin(t_ftp_client *c)
{
	char		line[2048];
	ssize_t		ret;

	while ((ret = read(c->dtp, line, sizeof(line))) && ret != -1)
		write(STDOUT_FILENO, line, ret);
}

int			handle_ls(t_ftp_client *c, char *cmd)
{
	if (ftp_c_create_dtp(c) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ftp_c_send(c, "LIST ", cmd);
	if (ftp_recv(c->sock) != 150)
	{
		close_reset(&c->dtp);
		return (EXIT_FAILURE);
	}
	if (c->ascii)
		static_handle_ls_ascii(c);
	else
		static_handle_ls_bin(c);
	close_reset(&c->dtp);
	if (ftp_recv(c->sock) == 226)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
