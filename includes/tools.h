/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:55:10 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/30 18:02:07 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "../libft/includes/libft.h"
# include <sys/socket.h>
# include <netdb.h>
# include <sys/types.h>

#define FTP_MAC_NPROC 42

void		ftp_send(int sock, char *msg);
pid_t		new_fork(void);
void		fork_supp(pid_t pid);
void		fork_exit(pid_t pid, int ret);

#endif