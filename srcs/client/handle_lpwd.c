/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lpwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:27:32 by guiforge          #+#    #+#             */
/*   Updated: 2019/03/12 16:39:05 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int		handle_lpwd(t_ftp_client *c, char *cmd)
{
	char		current[PATH_MAX + 1];

	(void)c;
	(void)cmd;
	ft_bzero(current, sizeof(current));
	if (!getcwd(current, PATH_MAX))
	{
		log_error("getcwd error");
		return (EXIT_FAILURE);
	}
	log_info("Local pwd is: {blue}%s{no}", current);
	return (EXIT_SUCCESS);
}