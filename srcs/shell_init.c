/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:02:02 by csapt             #+#    #+#             */
/*   Updated: 2021/02/08 15:43:18 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char **create_command(char *command)
{
	char **tab_command;
	if (!(tab_command = ft_split((const char *)command, ' ')))
		return (NULL);
	return(tab_command);
}

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
	if (get_path(glb->env, &glb->path))
		return (1);
	if (get_home(glb->env, &glb->home))
		return (1);
	printf("home: %s\n", glb->home);
	if (get_date(glb)) //may cause problems
		return (glb->ret);
	ft_printf("> ");
	return (0);
}