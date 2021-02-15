/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_quit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:19:22 by csapt             #+#    #+#             */
/*   Updated: 2021/02/15 15:38:01 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	free_shell(t_global *glb)
{
	ft_free_tab(glb->command);
	free(glb->home);
	ft_free_tab(glb->path);
	if (glb->env)
	{
		ft_free_tab(glb->env->env_tab);
		ft_lst_clear(&glb->env->env_lst, free);
	}
	free(glb->buf);
	free(glb->env);
	if (glb)
		free(glb);
	return (glb->ret);
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