/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:34:00 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/12 16:46:01 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO: check header
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../../includes/client.h"

int			create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;
	struct hostent		*h;

	if (!(proto = getprotobyname("tcp")))
		return (over("ERROR GETPROTO\n", -1));
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if (!(h = gethostbyname(addr)))
		return (over("gethostbyname error\n", -1));
	ft_memcpy(&(sin.sin_addr.s_addr), h->h_addr, h->h_length);
	if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
	{
		log_error("ERROR SOCK\n");
		close_reset(&sock);
		return (-1);
	}
	return (sock);
}

char		*get_cmd(size_t *len)
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

static int	init_client(t_ftp_client *c)
{
	c->ascii = False;
	c->dtp = -1;
	c->sock = -1;
	return (log_init(NULL, STDERR_FILENO));
}

static void	cmd(t_ftp_client *c)
{
	char	*cmd;

	ft_putstr("ftp >> ");
	while ((get_next_line(STDIN_FILENO, &cmd)))
	{
		if (handle_cmd(c, cmd))
			ft_printf("{red}ERROR{no}\n");
		else
			ft_printf("{green}SUCCESS{no}\n");
		ft_putstr("ftp >> ");
		ft_strdel(&cmd);
	}
	ft_strdel(&cmd);
	ftp_c_send(c, "QUIT ", NULL);
	close(c->sock);
}

int			main(int ac, char **av)
{
	int					port;
	t_ftp_client		c;

	if (ac != 3)
	{
		ft_dprintf(STDERR_FILENO, "usage: %s <IP> <PORT>\n", *av);
		return (EXIT_FAILURE);
	}
	if (init_client(&c) == -1)
		return (over("Error init client", EXIT_FAILURE));
	port = ft_atoi(av[2]);
	c.sock = create_client(av[1], port);
	if (c.sock == -1)
	{
		log_error("Impossible to connect");
		exit(EXIT_FAILURE);
	}
	ftp_recv(c.sock);
	cmd(&c);
	return (0);
}
