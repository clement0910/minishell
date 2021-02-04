/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:02:02 by csapt             #+#    #+#             */
/*   Updated: 2021/02/04 10:52:39 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	init_shell(t_global *glb)
{
	// if ((glb->pid = fork()) == -1)
	// 	return_strerror();
	if (!(glb->buf = ft_calloc(BUFFER_SIZE, sizeof(char))))
		return_message_int("Failed to init buf", 1);
	if (get_path(glb->env, &glb->path))
		return(1);
	//print_tab(glb->path);
	//launch shell
	return (0);
}