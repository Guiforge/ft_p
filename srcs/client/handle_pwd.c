/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:47:48 by guiforge          #+#    #+#             */
/*   Updated: 2019/02/26 12:18:09 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int handle_pwd(t_ftp_client *c, char *cmd)
{
	(void)cmd;
	ftp_send(c->sock, "PWD\n", -1);
	return(ftp_recv(c->sock));
}
