/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:02:02 by csapt             #+#    #+#             */
/*   Updated: 2021/02/05 10:35:57 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	start_shell(t_global *glb)
{
	// if (excve_command("/bin/date", glb) > 0)
	// 	return (1); //exit ?
	// printf("%s\n", strerror(errno));
}

int	init_shell(t_global *glb)
{
	if (!(glb->buf = ft_calloc(BUFFER_SIZE, sizeof(char))))
		return_message_int("Failed to init buf", 1);
	if (get_path(glb->env, &glb->path))
		return (1);
	// if (start_shell(glb);
	return (0);
}