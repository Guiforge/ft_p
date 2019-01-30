/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:47:04 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/30 18:18:44 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

void ftp_send(int sock, char *msg)
{
	int		ret;
	ret = send(sock, msg, ft_strlen(msg), 0);
	if (ret == -1)
	{
		log_error("send [%s] fail", msg);
		ft_dprintf(STDERR_FILENO, "send [%s] fail", msg);
	}
}