/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:34:00 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/03 21:29:40 by gpouyat          ###   ########.fr       */
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
		log_error("ERROR SOCK\n");
		close_reset(&sock);
		//TODO: NO pas de EXIT
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

	//TODO: init
	c.ascii = True;
	c.dtp = -1;
	c.sock = -1;

	if (ac < 3 || ac > 3)
	{
		ft_dprintf(STDERR_FILENO,"usage: %s <IP> <PORT>\n", *av);
		return (EXIT_FAILURE);
	}

	log_init(NULL, STDERR_FILENO);
	port = atoi(av[2]);
	c.sock = create_client(av[1], port);
	//TODO: PAS utile
	if (c.sock == -1)
	{
		log_error("Impossible to connect");
		exit(EXIT_FAILURE);
	}
	ftp_recv(c.sock);

	char	*cmd;
	// size_t	len;
	ft_putstr("ftp >> ");
	while((get_next_line(STDIN_FILENO, &cmd)))
	{
		if (handle_cmd(&c, cmd))
			ft_printf("{red}ERROR{no}\n");
		else
			ft_printf("{green}SUCCESS{no}\n");
		ft_putstr("ftp >> ");
		ft_memdel((void **)&cmd);
	}
	ft_memdel((void **)&cmd);
	close(c.sock);
}