/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:47:04 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/04 16:56:17 by gpouyat          ###   ########.fr       */
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

static void static_ftp_send_log(int sock, char *msg)
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
	if (index <= 5)
		inter_log(FTP_LOG_SEND_FMT, sock, g_tab_log[index], msg);
	else
		log_fatal("message not in Norme (%s)", msg);
	
}

void ftp_send(int sock, char *msg)
{
	int		ret;
	size_t	len;
	
	len = ft_strlen(msg);
	static_ftp_send_log(sock, msg);
	ret = send(sock, msg, len, 0);
	if (ret == -1)
	{
		log_error("send [%s] fail", msg);
		ft_dprintf(STDERR_FILENO, "send [%s] fail", msg);
	}
}