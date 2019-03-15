/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:34:00 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/15 14:40:29 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

extern int g_optind;

int						create_server(char *av_port)
{
	int					port;
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in6	sin;

	if (av_port)
		port = ft_atoi(av_port);
	else
		port = 4242;
	if (!(proto = getprotobyname("tcp")))
		return (over_log(-1, LOG_LVL_ERROR, "getprotobyname(tcp)"));
	sock = socket(PF_INET6, SOCK_STREAM, proto->p_proto);
	sin.sin6_family = AF_INET6;
	sin.sin6_port = htons(port);
	sin.sin6_addr = in6addr_any;
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
	context.ascii = False;
	context.user_log = (t_ftp_user){NULL, NULL, False, NULL};
	return (context);
}

int						main(int ac, char **av)
{
	t_ftp_server		serv;
	unsigned int		cslen;
	struct sockaddr_in	csin;
	size_t				id;

	id = 0;
	if (ac > 3)
	{
		ft_dprintf(STDERR_FILENO, "usage: %s -[t] <PORT>\n", *av);
		return (EXIT_FAILURE);
	}
	if (ft_getopt(ac, (char const **)av, "t") == 't')
		log_init(NULL, STDERR_FILENO);
	serv = ftp_init();
	serv.pi.sock = create_server(av[g_optind]);
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
