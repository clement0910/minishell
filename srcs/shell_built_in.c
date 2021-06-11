/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:21:13 by csapt             #+#    #+#             */
/*   Updated: 2021/05/18 15:50:48 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int built_in_hello(void)
{
	printf(C_Y"Hello World !\n");
	ft_putstr_fd(C_N, 1);
	return (0);
}

int built_in_command(char *cmd, char **args, t_global *glb)
{
    if (!cmd)
        glb->ret = 1;
    if (ft_strcmp("ls", cmd) == 0)
        glb->ret = built_in_ls();
	else if (ft_strcmp("echo", cmd) == 0)
		glb->ret = built_in_echo(args);
	else if (ft_strcmp("cd", cmd) == 0)
		glb->ret = built_in_cd(args[0], get_var_value(glb->env, "HOME"));
	else if (ft_strcmp("hello", cmd) == 0)
		glb->ret = built_in_hello();
	else if (ft_strcmp("pwd", cmd) == 0)
		glb->ret = built_in_pwd();
    else if (ft_strcmp("env", cmd) == 0)
        glb->ret = built_in_env(glb->tab_env);
    else if (ft_strcmp("unset", cmd) == 0)
        glb->ret = built_in_unset(args[1], &glb->tab_env, &glb->env);
    else if (ft_strcmp("export", cmd) == 0)
        glb->ret = built_in_export(1, args[1], &glb->env, &glb->tab_env);
    else if (ft_strcmp("exit", cmd) == 0) {
        free_shell(glb);
        exit(EXIT_SUCCESS);
    }
	else
		glb->ret = 1;
    return (glb->ret);
}