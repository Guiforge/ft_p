/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:03:27 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/15 15:57:41 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H
# include "../libft/includes/intern/t_bool.h"

# ifdef __APPLE__
#  define FTP_OS "MACOS"
# else
#  define FTP_OS "Linux"
# endif

# define FTP_C_OK "200"
# define FTP_C_CLOSE "426"
# define FTP_C_OK_LOG "230"
# define FTP_C_NEED_PASS "331"
# define FTP_C_NEED_ACC "332"
# define FTP_C_KO_LOG "530"
# define FTP_C_TOO_LONG "500"
# define FTP_C_CMD_NOT "502"
# define FTP_C_SYST "215"
# define FTP_C_OK_PWD "257"
# define FTP_C_F_NOT_F "550"
# define FTP_C_QUIT "221"
# define FTP_C_PASV "227"
# define FTP_C_KO_ODATA "425"
# define FTP_C_OK_ODATA "150"
# define FTP_C_CLOSE_ODATA "226"
# define FTP_C_REQU_ABRT "551"
# define FTP_C_REQUF_OK "250"
# define FTP_C_ODATAY "125"
# define FTP_C_SYTXERR "501"

# define FTP_M_SYTXERR FTP_C_SYTXERR " Syntax error in parameters\r\n"
# define FTP_M_OK FTP_C_OK " Ok\r\n"
# define FTP_M_ODATAY FTP_C_ODATAY " Data connection already open\r\n"
# define FTP_M_REQUF_OK FTP_C_REQUF_OK " Completed.\r\n"
# define FTP_M_CLOSE_ODATA FTP_C_CLOSE_ODATA " Closing data connection.\r\n"
# define FTP_M_OK_ODATA FTP_C_OK_ODATA " File status okay\r\n"
# define FTP_M_KO_ODATA FTP_C_KO_ODATA " Can't open data connection.\r\n"
# define FTP_M_QUIT FTP_C_QUIT " Goodbye 👋 \r\n"
# define FTP_M_F_NOT_F FTP_C_F_NOT_F " File not found.\r\n"
# define FTP_M_F_NOT_A FTP_C_F_NOT_F " File unavailable, not access.\r\n"
# define FTP_M_F_NOT_D FTP_C_F_NOT_F " File unavailable, not directory.\r\n"
# define FTP_M_SYST FTP_C_SYST " " FTP_OS " of 42!! \r\n"
# define FTP_M_TOO_LONG FTP_C_TOO_LONG " Command line too long.\r\n"
# define FTP_M_WELCOM FTP_C_OK " Welcome on this server by gpouyat!!\r\n"
# define FTP_M_ABRT FTP_C_CLOSE " Connection closed\r\n"
# define FTP_M_OK_LOG FTP_C_OK_LOG " User logged in, proceed.\r\n"
# define FTP_M_NEED_PASS FTP_C_NEED_PASS " User name okay, need password.\r\n"
# define FTP_M_NEED_ACC FTP_C_NEED_ACC " Need account for login.\r\n"
# define FTP_M_KO_LOG FTP_C_KO_LOG " Login incorrect.\r\n"
# define FTP_M_CMD_NOT FTP_C_CMD_NOT " Command not implemented.\r\n"
# define FTP_M_PASV FTP_C_PASV " Entering Passive Mode ("
# define FTP_M_REQU_ABRT FTP_C_REQU_ABRT " Requested action aborted.\n"

# define FTP_CRLF "\r\n"

typedef struct	s_ftp_cmd
{
	char		*cmd;
	int			(*handler)(void *contex, char *cmd);
	t_bool		need_log;
}				t_ftp_cmd;

# define FTP_MAX_LEN_CMD 256

#endif
