/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:27:02 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/10 14:38:55 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"
#include <dirent.h>


static void		send_type_ls(t_ftp_server *serv, char d_type)
{
	char	*send_type;

	send_type = NULL;
	if (d_type == DT_DIR)
		send_type = "D: ";
	else if (d_type == DT_BLK)
		send_type = "B: ";
	else if (d_type == DT_CHR)
		send_type = "C: ";
	else if (d_type == DT_FIFO)
		send_type = "P: ";
	else if (d_type == DT_LNK)
		send_type = "L: ";
	else if (d_type == DT_SOCK)
		send_type = "S: ";
	else if (d_type == DT_REG)
		send_type = "F: ";
	else
		send_type = "unknow: ";
	ftp_serv_send_data(serv, send_type, ft_strlen(send_type));
}

static int		ftp_run_ls(t_ftp_server *serv, char *cmd)
{
	char			*path;
	DIR				*dir;
	struct dirent	*dir_content;

	if (cmd)
		path = ft_secu_add(ft_exp_path(cmd, serv->pwd), M_LVL_FUNCT);
	else
		path = ft_secu_add(ft_exp_path(".", serv->pwd), M_LVL_FUNCT);
	if (ftp_serv_check(serv, path) == False)
	{
		ftp_serv_send(serv, FTP_M_F_NOT_A);
		return (EXIT_FAILURE);
	}
	if(!(dir = opendir(path)))
	{
		ftp_serv_send(serv, FTP_M_F_NOT_F);
		return (over_log(EXIT_FAILURE, LOG_LVL_ERROR, "Error open"));
	}
	ftp_serv_send(serv, FTP_M_OK_ODATA);
	while((dir_content = readdir(dir)))
	{
		if (!ft_strequ(dir_content->d_name, "..") && !ft_strequ(dir_content->d_name, "."))
		{
			send_type_ls(serv, dir_content->d_type);
			ftp_serv_send_data(serv, dir_content->d_name, ft_strlen(dir_content->d_name));
			ftp_serv_send_data(serv, "\n", 1);
		}
	}
	closedir(dir);
	ftp_serv_close_dtp(serv, 0);
	ft_secu_free(path);
	return (EXIT_SUCCESS);
}

int				handle_ls(t_ftp_server *serv, char *cmd)
{
	if (ftp_serv_accept_dtpcs(serv) != -1)
		ftp_run_ls(serv, cmd);
	return (0);
}
