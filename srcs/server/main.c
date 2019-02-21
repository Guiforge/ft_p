/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:34:00 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/21 16:17:49 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

int						create_server(char *av_port)
{
	int					port;
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (av_port)
		port = ft_atoi(av_port);
	else
		port = 4242;
	if (!(proto = getprotobyname("tcp")))
		return (over_log(-1, LOG_LVL_ERROR, "getprotobyname(tcp)"));
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if ((bind(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
		ftp_err_close_exit(sock, LOG_LVL_ERROR, "bind fail");
	if (listen(sock, FTP_PORT_LISTEN))
		ftp_err_close_exit(sock, LOG_LVL_ERROR, "listen %d %d fail", \
														sock, FTP_PORT_LISTEN);
	return (sock);
}

t_ftp_server			ftp_init(void)
{
	t_ftp_server		context;

	ft_memset(&context.dtp, -1, sizeof(context.dtp));
	ft_memset(&context.pi, -1, sizeof(context.pi));
	if (!getcwd(context.pwd, PATH_MAX))
	{
		log_fatal("getcwd fail");
		exit(EXIT_FAILURE);
	}
	ft_strcpy(context.base, context.pwd);
	context.ascii = True;
	return (context);
}

int						main(int ac, char **av)
{
	t_ftp_server		serv;
	unsigned int		cslen;
	struct sockaddr_in	csin;
	size_t				id;

	(void)ac;
	id = 0;
	log_init(NULL, STDERR_FILENO);
	serv = ftp_init();
	serv.pi.sock = create_server(av[1]);
	while (42)
	{
		cslen = sizeof(csin);
		serv.pi.cs = accept(serv.pi.sock, (struct sockaddr *)&csin, &cslen);
		serv.id = id++;
		ftp_serv_new_connect(&serv);
	}
	close_reset(&(serv.pi.cs));
	close_reset(&(serv.pi.sock));
}
