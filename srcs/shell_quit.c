/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_quit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:19:22 by csapt             #+#    #+#             */
/*   Updated: 2021/02/04 12:57:30 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	free_shell(t_global *glb)
{
	free(glb->buf);
	ft_free_tab(glb->path);
	if (glb)
		free(glb);
	return (1);
}

int	return_message_int(char *str, int ret)
{
	ft_putendl_fd(str, 1);
	return (ret);
}

int return_strerror(void)
{
	ft_putendl_fd(strerror(errno), 1);
	return (1);
}