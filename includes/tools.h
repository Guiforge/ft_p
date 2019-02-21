/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:55:10 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/21 16:29:44 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "./proto.h"
# include "../libft/includes/libft.h"
# include <sys/socket.h>
# include <netdb.h>
# include <sys/types.h>

# define FTP_MAX_NPROC 1
# define FTP_LOG_SEND_FMT "[sock: %d] {yellow}(%s){no} %s"

typedef struct	s_ftp_connect {
	int			sock;
	int			cs;
}				t_ftp_connect;

void			ftp_send(int sock, char *msg, size_t id);
pid_t			new_fork(void);
int				ftp_err_close(int fd, enum e_logger_lvl lvl, \
														const char *fmt, ...);
int				ftp_err_close_exit(int fd, enum e_logger_lvl lvl, \
														const char *fmt, ...);
int				ftp_over_cconnect(int cs, char *msg, int ret, size_t id);
char			*ftp_get_ip(void);
char			*ftp_cr_end(char *buffer, size_t len);
char			*ftp_newline_end(char *buffer);
void			ftp_send_msg(int sock, char *code, char *msg, size_t id);

#endif
