/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:58:30 by csapt             #+#    #+#             */
/*   Updated: 2021/04/27 17:04:24 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int init_var(t_global *glb, char **envp)
{
	glb->command = ft_calloc(1, sizeof(t_parse));
	if (!glb->command)
		return (ret_errno_msg(NULL, 0));
	glb->tab_env = ft_strtabdup(envp);
	if (!glb->tab_env)
		return (ret_errno_msg(NULL, 0));
	glb->env = get_env(envp);
	if (!glb->env)
		return (ret_msg("Failed to get env", 0));
	return (1);
}
