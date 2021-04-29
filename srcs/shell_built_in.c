/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:21:13 by csapt             #+#    #+#             */
/*   Updated: 2021/04/29 17:12:19 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int built_in_hello(void)
{
	printf(C_Y"Hello World !\n");
	ft_putstr_fd(C_N, 1);
	return (0);
}

int built_in_command(char *cmd, char **args, t_global *glb)
{
	glb->ret = 0;
	if (ft_strcmp("echo", cmd) == 0)
		return (built_in_echo(args));
	else if (ft_strcmp("cd", cmd) == 0)
		return (built_in_cd(args[1], get_var_name(glb->env, "HOME")));
	else if (ft_strcmp("hello", cmd) == 0)
		return (built_in_hello());
	else if (ft_strcmp("pwd", cmd) == 0)
		return (built_in_pwd());
	else if (ft_strcmp("unset", cmd) == 0)
		return (built_in_unset(args[1], &glb->tab_env, &glb->env));
	else
	{
		glb->ret = 1;
		return (1);
	}
}