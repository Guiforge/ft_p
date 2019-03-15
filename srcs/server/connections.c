/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:50:15 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/15 15:42:46 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

pid_t	ftp_serv_new_connect(t_ftp_server *serv)
{
	pid_t		pid;

	if (!serv || serv->pi.cs < 0)
	{
		log_error("accept error");
		return (-1);
	}
	if ((pid = fork()) < 0)
		return (ftp_over_cconnect(serv->pi.cs, "Error fork", 0, serv->id));
	else if (pid > 0)
	{
		wait4(pid, NULL, WNOHANG, NULL);
		close_reset(&(serv->pi.cs));
		return (pid);
	}
	ftp_serv_send(serv, FTP_M_WELCOM);
	ftp_handle_cmd(serv);
	close_reset(&(serv->pi.sock));
	exit(EXIT_SUCCESS);
}

int		ftp_serv_new_sock_bind(int port)
{
	struct sockaddr_in6		sin;
	int						sock;
	struct protoent			*proto;

	if (!(proto = getprotobyname("tcp")))
		return (over_log(-1, LOG_LVL_ERROR, "getprotobyname(tcp)"));
	sock = socket(PF_INET6, SOCK_STREAM, proto->p_proto);
	sin.sin6_family = AF_INET6;
	sin.sin6_port = htons(port);
	sin.sin6_addr = in6addr_any;
	if ((bind(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
		close_reset(&sock);
	return (sock);
}

void	ftp_serv_close_dtp(t_ftp_server *serv, int is_error)
{
	if (is_error == 1)
		ftp_serv_send(serv, FTP_M_ABRT);
	else if (!is_error)
		ftp_serv_send(serv, FTP_M_CLOSE_ODATA);
	close_reset(&serv->dtp.cs);
	close_reset(&serv->dtp.sock);
}

int		ftp_serv_accept_dtpcs(t_ftp_server *serv)
{
	unsigned int		cslen;
	struct sockaddr_in	csin;

	if (serv->dtp.sock == -1)
	{
		ftp_serv_send(serv, FTP_M_ABRT);
		return (-1);
	}
	cslen = sizeof(csin);
	serv->dtp.cs = accept(serv->dtp.sock, (struct sockaddr *)&csin, &cslen);
	if (serv->dtp.cs == -1)
	{
		ftp_serv_send(serv, FTP_M_KO_ODATA);
		close_reset(&serv->dtp.sock);
	}
	return (serv->pi.cs);
}
