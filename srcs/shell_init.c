/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:02:02 by csapt             #+#    #+#             */
/*   Updated: 2021/02/16 12:20:32 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	get_date(t_global *glb) //opti
{
	char **command;

	if (!(command = create_command("/bin/date")))
		return (1);
	if (execve_command("/bin/date", command, glb->env->env_tab, &glb->ret)) // if Failed here
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
	if (get_env(&glb->env->env_lst, glb->env->env_tab))
		return (free_shell(glb));
	// if (get_env(&glb->env->env_lst_ascii, glb->env->env_tab)) //temporary ?
	// 	return (free_shell(glb));
	if (get_path(glb->env->env_tab, &glb->path))
		return (1);
	if (get_var_from_env(glb->env->env_tab, &glb->home, "HOME="))
		return (1);
	if (get_date(glb)) //may cause problems
		return (glb->ret);
	return (0);
}