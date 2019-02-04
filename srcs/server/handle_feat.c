/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_feat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:18:23 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/04 16:18:52 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

int		handle_feat(t_ftp *context, int cs, char *cmd)
{
	(void)cmd;
	(void)context;
	ftp_send(cs, FTP_MSG_SYST);
	return(EXIT_SUCCESS);
}