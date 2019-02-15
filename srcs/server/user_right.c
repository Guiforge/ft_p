/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 17:00:35 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/15 14:32:54 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

t_bool	ftp_serv_check(t_ftp_server *serv, char *path)
{
	char		*new;
	char		home[PATH_MAX + 1];

	if (!path || !serv)
		return (False);
	ftp_serv_get_home(serv, home);
	if (serv->user_log.admin)
		return (True);
	new = ft_secu_add(ft_exp_path(path, serv->pwd), M_LVL_FUNCT);
	if (new && ft_strnequ(home, new, ft_strlen(home)))
	{
		ft_secu_free(new);
		return (True);
	}
	ft_secu_free(new);
	return (False);
}

void	ftp_serv_get_home(t_ftp_server *serv, char home[PATH_MAX + 1])
{
	ft_bzero(home, PATH_MAX + 1);
	ft_strcpy(home, serv->base);
	ft_strcat(home, "/users/");
	ft_strcat(home, serv->user_log.user);
}
