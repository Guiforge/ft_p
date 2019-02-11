/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pasv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 15:47:16 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/11 11:17:51 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"
#include <arpa/inet.h>

static	void ftp_serv_concate_ip_port(char buffer[64], char *addr, in_port_t port)
{
	char	*tmp;
	ft_bzero(buffer, 64);
	ft_strcat(buffer, FTP_MSG_PASV);
	ft_strcat(buffer, addr);
	ft_strcat(buffer, ",");
	tmp = ft_itoa(((port >> 8) & 0xff));
	ft_secu_add(tmp, M_LVL_FUNCT);
	ft_strcat(buffer, tmp);
	ft_strcat(buffer, ",");
	tmp = ft_itoa((port & 0xff));
	ft_secu_add(tmp, M_LVL_FUNCT);
	ft_strcat(buffer, tmp);
	ft_strcat(buffer, ")\n");
	ft_secu_free_lvl(M_LVL_FUNCT);
}


int	handle_pasv(t_ftp_server *serv)
{
	struct	sockaddr_in sin;
	socklen_t 			len;
	char				*addr;
	char				msg[64];

	serv->dtp.sock = ftp_serv_new_sock_bind(0);
	if (listen(serv->dtp.sock, FTP_PORT_LISTEN))
		close_reset(&serv->dtp.sock);
	len = sizeof(sin);
	if (getsockname(serv->dtp.sock, (struct sockaddr *)&sin, &len) == -1)
		ftp_send(serv->pi.cs, FTP_MSG_KO_ODATA);
	addr = ft_overwrite(ft_getip(), '.', ',', -1);
	if (!addr)
		ftp_send(serv->pi.cs, FTP_MSG_KO_ODATA);
	ftp_serv_concate_ip_port(msg, addr, ntohs(sin.sin_port));
	ftp_send(serv->pi.cs, msg);
	return(0);
}