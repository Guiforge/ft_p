/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dtp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 13:34:56 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/15 15:39:00 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

static char		*stat_get_ip(char *buffer, char **port)
{
	char		*start;
	char		*end;

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

static t_bool	stat_get(char *buffer, char **ip, int *port)
{
	char		*star_port;
	int			sep;

	if (!ip || !port || !buffer)
		return (False);
	*ip = stat_get_ip(buffer, &star_port);
	if (!*ip || !star_port)
	{
		log_error("Error parse IP response");
		return (False);
	}
	sep = ft_indexchr(star_port, ',');
	if (!sep || sep > 3 || !star_port[sep])
	{
		log_error("Error parse PORT response");
		return (False);
	}
	star_port[sep] = 0;
	*port = ft_atoi(star_port) << 8 | ft_atoi(&star_port[sep + 1]);
	return (True);
}

int				ftp_c_create_dtp_pasv(t_ftp_client *c)
{
	char		buffer[FTP_MAX_LEN_CMD + 1];
	int			ret;
	char		*ip;
	int			port;

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
	if ((c->dtp = create_client(c, ip, port)) == -1)
	{
		log_error("Can't Connect");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int				ftp_c_create_dtp_epsv(t_ftp_client *c)
{
	int		ret;
	char	buffer[FTP_MAX_LEN_CMD + 1];
	int		port;
	char	*start_port;

	ftp_send(c->sock, "EPSV\r\n", -1);
	ret = ft_atoi(ftp_recv_buff(c->sock, buffer, sizeof(buffer) - 1));
	ftp_msg_log(-1, buffer);
	if (!ret || ret != 229)
		return (EXIT_FAILURE);
	if (!(start_port = ft_strstr(buffer, "|||")))
	{
		log_error("Passive mode Extend erreur cannot get port or ip");
		return (EXIT_FAILURE);
	}
	start_port += 3;
	port = ft_atoi(start_port);
	if ((c->dtp = create_client(c, NULL, port)) == -1)
	{
		log_error("Can't Connect");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int				ftp_c_create_dtp(t_ftp_client *c)
{
	if (ftp_c_create_dtp_epsv(c) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (ftp_c_create_dtp_pasv(c) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
