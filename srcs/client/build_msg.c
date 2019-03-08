/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:33:39 by guiforge          #+#    #+#             */
/*   Updated: 2019/03/08 16:06:34 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

char	*build_msg(char *cmd, char *arg, size_t *len)
{
	char	*buffer;

	if (len)
	{
		*len = ft_strlen(cmd) + ft_strlen(arg) + 3;
		buffer = ft_strnew(*len);
	}
	else
		buffer = ft_strnew(ft_strlen(cmd) + ft_strlen(arg) + 3);
	if (!buffer)
		exit(over("ERROR MALLOC", EXIT_FAILURE));
	ft_strcat(buffer, cmd);
	if (arg)
		ft_strcat(buffer, arg);
	ft_strcat(buffer, "\r\n");
	return (buffer);
}
