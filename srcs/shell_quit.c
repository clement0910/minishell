/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_quit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:35:40 by csapt             #+#    #+#             */
/*   Updated: 2021/05/18 14:05:29 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void 	free_env(void *content)
{
	if (!content)
		return ;
	free(((t_env_var*)content)->key);
	free(((t_env_var*)content)->value);
	free(content);
}

int 	free_shell(t_global *glb)
{
	ft_lst_clear(&glb->env, free_env);
	ft_free_tab(glb->tab_env);
	if (glb->p)
		ft_free_tab(glb->p->cmds);
	free(glb->p);
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

void 	unknow_command_msg(char *command)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(command, 1);
	ft_putendl_fd(": command not found", 1);
}