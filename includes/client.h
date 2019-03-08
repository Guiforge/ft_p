/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:17:46 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/02 14:44:47 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H

#include "../includes/proto.h"
#include "../includes/tools.h"

typedef struct		s_ftp_client {
	char			pwd[PATH_MAX + 1];
	int				sock;
	// t_ftp_connect	pi;
	int				dtp;
	t_bool			ascii;
}					t_ftp_client;

int		handle_syst(t_ftp_client *c, char *cmd);
int		handle_cmd(t_ftp_client *c, char *cmd);
int		handle_pwd(t_ftp_client *c, char *cmd);
int		handle_debug(t_ftp_client *c, char *cmd);
int		handle_user(t_ftp_client *c, char *cmd);
int		handle_pass(t_ftp_client *c, char *cmd);
char	*build_msg(char *cmd, char *arg, size_t *len);
int		handle_quit(t_ftp_client *c, char *cmd);
int		handle_ls(t_ftp_client *c, char *cmd);
int		ftp_c_create_dtp(t_ftp_client *c);
int		create_client(char *addr, int port);
int		handle_cwd(t_ftp_client *c, char *cmd);
int		handle_get(t_ftp_client *c, char *cmd);
int		handle_stor(t_ftp_client *c, char *cmd);
void	ftp_c_send(t_ftp_client *c, char *cmd, char *arg);
int		handle_type(t_ftp_client *c, char *cmd);
int		handle_bin(t_ftp_client *c, char *cmd);
int		handle_ascii(t_ftp_client *c, char *cmd);

#endif