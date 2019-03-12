/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:39:57 by guiforge          #+#    #+#             */
/*   Updated: 2019/03/12 16:39:46 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

static t_ftp_cmd	g_hands[] = {
	{"ASCII", (int (*)(void *, char *))&handle_ascii, True},
	{"BIN", (int (*)(void *, char *))&handle_bin, True},
	{"BINARY", (int (*)(void *, char *))&handle_bin, True},
	{"TYPE", (int (*)(void *, char *))&handle_type, True},
	{"STOR", (int (*)(void *, char *))&handle_stor, True},
	{"PUT", (int (*)(void *, char *))&handle_stor, True},
	{"CWD", (int (*)(void *, char *))&handle_cwd, True},
	{"CD", (int (*)(void *, char *))&handle_cwd, True},
	{"RETR", (int (*)(void *, char *))&handle_get, True},
	{"GET", (int (*)(void *, char *))&handle_get, True},
	{"QUIT", (int (*)(void *, char *))&handle_quit, False},
	{"PWD", (int (*)(void *, char *))&handle_pwd, True},
	{"LS", (int (*)(void *, char *))&handle_ls, True},
	{"LIST", (int (*)(void *, char *))&handle_ls, True},
	{"SYST", (int (*)(void *, char *))&handle_syst, True},
	{"USER", (int (*)(void *, char *))&handle_user, False},
	{"DEBUG", (int (*)(void *, char *))&handle_debug, False},
	{"PASS", (int (*)(void *, char *))&handle_pass, False},
	{"LCD", (int (*)(void *, char *))&handle_lcd, False},
	{"LLS", (int (*)(void *, char *))&handle_lls, False},
	{"LPWD", (int (*)(void *, char *))&handle_lpwd, False},
	{NULL, NULL, False}
};

static int	handle_help(void)
{
	size_t	i;

	i = 0;
	while (g_hands[i].cmd)
	{
		ft_printf("- %s\n", g_hands[i].cmd);
		i++;
	}
	return (EXIT_SUCCESS);
}

int			handle_cmd(t_ftp_client *c, char *cmd)
{
	size_t		i;
	char		*param;

	i = 0;
	if (ft_strequ("help", cmd))
		return (handle_help());
	while (g_hands[i].cmd && ft_strncmpi(g_hands[i].cmd, cmd, \
												ft_strlen(g_hands[i].cmd) - 1))
		i++;
	if (g_hands[i].cmd)
	{
		param = ft_strchr(cmd, ' ');
		if (param)
			param++;
		return (g_hands[i].handler(c, param));
	}
	ft_printf("Command not found %s\n", cmd);
	return (-1);
}
