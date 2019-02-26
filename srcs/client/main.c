/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:34:00 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/26 12:19:50 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../../includes/client.h"


int create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (!(proto = getprotobyname("tcp")))
	{
		printf("ERROR GETPROTO\n");
		return (-1);
	}
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
	{
		printf("ERROR SOCK\n");
		close(sock);
		exit(EXIT_FAILURE);
	}
	return (sock);
}

char	*get_cmd(size_t *len)
{
	ssize_t		len_intern;
	char		*buffer;

	buffer = ft_strnew(FTP_MAX_LEN_CMD + 1);
	if (!buffer)
	{
		log_error("Malloc Error");
		exit(EXIT_FAILURE);
	}
	len_intern = read(STDIN_FILENO, buffer, FTP_MAX_LEN_CMD);
	if (len_intern == -1 || !len_intern)
	{
		log_fatal("ERROR SYSCALL READ");
		return (NULL);
	}
	buffer[len_intern] = 0;
	if (len)
		*len = len_intern;
	return (buffer);
}


int main(int ac, char **av)
{
	int					port;
	t_ftp_client		c;

	if (ac < 3 || ac > 3)
	{
		ft_dprintf(STDERR_FILENO,"usage: %s <IP> <PORT>\n", *av);
		return (EXIT_FAILURE);
	}

	log_init(NULL, STDERR_FILENO);
	port = atoi(av[2]);
	c.sock = create_client(av[1], port);
	ftp_recv(c.sock);

	char	*cmd;
	// size_t	len;
	ft_putstr("ftp >> ");
	while((get_next_line(STDIN_FILENO, &cmd)))
	{
		handle_cmd(&c, cmd);
		ft_putstr("ftp >> ");
		ft_memdel((void **)&cmd);
	}
	ft_memdel((void **)&cmd);
	close(c.sock);
}