/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:47:23 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/03 21:28:12 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int		handle_cwd(t_ftp_client *c, char *cmd)
{
	// char	*buffer;

	// buffer = build_msg("CWD ", cmd, NULL);
	// ftp_send(c->sock, buffer, -1);
	// ft_memdel((void **)&buffer);
	ftp_c_send(c, "CWD ", cmd);
	if (ftp_recv(c->sock) == 250)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}