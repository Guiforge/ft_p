/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:36:14 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/04 16:48:56 by gpouyat          ###   ########.fr       */
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

typedef struct	s_ftp {
	t_ftp_user		user_log;
	char			pwd[PATH_MAX];
}				t_ftp;




void		ftp_handle_cmd(t_ftp context, int cs);
int			handle_ls(t_ftp *context, int cs, char *cmd);
int			handle_user(t_ftp *context, int cs, char *cmd);
int			handle_pass(t_ftp *context, int cs, char *cmd);
int			handle_syst(t_ftp *context, int cs, char *cmd);
int			handle_pwd(t_ftp *context, int cs, char *cmd);

#endif
