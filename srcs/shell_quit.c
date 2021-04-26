/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_quit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:35:40 by csapt             #+#    #+#             */
/*   Updated: 2021/04/26 17:09:00 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int 	free_shell(t_global *glb)
{
	ft_free_tab(glb->tab_env);
	if (glb->command)
		ft_free_tab(glb->command->tab_command);
	free(glb->command);
	free(glb);
	return (1); //need to ret glb->ret
}

int 	ret_errno_msg(char *msg, int ret)
{
	if (msg)
		printf("%s", msg);
	printf(C_R" errno :%s\n"C_N, strerror(errno));
	return (ret);
}

int 	ret_msg(char *msg, int ret)
{
	printf(C_Y"%s\n", msg);
	ft_putstr_fd(C_N, 1);
	return (ret);
}