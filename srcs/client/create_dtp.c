/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dtp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 13:34:56 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/04 16:53:57 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

static char	*stat_get_ip(char *buffer, char **port)
{
	char	*start;
	char	*end;

	*port = NULL;
	if (!buffer || *buffer != '(' || !buffer[1])
		log_error("Passive mode erreur internal");
	ft_overwrite(buffer, ',', '.', 3);
	start = buffer + 1;
	end = ft_strchr(start, ',');
	if (!end)
		return (NULL);
	*port = end + 1;
	*end = 0;
	return (start);
}

static int	stat_get_port(char *start, int *port)
{
	int			sep;

	if (!start)
		return (False);
	sep = ft_indexchr(start, ',');
	if (!sep || sep > 3 || !start[sep])
		return (False);
	start[sep] = 0;
	*port = ft_atoi(start) << 8 | ft_atoi(&start[sep + 1]);
	return (True);
}

static t_bool stat_get(char *buffer, char **ip, int *port)
{
	char	*star_port;

	if(!ip || !port || !buffer)
		return(False);
	*ip = stat_get_ip(buffer, &star_port);
	if (!*ip)
	{
		log_error("Error parse IP response");
		return (False);
	}
	if (!stat_get_port(star_port, port))
	{
		log_error("Error parse PORT response");
		return (False);
	}
	return (True);
}

int	ftp_c_create_dtp(t_ftp_client *c)
{
	char	buffer[FTP_MAX_LEN_CMD + 1];
	int		ret;
	char	*ip;
	int		port;

	ftp_send(c->sock, "PASV\r\n", -1);
	ret = ft_atoi(ftp_recv_buff(c->sock, buffer, FTP_MAX_LEN_CMD));
	ftp_msg_log(-1, buffer);
	if (!ret || ret != 227)
	{
		log_error("Passive mode erreur: Wrong return Code");
		return (EXIT_FAILURE);
	}
	close_reset(&(c->dtp));
	if (!stat_get(ft_strchr(buffer, '('), &ip, &port))
	{
		log_error("Passive mode erreur cannot get port or ip");
		return (EXIT_FAILURE);
	}
	log_debug("Connect %s, %d", ip, port);
	c->dtp = create_client(ip, port);
	if (c->dtp == -1)
	{
		log_error("Can't Connect");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}