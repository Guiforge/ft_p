/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:27:02 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/01 18:14:19 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

int		handle_ls(t_ftp *context, int cs, char *cmd)
{
	(void)context;
	(void)cs;
	(void)cmd;
	log_debug("HELLO !");
	return(0);
}