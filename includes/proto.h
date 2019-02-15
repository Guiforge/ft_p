/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:03:27 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/15 14:54:05 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H
# include "../libft/includes/intern/t_bool.h"

# define FTP_CODE_OK "200"
# define FTP_CODE_CLOSE "426"
# define FTP_CODE_OK_LOG "230"
# define FTP_CODE_NEED_PASS "331"
# define FTP_CODE_NEED_ACC "332"
# define FTP_CODE_KO_LOG "530"
# define FTP_CODE_TOO_LONG "500"
# define FTP_CODE_CMD_NOT "502"
# define FTP_CODE_SYST "215"
# define FTP_CODE_OK_PWD "257"
# define FTP_CODE_F_NOT_F "550"
# define FTP_CODE_QUIT "221"
# define FTP_CODE_PASV "227"
# define FTP_CODE_KO_ODATA "425"
# define FTP_CODE_OK_ODATA "150"
# define FTP_CODE_CLOSE_ODATA "226" 
# define FTP_CODE_REQU_ABRT "551"
# define FTP_CODE_REQUF_OK "250"

# define FTP_MSG_REQUF_OK FTP_CODE_REQUF_OK " Requested file action okay, completed.\r\n"
# define FTP_MSG_CLOSE_ODATA FTP_CODE_CLOSE_ODATA " Closing data connection.\r\n"
# define FTP_MSG_OK_ODATA FTP_CODE_OK_ODATA " File status okay; about to open data connection.\r\n"
# define FTP_MSG_KO_ODATA FTP_CODE_KO_ODATA " Can't open data connection.\r\n"
# define FTP_MSG_QUIT FTP_CODE_QUIT " Goodbye 👋 \r\n"
# define FTP_MSG_F_NOT_F FTP_CODE_F_NOT_F " Requested action not taken. File not found.\r\n"
# define FTP_MSG_F_NOT_A FTP_CODE_F_NOT_F " Requested action not taken. File unavailable, not access.\r\n"
# define FTP_MSG_F_NOT_D FTP_CODE_F_NOT_F " Requested action not taken. File unavailable, not directory.\r\n"
# define FTP_MSG_SYST FTP_CODE_SYST " MACOS of 42!! \r\n"
# define FTP_MSG_TOO_LONG FTP_CODE_TOO_LONG " Syntax error, command unrecognized. This may include errors such as command line too long.\r\n"
# define FTP_MSG_WELCOM FTP_CODE_OK " Welcome on this server by gpouyat!!\r\n"
# define FTP_MSG_ABRT FTP_CODE_CLOSE " Connection closed\r\n"
# define FTP_MSG_OK_LOG FTP_CODE_OK_LOG " User logged in, proceed.\r\n"
# define FTP_MSG_NEED_PASS FTP_CODE_NEED_PASS " User name okay, need password.\r\n"
# define FTP_MSG_NEED_ACC FTP_CODE_NEED_ACC " Need account for login.\r\n"
# define FTP_MSG_KO_LOG FTP_CODE_KO_LOG " Login incorrect.\r\n"
# define FTP_MSG_CMD_NOT FTP_CODE_CMD_NOT " Command not implemented.\r\n"
# define FTP_MSG_PASV FTP_CODE_PASV " Entering Passive Mode ("
# define FTP_MSG_REQU_ABRT FTP_CODE_REQU_ABRT " Requested action aborted. Page type unknown.\n"

/*
         110 Restart marker reply. In this case, the text is exact and not left to the particular implementation; it must read:      MARK yyyy = mmmm Where yyyy is User-process data stream marker, and mmmm server's equivalent marker (note the spaces between markers and "=").
         120 Service ready in nnn minutes.
         125 Data connection already open; transfer starting.
         200 Command okay.
         202 Command not implemented, superfluous at this site.
         211 System status, or system help reply.
         212 Directory status.
         213 File status.
         214 Help message. On how to use the server or the meaning of a particular non-standard command.  This reply is useful only to the human user.
         220 Service ready for new user.
         221 Service closing control connection. Logged out if appropriate.
         225 Data connection open; no transfer in progress.
         350 Requested file action pending further inform
         421 Service not available, closing control connection. This may be a reply to any command if the service knows it must shut down.
         450 Requested file action not taken. File unavailable (e.g., file busy).
         451 Requested action aborted. Local error in processing.
         452 Requested action not taken. Insufficient storage space in system.
         501 Syntax error in parameters or arguments.
         503 Bad sequence of commands.
         504 Command not implemented for that parameter.
         532 Need account for storing files.
         552 Requested file action aborted. Exceeded storage allocation (for current directory or dataset).
         553 Requested action not taken. File name not allowed.
*/

typedef struct s_ftp_cmd
{
	char	*cmd;
	int		(*handler)(void *contex, char *cmd);
	t_bool	need_log;
}			t_ftp_cmd;


#endif