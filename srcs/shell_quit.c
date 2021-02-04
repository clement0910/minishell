/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_quit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:19:22 by csapt             #+#    #+#             */
/*   Updated: 2021/02/03 15:58:01 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	free_shell(t_global *glb)
{
	ft_free_tab(glb->env);
	ft_free_tab(glb->path);
	free(glb->buf);
	free(glb->main_command);
	ft_free_tab(glb->command);
	free(glb->buf);
	if (glb)
		free(glb);
	return (1);
}

int	return_message_int(char *str, int x)
{
	ft_putendl_fd(str, 1);
	return (x);
}

int return_strerror(void)
{
	ft_putendl_fd(strerror(errno), 1);
	return (1);
}