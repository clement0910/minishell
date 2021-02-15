/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:01:33 by csapt             #+#    #+#             */
/*   Updated: 2021/02/15 16:32:40 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	parse_command(char ***command, char *buf)
{
	if (!buf) //?
		return (1);
	if (!(*command = ft_split((const char*)buf, ' ')))
		return (1);
	if (*command && !*command[0])
		*command[0] = ft_strdup("");
	return (0);
}

int	built_in_command(t_global *glb)
{
	if (ft_strcmp(glb->command[0], "echo") == 0)
		return (built_in_echo(glb->command)); // glb->command + 1 ? | opti
	else if (ft_strcmp(glb->command[0], "pwd") == 0)
		return (built_in_pwd(&glb->cwd));
	else if (ft_strcmp(glb->command[0], "cd") == 0)
		return(built_in_cd(glb->command, glb->home));
	else if (ft_strcmp(glb->command[0], "export") == 0)
		return (built_in_export(glb->command, glb->env));
	else if (ft_strcmp(glb->command[0], "unset") == 0)
		return (built_in_unset(glb->command, glb->env));
	else if (ft_strcmp(glb->command[0], "env") == 0)
		return (built_in_env(glb->env->env_tab));
	return (2);
}
