/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 17:13:53 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/15 12:39:46 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

t_bool	ftp_serv_mv(t_ftp_server *serv, char *path)
{
	if (chdir(path) == -1)
		return (False);
	ft_strcpy(serv->pwd, path);
	return (True);
}
