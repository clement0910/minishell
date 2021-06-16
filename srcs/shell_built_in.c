/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:21:13 by csapt             #+#    #+#             */
/*   Updated: 2021/06/16 16:59:20 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	built_in_hello(void)
{
	printf(C_Y"Hello World !\n");
	ft_putstr_fd(C_N, 1);
	return (0);
}

int	built_in_env_command(char *cmd, char **args, t_global *glb)
{
	if (ft_strcmp("env", cmd) == 0)
		return (built_in_env(glb->tab_env));
	else if (ft_strcmp("unset", cmd) == 0)
		return (built_in_unset(args[1], &glb->tab_env, &glb->env));
	else if (ft_strcmp("export", cmd) == 0)
		return (built_in_export(1, args[1], &glb->env, &glb->tab_env));
	else if (ft_chrcmp(cmd, '=') == 0 && check_var_name(cmd) == 0)
		return (built_in_export(0, cmd, &glb->env, &glb->tab_env));
	else
		return (1);
}

int	built_in_command(char *cmd, char **args, t_global *glb)
{
	if (!cmd)
		return (glb->ret);
	if (ft_strcmp("built_ls", cmd) == 0)
		glb->ret = built_in_ls();
	else if (ft_strcmp("echo", cmd) == 0)
		glb->ret = built_in_echo(args + 1);
	else if (ft_strcmp("cd", cmd) == 0)
		glb->ret = built_in_cd(args[1], glb->env, &glb->tab_env);
	else if (ft_strcmp("hello", cmd) == 0)
		glb->ret = built_in_hello();
	else if (ft_strcmp("pwd", cmd) == 0)
		glb->ret = built_in_pwd();
	else if (ft_strcmp("exit", cmd) == 0)
	{
		free_shell(glb);
		exit(EXIT_SUCCESS);
	}
	else if (built_in_env_command(cmd, args, glb) == 0)
		glb->ret = 0;
	else
		glb->ret = 1;
	return (glb->ret);
}
