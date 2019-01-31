/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:34:00 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/31 17:23:55 by gpouyat          ###   ########.fr       */
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

void		handle_cmd(int cs)
{
	char			*line;

	while(get_next_line(cs, &line) == 1)
	{
		ft_printf("received: [%s]\n", line);
	}
}

void		new_connection(int sock, int cs)
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
	handle_cmd(cs);
	exit(EXIT_SUCCESS);
}

int main(int ac, char **av)
{
	int					port;
	int					sock;
	int					cs;
	unsigned int		cslen;
	struct	sockaddr_in	csin;

	(void)ac;
	log_init(NULL, STDERR_FILENO);
	port = atoi(av[1]);
	sock = create_server(port);
	while (42)
	{
		cs = accept(sock, (struct sockaddr *)&csin, &cslen);
		new_connection(sock, cs);
		ft_printf("READY\n");
	}
	close(cs);
	close(sock);
}