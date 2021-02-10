/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:02:02 by csapt             #+#    #+#             */
/*   Updated: 2021/02/10 12:39:42 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	get_date(t_global *glb) //opti
{
	char **command;

	if (!(command = create_command("/bin/date")))
		return (1);
	if (execve_command("/bin/date", command, glb->env, &glb->ret)) // Failed here
	{
		ft_free_tab(command);
		return(return_message_int("Failed to init Minishell", glb->ret));
	}
	ft_free_tab(command);
	//ret need to be 0
	return(0);
}

int	init_shell(t_global *glb)
{
	if (!(glb->buf = ft_calloc(BUFFER_SIZE, sizeof(char))))
		return(return_message_int("Failed to init buf", 1));
	if (get_env(&glb->env_list, glb->env))
		return (free_shell(glb));
	if (get_path(glb->env, &glb->path))
		return (1);
	if (get_var_from_env(glb->env, &glb->home, "HOME="))
		return (1);
	if (get_date(glb)) //may cause problems
		return (glb->ret);
	return (0);
}