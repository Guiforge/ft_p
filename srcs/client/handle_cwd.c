/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:47:23 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/08 16:09:07 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int		handle_cwd(t_ftp_client *c, char *cmd)
{
	ftp_c_send(c, "CWD ", cmd);
	if (ftp_recv(c->sock) == 250)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
