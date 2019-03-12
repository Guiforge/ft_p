/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lcd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:27:32 by guiforge          #+#    #+#             */
/*   Updated: 2019/03/12 16:21:57 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

int		handle_lcd(t_ftp_client *c, char *cmd)
{
	int		ret;

	(void)c;
	if ((ret = chdir(cmd)))
		log_error("Can't local move to \"%s\"", cmd);
	return (ret);
}
