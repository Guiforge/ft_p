/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:17:46 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/26 19:51:48 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H

#include "../includes/proto.h"
#include "../includes/tools.h"

typedef struct		s_ftp_client {
	char			pwd[PATH_MAX + 1];
	int				sock;
	// t_ftp_connect	pi;
	// t_ftp_connect	dtp;
	t_bool			ascii;
}					t_ftp_client;

int		handle_syst(t_ftp_client *c, char *cmd);
int		handle_cmd(t_ftp_client *c, char *cmd);
int		handle_pwd(t_ftp_client *c, char *cmd);
int		handle_debug(t_ftp_client *c, char *cmd);
int		handle_user(t_ftp_client *c, char *cmd);
int		handle_pass(t_ftp_client *c, char *cmd);
char	*build_msg(char *cmd, char *arg, size_t *len);

#endif