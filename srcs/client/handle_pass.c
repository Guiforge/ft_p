/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pass.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:27:32 by guiforge          #+#    #+#             */
/*   Updated: 2019/02/26 19:51:36 by guiforge         ###   ########.fr       */
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
	return (ftp_recv(c->sock));
}