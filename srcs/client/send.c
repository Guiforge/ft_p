/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:12:48 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/04 16:29:38 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

void	ftp_c_send(t_ftp_client *c, char *cmd, char *arg)
{
	char	*buffer;

	if (!cmd)
		return ;
	buffer = build_msg(cmd, arg, NULL);
	if (!buffer)
		exit(over("ERROR MALLOC", EXIT_FAILURE));
	ftp_send(c->sock, buffer, -1);
	ft_strdel(&buffer);
}