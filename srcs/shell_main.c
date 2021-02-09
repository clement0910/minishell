/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:08:42 by csapt             #+#    #+#             */
/*   Updated: 2021/02/09 14:47:55 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	execve_command(char *path_command, char **command, char **envp, int *ret)
{
	pid_t pid;

	if ((pid = fork()) == -1)
		return(return_strerror());
	if (pid == 0)
	{
		if ((*ret = execve(path_command, command, envp)) == -1)
			exit(*ret);
	}
	else
	{
		waitpid(pid, ret, 0);
		*ret = WEXITSTATUS(*ret);
	}
	return (*ret);
}

int search_command_path(t_global *glb)
{
	int x;
	int command;
	char *path_command;

	x = 0;
	command = 0;
	if (!(path_command = ft_strdup(glb->main_command)))
		return (1);
	while(glb->path[x])
	{
		if (stat(path_command, &glb->file) == 0)
		{
			command = 1;
			execve_command(path_command, glb->command, glb->env, &glb->ret);	
		}
		free(path_command);
		if (!(path_command = ft_strjoin(ft_strjoin(glb->path[x], "/"), glb->main_command)))
			return (1);
		x++;
	}
	if (command == 0)
	{
		glb->ret = 127;
		printf("error command\n");
	}
	free(path_command);
	return (0);
}

int	launch_shell(t_global *glb)
{
	while (1)
	{
		get_next_line(0, &glb->buf);
		if (parse_command(glb))
			return (1);
		if (built_in_command(glb) != 0 && !(glb->buf[0] == '\0'))
		{
			if (search_command_path(glb))
				return (1);
		}
		free(glb->command);
		free(glb->main_command);
		ft_printf("> ");
	}
}

int main(int ac, char **av, char **envp)
{
	t_global *glb;
	if (!(glb = ft_calloc(1, sizeof(t_global))))
		return (1);
	glb->env = ft_strtabdup(envp);
	if (get_env(&glb->env_list, glb->env))
		return (1);
	if (init_shell(glb))
		return (free_shell(glb));
	if (launch_shell(glb))
		return (free_shell(glb));
	return (0);
}

