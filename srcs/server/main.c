/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:34:00 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/01 18:22:41 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

int create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (!(proto = getprotobyname("tcp")))
		return(over_log(-1, LOG_LVL_ERROR, "getprotobyname(tcp)"));
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if((bind(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
		ftp_err_close_exit(sock, LOG_LVL_ERROR, "bind fail");
	if (listen(sock, FTP_PORT_LISTEN))
		ftp_err_close_exit(sock, LOG_LVL_ERROR, "listen %d %d fail", sock, FTP_PORT_LISTEN);
	return (sock);
}


void		new_connection(t_ftp context, int sock, int cs)
{
	int		pid;

	if (cs < 0)
	{
		log_error("accept error");
		return ;
	}
	if ((pid = fork()) < 0)
		return ((void)ftp_over_cconnect(cs, "Error fork", 0));
	else if (pid > 0)
	{
		close(cs);
		return ;
	}
	close(sock);
	ftp_send(cs, FTP_MSG_WELCOM);
	ftp_handle_cmd(context, cs);
	exit(EXIT_SUCCESS);
}

t_ftp	ftp_init(void)
{
	t_ftp	context;

	if(!getcwd(context.pwd, PATH_MAX))
	{
		log_fatal("getcwd fail");
		exit(EXIT_FAILURE);
	}
	return (context);
}

int main(int ac, char **av)
{
	int					port;
	int					sock;
	int					cs;
	unsigned int		cslen;
	struct	sockaddr_in	csin;

	t_ftp context = ftp_init();
	(void)ac;
	log_init(NULL, STDERR_FILENO);
	port = atoi(av[1]);
	sock = create_server(port);
	while (42)
	{
		cs = accept(sock, (struct sockaddr *)&csin, &cslen);
		new_connection(context, sock, cs);
		ft_printf("READY\n");
	}
	close(cs);
	close(sock);
}