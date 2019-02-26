/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:34:00 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/25 17:36:23 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../../includes/client.h"
int handle_syst(t_ftp_client *c, char *cmd);

static t_ftp_cmd	g_hands[] = {
	// {"TYPE", (int (*)(void *, char *))&handle_type, True},
	// {"STOR", (int (*)(void *, char *))&handle_stor, True},
	// {"CWD", (int (*)(void *, char *))&handle_cwd, True},
	// {"RETR", (int (*)(void *, char *))&handle_get, True},
	// {"QUIT", (int (*)(void *, char *))&handle_quit, False},
	// {"PASV", (int (*)(void *, char *))&handle_pasv, True},
	// {"PWD", (int (*)(void *, char *))&handle_pwd, True},
	// {"LS", (int (*)(void *, char *))&handle_ls, True},
	// {"LIST", (int (*)(void *, char *))&handle_ls, True},
	{"SYST", (int (*)(void *, char *))&handle_syst, True},
	// {"USER", (int (*)(void *, char *))&handle_user, False},
	// {"PASS", (int (*)(void *, char *))&handle_pass, False},
	{NULL, NULL, False}
};

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

int handle_syst(t_ftp_client *c, char *cmd)
{
	(void)c;
	log_debug("HELLO %s", cmd);
	//SEND
	//RECEIVE
	return (-1);
}

int	handle_cmd(t_ftp_client *c, char *cmd)
{
	size_t		i;
	char		*param;

	i = 0;
	(void)c;
	while (g_hands[i].cmd  && ft_strncmpi(g_hands[i].cmd, cmd, \
												ft_strlen(g_hands[i].cmd) - 1))
		i++;
	if (g_hands[i].cmd)
	{
		param = ft_strchr(cmd, ' ');
		if (param)
			param++;
		return (g_hands[i].handler(c, param));
	}
	ft_printf("Command not found %s\n", cmd);
	return (-1);
}

int main(int ac, char **av)
{
	int					port;
	int					sock;

	if (ac < 3 || ac > 3)
	{
		ft_dprintf(STDERR_FILENO,"usage: %s <IP> <PORT>\n", *av);
		return (EXIT_FAILURE);
	}

	log_init(NULL, STDERR_FILENO);
	port = atoi(av[2]);
	sock = create_client(av[1], port);
	
	char	*cmd;
	// size_t	len;
	while((get_next_line(STDIN_FILENO, &cmd)))
	{
		handle_cmd(NULL, cmd);
		// free(cmd);
		// send(sock, cmd, len, 0);
	}
	close(sock);
}