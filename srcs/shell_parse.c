/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:01:33 by csapt             #+#    #+#             */
/*   Updated: 2021/02/08 12:37:02 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	get_path(char **env, char ***path)
{
	int x;
	char *str;

	x = 0;
	while (env[x] && ft_strnstr(env[x], "PATH=", 5) == NULL)
		x++;
	if (!env[x])
		return (return_message_int("Failed to find path in env", 1));
	if (!(str = ft_strtrim(env[x], "PATH=")))
		return (return_message_int("Impossible to get the Path", 1));
	if (!(*path = ft_split(str, ':')))
	{
		free(str);
		return (return_message_int("Failed to get all path", 1));
	}
	free(str);
	return (0);
}

int	parse_command(t_global *glb)
{
	if (!glb->buf) //?
		return (1);
	if (!(glb->command = ft_split((const char*)glb->buf, ' ')))
		return (1);
	if (glb->command && !glb->command[0])
		glb->command[0] = ft_strdup("");
	if (!(glb->main_command = ft_strdup(glb->command[0])))
		return (1);
	return (0);
}

int	built_in_command(t_global *glb)
{
	if (ft_strcmp(glb->main_command, "echo") == 0)
		return (ft_echo(glb->command)); // glb->command + 1 ?
	else if (ft_strcmp(glb->main_command, "pwd") == 0)
		return (ft_pwd(glb->cwd));
	else
		return (2);
	return (2);
}

