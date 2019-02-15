/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:31:24 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/15 18:20:35 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

static int			static_handle_cwd_error(int sock, char *msg)
{
	ftp_send(sock, msg);
	return (-1);
}

static int			static_is_dir(char *path)
{
	int		fd;

	if (!path)
		return (-1);
	fd = open(path, O_DIRECTORY | O_NOFOLLOW);
	close(fd);
	return (fd);
}

int					handle_cwd(t_ftp_server *serv, char *cmd)
{
	char		*new;
	char		home[PATH_MAX + 1];

	new = NULL;
	new = ft_secu_add(ft_exp_path(cmd, serv->pwd), M_LVL_FUNCT);
	if (!new)
		return (static_handle_cwd_error(serv->pi.cs, FTP_M_REQU_ABRT));
	ftp_serv_get_home(serv, home);
	log_debug("user: %s CWD: {blue}%s{no}", serv->user_log.user, new);
	if (!serv->user_log.admin)
	{
		if (static_is_dir(new) == -1)
			return (static_handle_cwd_error(serv->pi.cs, FTP_M_F_NOT_D));
		if (ft_strncmp(home, new, ft_strlen(home)))
			return (static_handle_cwd_error(serv->pi.cs, FTP_M_F_NOT_A));
	}
	if (chdir(new) == -1)
		return (static_handle_cwd_error(serv->pi.cs, FTP_M_F_NOT_A));
	ft_strcpy(serv->pwd, new);
	ftp_send(serv->pi.cs, FTP_M_REQUF_OK);
	ft_secu_free(new);
	return (0);
}
