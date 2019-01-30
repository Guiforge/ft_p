/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:34:00 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/30 17:58:38 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../../includes/server.h"

int create_client(char *addr, int port)
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
	sin.sin_addr.s_addr = inet_addr(addr);
	if((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
	{
		printf("ERROR SOCK\n");
		close(sock);
		exit(EXIT_FAILURE);
	}
	return (sock);
}

int main(int ac, char **av)
{
	int					port;
	int					sock;

	(void)ac;
	port = atoi(av[2]);
	sock = create_client(av[1], port);
	char *line;
	line = NULL;
	

	char b[1024];
	ssize_t r;
	while((r = read(sock, b, 1023)))
	{
		b[r] = 0;
		printf("received: %zd [%s]\n", r, b);
	}

	get_next_line(STDIN_FILENO, &line);
	write(sock, line, ft_strlen(line));
	close(sock);
}