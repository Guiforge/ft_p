/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 10:30:34 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/21 16:29:16 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

int	ftp_err_close(int fd, enum e_logger_lvl lvl, const char *fmt, ...)
{
	va_list		list;

	close(fd);
	va_start(list, fmt);
	print(STDERR_FILENO, (char *)fmt, list);
	log_log(lvl, fmt, list);
	va_end(list);
	return (-1);
}

int	ftp_err_close_exit(int fd, enum e_logger_lvl lvl, const char *fmt, ...)
{
	va_list		list;

	close(fd);
	va_start(list, fmt);
	print(STDERR_FILENO, (char *)fmt, list);
	log_log(lvl, fmt, list);
	va_end(list);
	exit(EXIT_FAILURE);
}

int	ftp_over_cconnect(int cs, char *msg, int ret, size_t id)
{
	over(msg, 0);
	ftp_send(cs, FTP_M_ABRT, id);
	return (ret);
}
