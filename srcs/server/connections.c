/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:50:15 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/21 16:29:35 by guiforge         ###   ########.fr       */
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
	struct sockaddr_in		sin;
	int						sock;
	struct protoent			*proto;

	if (!(proto = getprotobyname("tcp")))
		return (over_log(-1, LOG_LVL_ERROR, "getprotobyname(tcp)"));
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	// Mac oS ?sin.sin_len = sizeof(sin);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if ((bind(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
		close_reset(&sock);
	return (sock);
}

void	ftp_serv_close_dtp(t_ftp_server *serv)
{
	close_reset(&serv->dtp.cs);
	close_reset(&serv->dtp.sock);
	ftp_serv_send(serv, FTP_M_CLOSE_ODATA);
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