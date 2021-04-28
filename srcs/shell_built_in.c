/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:21:13 by csapt             #+#    #+#             */
/*   Updated: 2021/04/28 15:09:11 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int built_in_hello(void)
{
	printf(C_Y"Hello World !\n");
	ft_putstr_fd(C_N, 1);
	return (1);
}

int built_in_command(t_global *glb)
{
	if (ft_strcmp("hello", glb->command->tab_command[0]) == 0)
		return (built_in_hello());
	else if (ft_strcmp("env", glb->command->tab_command[0]) == 0)
		return (built_in_env(glb->tab_env));
	else if (ft_strcmp("export", glb->command->tab_command[0]) == 0)
		return (built_in_export(glb->command, &glb->env, &glb->tab_env));
	else if (ft_strcmp("unset", glb->command->tab_command[0]) == 0)
		return (built_in_unset(glb->command, &glb->tab_env, &glb->env));
	else
		return (0);
}