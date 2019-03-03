/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pass.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:27:32 by guiforge          #+#    #+#             */
/*   Updated: 2019/03/03 21:25:41 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int		handle_pass(t_ftp_client *c, char *cmd)
{
	char	*msg;
	size_t	len;

	msg = build_msg("PASS ", cmd, &len);
	send(c->sock, msg, len, 0);
	ft_memdel((void **)&msg);
	if (ftp_recv(c->sock) == 230)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}