/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiforge <guiforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:33:39 by guiforge          #+#    #+#             */
/*   Updated: 2019/02/26 19:54:38 by guiforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

char	*build_msg(char *cmd, char *arg, size_t *len)
{
	char	*buffer;

	if (len)
	{
		*len = ft_strlen(cmd) + ft_strlen(arg) + 2;
		buffer = ft_strnew(*len);
	}
	else
		buffer = ft_strnew(ft_strlen(cmd) + ft_strlen(arg) + 2);
	
	if (!buffer)
		exit(over("ERROR MALLOC", EXIT_FAILURE));
	ft_strcat(buffer, cmd);
	ft_strcat(buffer, arg);
	ft_strcat(buffer, "\n");
	return (buffer);
}