/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_epsv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 15:47:16 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/15 15:50:58 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

static void	static_build_msg(char *msg, in_port_t port)
{
	char	*tmp;

	ft_strcpy(msg, "229 Entering Extend Passive Mode (");
	ft_strcat(msg, "|||");
	tmp = ft_itoa(port);
	if (!tmp)
		exit(over("ERROR MALLOC", EXIT_FAILURE));
	ft_strcat(msg, tmp);
	ft_strcat(msg, "|)\n");
}

int			handle_epsv(t_ftp_server *serv, char *cmd)
{
	struct sockaddr_in6	sin;
	socklen_t			len;
	char				msg[64];

	(void)cmd;
	close_reset(&serv->dtp.cs);
	close_reset(&serv->dtp.sock);
	serv->dtp.sock = ftp_serv_new_sock_bind(0);
	if (listen(serv->dtp.sock, FTP_PORT_LISTEN))
		close_reset(&serv->dtp.sock);
	len = sizeof(sin);
	if (getsockname(serv->dtp.sock, (struct sockaddr *)&sin, &len) == -1)
	{
		ftp_serv_send(serv, FTP_M_KO_ODATA);
		return (EXIT_FAILURE);
	}
	static_build_msg(msg, ntohs(sin.sin6_port));
	ftp_serv_send(serv, msg);
	return (0);
}
