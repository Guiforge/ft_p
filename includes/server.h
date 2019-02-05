/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:36:14 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/05 13:34:46 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_SERVER_H
# define FT_P_SERVER_H

# include "../libft/includes/libft.h"
# include "./proto.h"
# include "./tools.h"

#define FTP_PRGM "server ftp"
#define FTP_PORT_LISTEN 42

# define FTP_MAX_LEN_CMD 256


typedef struct	s_ftp_user {
	char		*user;
	char		*pass;
	t_bool		admin;
}				t_ftp_user;

typedef struct			s_ftp_server {
	t_ftp_user			user_log;
	char				pwd[PATH_MAX];
	t_ftp_connection	pi;
	t_ftp_connection	dtp;
}						t_ftp_server;


void		ftp_serv_new_connect(t_ftp_server *serv);
void		ftp_handle_cmd(t_ftp_server *serv);
int			handle_ls(t_ftp_server *serv, char *cmd);
int			handle_user(t_ftp_server *serv, char *cmd);
int			handle_pass(t_ftp_server *serv, char *cmd);
int			handle_syst(t_ftp_server *serv, char *cmd);
int			handle_pwd(t_ftp_server *serv, char *cmd);

#endif
