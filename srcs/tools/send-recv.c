/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send-recv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:47:04 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/01 14:32:34 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

static char *g_tab_log[] = {
	"Syntax",
	"Information",
	"Connection",
	"Authentification",
	"No define",
	"File system"
};

void	ftp_msg_log(ssize_t id, char *msg)
{
	void	(*inter_log)(const char *fmt, ...);
	size_t	index;

	if (!msg || !*msg)
	{
		log_fatal("message send empty");
		return ;
	}
	if (*msg == '1' || *msg == '2' || *msg == '3')
		inter_log = &log_info;
	else if (*msg == '4')
		inter_log = &log_warn;
	else
		inter_log = &log_error;
	index = msg[1] - '0';
	if (index <= 5 && id != -1)
		inter_log(FTP_LOG_SEND_FMT, id, g_tab_log[index], msg);
	else if (index <= 5)
		inter_log(FTP_LOG_RECV_FMT, g_tab_log[index], msg);
	else
		log_fatal("message not in Norme (%s)", msg);
}

void		ftp_send(int sock, char *msg, ssize_t id)
{
	int		ret;
	size_t	len;

	len = ft_strlen(msg);
	ret = send(sock, msg, len, 0);
	if (ret == -1)
		log_error("send [%s] fail", msg);
	else if (id != -1)
		ftp_msg_log(id, msg);
	else
		log_debug("Send: %s", msg);
	
}

void		ftp_send_msg(int sock, char *code, char *msg, size_t id)
{
	char	*final_msg;

	final_msg = ft_strnew(ft_strlen(msg) + 3 + 3);
	if (!final_msg)
		exit(over("ERROR MALLOC", EXIT_FAILURE));
	ft_strcat(final_msg, code);
	ft_strcat(final_msg, " ");
	ft_strcat(final_msg, msg);
	ft_strcat(final_msg, "\r\n");
	ftp_send(sock, final_msg, id);
	free(final_msg);
}

int		ftp_recv(int sock)
{
	char		buffer[FTP_MAX_LEN_CMD + 1];
	ft_bzero(buffer, FTP_MAX_LEN_CMD + 1);
	if (!ftp_recv_buff(sock, buffer, FTP_MAX_LEN_CMD))
		return (0);
	ftp_msg_log(-1, buffer);
	return (ft_atoi(buffer));
}

char	*ftp_recv_buff(int sock, char *buffer, size_t len_buff)
{
	ssize_t		len;

	len = recv(sock, buffer, len_buff, 0);
	if (len == -1)
	{
		log_error("ERROR SYSCALL RECV");
		return (NULL);
	}
	if (len == 0)
		return (NULL);
	buffer[len - 1] = 0;
	return (buffer);
}