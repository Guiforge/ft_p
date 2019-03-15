/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:17:46 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/15 15:57:01 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "../includes/proto.h"
# include "../includes/tools.h"

typedef struct		s_ftp_client {
	int				sock;
	int				dtp;
	t_bool			ascii;
	struct hostent	*host;
}					t_ftp_client;

int					handle_syst(t_ftp_client *c, char *cmd);
int					handle_cmd(t_ftp_client *c, char *cmd);
int					handle_pwd(t_ftp_client *c, char *cmd);
int					handle_debug(t_ftp_client *c, char *cmd);
int					handle_user(t_ftp_client *c, char *cmd);
int					handle_pass(t_ftp_client *c, char *cmd);
char				*build_msg(char *cmd, char *arg, size_t *len);
int					handle_quit(t_ftp_client *c, char *cmd);
int					handle_ls(t_ftp_client *c, char *cmd);
int					ftp_c_create_dtp(t_ftp_client *c);
int					create_client(t_ftp_client *c, char *addr, int port);
int					handle_cwd(t_ftp_client *c, char *cmd);
int					handle_get(t_ftp_client *c, char *cmd);
int					handle_stor(t_ftp_client *c, char *cmd);
void				ftp_c_send(t_ftp_client *c, char *cmd, char *arg);
int					handle_type(t_ftp_client *c, char *cmd);
int					handle_bin(t_ftp_client *c, char *cmd);
int					handle_ascii(t_ftp_client *c, char *cmd);
int					handle_lcd(t_ftp_client *c, char *cmd);
int					handle_lls(t_ftp_client *c, char *cmd);
int					handle_lpwd(t_ftp_client *c, char *cmd);
int					handle_dele(t_ftp_client *c, char *cmd);
#endif
