/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:56:31 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/27 21:02:16 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

static int			stat_create_client(char *addr, int port, t_ftp_client *c)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (!(proto = getprotobyname("tcp")))
		return (over("ERROR GETPROTO\n", -1));
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if (!c->host && !(c->host = gethostbyname2(addr, AF_INET)))
		return (over("gethostbyname error\n", -1));
	ft_memcpy(&(sin.sin_addr.s_addr), c->host->h_addr, % sizeof(sin.sin_addr.s_addr));
	if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
	{
		log_error("ERROR SOCK\n");
		close_reset(&sock);
		return (-1);
	}
	return (sock);
}

static int			stat_create_client6(char *addr, int port, t_ftp_client *c)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in6	sin;

	if (!(proto = getprotobyname("tcp")))
		return (over("ERROR GETPROTO\n", -1));
	sock = socket(PF_INET6, SOCK_STREAM, proto->p_proto);
	sin.sin6_family = AF_INET6;
	sin.sin6_port = htons(port);
	if (!c->host && !(c->host = gethostbyname2(addr, AF_INET6)))
		return (over("gethostbyname error\n", -1));
	ft_memcpy(&(sin.sin6_addr), c->host->h_addr, c->host->h_length);
	if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
	{
		log_error("ERROR SOCK\n");
		close_reset(&sock);
		return (-1);
	}
	return (sock);
}

int					create_client(t_ftp_client *c, char *addr, int port)
{
	int		sock;

	sock = -1;
	if (!c->host && !addr)
	{
		log_error("Error arg create_client");
		return (EXIT_FAILURE);
	}
	if (!c->host)
	{
		log_debug("test ipv6");
		sock = stat_create_client6(addr, port, c);
		if (sock == -1)
		{
			log_debug("test ipv4");
			sock = stat_create_client(addr, port, c);
		}
		return (sock);
	}
	if (c->host->h_addrtype == AF_INET6)
		sock = stat_create_client6(addr, port, c);
	else
		sock = stat_create_client(addr, port, c);
	return (sock);
}
