/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:04:32 by gpouyat           #+#    #+#             */
/*   Updated: 2019/03/01 19:13:24 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tools.h"

char	*ftp_cr_end(char *buffer, size_t len)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!buffer)
		return (NULL);
	new = ft_strnew(len + ft_strcount(buffer, '\n'));
	if (!new)
		exit(over("Malloc Error !!", EXIT_FAILURE));
	i = 0;
	j = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			new[j] = '\r';
			j++;
			new[j] = buffer[i];
		}
		else
			new[j] = buffer[i];
		j++;
		i++;
	}
	return (new);
}

char	*ftp_newline_end(char *buffer)
{
	char *cpy;

	cpy = buffer;
	if (!buffer)
		return (NULL);
	while((buffer = ft_strstr(buffer, "\r\n")))
		ft_strcpy(buffer, buffer + 1);
	return(cpy);
}