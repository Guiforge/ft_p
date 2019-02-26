/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:17:46 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/25 17:26:55 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H

#include "../includes/proto.h"
#include "../includes/tools.h"

typedef struct		s_ftp_client {
	char			pwd[PATH_MAX + 1];
	int				sock;
	// t_ftp_connect	pi;
	// t_ftp_connect	dtp;
	t_bool			ascii;
}					t_ftp_client;

#endif