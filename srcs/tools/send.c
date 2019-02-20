/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:47:04 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/20 11:51:54 by guiforge         ###   ########.fr       */
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

static void	static_ftp_send_log(int sock, char *msg)
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

void		ftp_send(int sock, char *msg)
{
	int		ret;
	size_t	len;

	len = ft_strlen(msg);
	ret = send(sock, msg, len, 0);
	if (ret == -1)
		log_error("send [%s] fail", msg);
	else
		static_ftp_send_log(sock, msg);
}

void		ftp_send_msg(int sock, char *code, char *msg)
{
	char	*final_msg;

	final_msg = ft_strnew(ft_strlen(msg) + 3 + 3);
	if (!final_msg)
		exit(over("ERROR MALLOC", EXIT_FAILURE));
	ft_strcat(final_msg, code);
	ft_strcat(final_msg, " ");
	ft_strcat(final_msg, msg);
	ft_strcat(final_msg, "\r\n");
	ftp_send(sock, final_msg);
	free(final_msg);
}
