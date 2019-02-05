/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:55:10 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/05 11:42:36 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "./proto.h"
# include "../libft/includes/libft.h"
# include <sys/socket.h>
# include <netdb.h>
# include <sys/types.h>

#define FTP_MAX_NPROC 1
#define FTP_LOG_SEND_FMT "[sock: %d] {yellow}(%s){no} %s"

typedef struct s_ftp_connection {
	int		sock;
	int		cs;
}				t_ftp_connection;

void		ftp_send(int sock, char *msg);
pid_t		new_fork(void);
int			ftp_err_close(int fd, enum e_logger_lvl lvl, const char *fmt, ...);
int			ftp_err_close_exit(int fd, enum e_logger_lvl lvl, const char *fmt, ...);
int			ftp_over_cconnect(int cs, char *msg, int ret);

#endif