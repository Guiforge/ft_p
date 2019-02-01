/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:03:24 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/01 18:44:33 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

/*
ls : liste le répertoire courant du serveur
•
cd : change le répertoire courant du serveur
•
get _file_ : récupère le fichier _file_ du serveur vers le client
•
put _file_ : envoi le fichier _file_ du client vers le serveur
•
pwd : affiche le chemin du répertoire courant sur le serveur
•
quit : coupe la connection + sort du programme
*/
//230 User logged in, proceed.
static t_ftp_cmd	g_hands[] = {
	{"ls", (int (*)(void *, int, char *))&handle_ls},
	{"user", (int (*)(void *, int, char *))&handle_user},
	{NULL, NULL}
};


static void	exec_handler(t_ftp context, int cs, char *cmd)
{
	size_t	i;

	i = 0;
	log_debug("received: %s", cmd);
	while(g_hands[i].cmd && ft_strncmpi(g_hands[i].cmd, cmd, ft_strlen(g_hands[i].cmd) - 1))
	{
		log_debug("received: %s (%s, %d) %d", cmd, g_hands[i].cmd, ft_strlen(g_hands[i].cmd), ft_strncmpi(g_hands[i].cmd, cmd, ft_strlen(g_hands[i].cmd)));
		i++;
	}
	if(g_hands[i].cmd)
		g_hands[i].handler(&context, cs, cmd);
	else
		log_debug("cmd not found %s", cmd);
}

void		ftp_handle_cmd(t_ftp context, int cs)
{
	char			*line;
	int				ret;

	while((ret = get_next_line(cs, &line)) && ret != -1)
		exec_handler(context, cs, line);
	free(line);
}