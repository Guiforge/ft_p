/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:47:23 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/01 17:28:25 by gpouyat          ###   ########.fr       */
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
	return(ftp_recv(c->sock));
}