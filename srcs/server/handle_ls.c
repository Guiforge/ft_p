/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:27:02 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/05 13:36:07 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

int		handle_ls(t_ftp_server *serv, char *cmd)
{
	(void)serv;
	(void)cmd;
	log_debug("HELLO !");
	return(0);
}