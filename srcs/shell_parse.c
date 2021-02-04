/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:01:33 by csapt             #+#    #+#             */
/*   Updated: 2021/02/04 11:12:20 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	get_path(char **env, char ***path)
{
	int x;
	char *str;

	x = 0;
	while (ft_strnstr(env[x], "PATH", 4) == NULL)
		x++;
	//printf("BEFORE: [%s]\n", ft_strnstr(env[x], "PATH", 4));
	str = ft_strrchr(ft_strnstr(env[x], "PATH", 4), '=') + 1;
	//trim ?
	//printf("final [%s]\n", str);
	*path = ft_split(str, ':');
	return (0);
}

int	parse_command(t_global *glb)
{
	if (!(glb->command = ft_split((const char*)glb->buf, ' ')))
		return (1);
	if (!(glb->main_command = ft_strtrim(glb->command[0], "\n")))
		return (1);
	return (0);
}

int	built_in_command(t_global *glb)
{
	if (ft_strcmp(glb->main_command, "echo") == 0)
		return(ft_echo(glb->command)); // glb->command + 1 ?
	else if (ft_strcmp(glb->main_command, "pwd") == 0)
		return (ft_pwd(glb->cwd));
	else
		return (2);
	return (2);
}

