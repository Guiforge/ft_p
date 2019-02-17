/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:36:14 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/15 18:15:42 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_SERVER_H
# define FT_P_SERVER_H

# include "../libft/includes/libft.h"
# include "./proto.h"
# include "./tools.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>

# define FTP_PRGM "server ftp"
# define FTP_PORT_LISTEN 42

# define FTP_MAX_LEN_CMD 256

typedef struct		s_ftp_user {
	char			*user;
	char			*pass;
	t_bool			admin;
}					t_ftp_user;

typedef struct		s_ftp_server {
	t_ftp_user		user_log;
	char			pwd[PATH_MAX + 1];
	char			base[PATH_MAX + 1];
	t_ftp_connect	pi;
	t_ftp_connect	dtp;
}					t_ftp_server;

# define FTP_BACKLOG 42

int					ftp_serv_accept_dtpcs(t_ftp_server *serv);
void				ftp_serv_close_dtp(t_ftp_server *serv);
t_bool				ftp_serv_is_log(t_ftp_server *serv);
int					ftp_serv_new_sock_bind(int port);
void				ftp_serv_new_connect(t_ftp_server *serv);
void				ftp_handle_cmd(t_ftp_server *serv);
int					handle_ls(t_ftp_server *serv, char *cmd);
int					handle_user(t_ftp_server *serv, char *cmd);
int					handle_pass(t_ftp_server *serv, char *cmd);
int					handle_syst(t_ftp_server *serv, char *cmd);
int					handle_pwd(t_ftp_server *serv, char *cmd);
int					handle_pasv(t_ftp_server *serv, char *cmd);
int					handle_cwd(t_ftp_server *serv, char *cmd);
int					handle_quit(t_ftp_server *serv, char *cmd);
int					handle_get(t_ftp_server *serv, char *cmd);
void				ftp_serv_get_home(t_ftp_server *serv,\
													char home[PATH_MAX + 1]);
t_bool				ftp_serv_check(t_ftp_server *serv, char *path);
t_bool				ftp_serv_mv(t_ftp_server *serv, char *path);

#endif
