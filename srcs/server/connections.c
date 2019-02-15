/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:50:15 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/15 15:42:50 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

void	ftp_serv_new_connect(t_ftp_server *serv)
{
	int		pid;

	if (!serv || serv->pi.cs < 0)
	{
		log_error("accept error");
		return ;
	}
	if ((pid = fork()) < 0)
		return ((void)ftp_over_cconnect(serv->pi.cs, "Error fork", 0));
	else if (pid > 0)
	{
		close_reset(&(serv->pi.cs));
		return ;
	}
	close_reset(&(serv->pi.sock));
	ftp_send(serv->pi.cs, FTP_M_WELCOM);
	ftp_handle_cmd(serv);
	exit(EXIT_SUCCESS);
}

int		ftp_serv_new_sock_bind(int port)
{
	struct sockaddr_in		sin;
	int						sock;
	struct protoent			*proto;

	if (!(proto = getprotobyname("tcp")))
		return (over_log(-1, LOG_LVL_ERROR, "getprotobyname(tcp)"));
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_len = sizeof(sin);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if ((bind(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
		close_reset(&sock);
	return (sock);
}
