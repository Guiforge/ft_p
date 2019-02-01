/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:36:14 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/01 18:24:56 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_SERVER_H
# define FT_P_SERVER_H

# include "../libft/includes/libft.h"
# include "./proto.h"
# include "./tools.h"

#define FTP_PRGM "server ftp"
#define FTP_PORT_LISTEN 42

typedef struct	s_ftp {
	char			pwd[PATH_MAX];
}				t_ftp;

void		ftp_handle_cmd(t_ftp context, int cs);
int			handle_ls(t_ftp *context, int cs, char *cmd);
int			handle_user(t_ftp *context, int cs, char *cmd);

#endif
