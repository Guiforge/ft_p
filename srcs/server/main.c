/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:34:00 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/30 18:17:21 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

int create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (!(proto = getprotobyname("tcp")))
	{
		printf("ERROR GETPROTO\n");
		return(-1);
	}
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if((bind(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
	{
		printf("ERROR SOCK\n");
		close(sock);
		exit(EXIT_FAILURE);
	}
	if (listen(sock, 42))
	{
		printf("EEORRO LISTEN\n");
		close(sock);
		exit(EXIT_FAILURE);
	}
	return (sock);
}

void		new_connection(int cs)
{
	int		pid;

	if (cs < 0)
		return ;
	if ((pid = new_fork() < 0))
		return ((void)over_p("server:", "Fork Fail", 0));
	else if (pid > 0)
	{
		close(cs);
		return ;
	}
	ftp_send(cs, FTP_MSG_WELCOM);
	fork_exit(pid, 0);
}

int main(int ac, char **av)
{
	int					port;
	int					sock;
	int					cs;
	unsigned int		cslen;
	struct	sockaddr_in	csin;
	// ssize_t				r;
	// char				buf[1024];

	(void)ac;
	port = atoi(av[1]);
	sock = create_server(port);
	while (42)
	{
		cs = accept(sock, (struct sockaddr *)&csin, &cslen);	
		new_connection(cs);
	}
	// ft_printf("send %lld\n", send(cs, "220 Welcome on this server\n", ft_strlen("220 Welcome on this server\n"), 0));
	// perror("send:");
	// while((r = read(cs, buf, 1024)))
	// {
	// 	buf[r] = 0;
	// 	printf("received: %u [%s]\n", cslen, buf);
	// }
	close(cs);
	close(sock);
}