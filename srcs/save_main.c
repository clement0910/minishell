/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:08:42 by csapt             #+#    #+#             */
/*   Updated: 2021/02/05 11:09:15 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	execve_command(t_global *glb, char *path_command)
{
	if (glb->pid == 0)
	{
		if ((glb->ret = execve(path_command, glb->command, glb->env)) == -1)
			exit(glb->ret);
	}
	else
	{
		waitpid(glb->pid, &glb->ret, 0);
		glb->ret = WEXITSTATUS(glb->ret);
	}
	printf("yolo\n");
	return (glb->ret);
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
	if ((glb->pid = fork()) == -1)
		return(return_strerror());
	if (glb->pid == 0)
	{
		while(glb->path[x])
		{
			if (stat(path_command, &glb->file) == 0)
			{
				command = 1;
				if ((glb->ret = execve(path_command, glb->command, glb->env)) == -1)
					exit(glb->ret);	
			}
			free(path_command);
			if (!(path_command = ft_strjoin(ft_strjoin(glb->path[x], "/"), glb->main_command)))
				return (1);
			x++;
		}
		printf("??\n");
	}
	else
	{
		waitpid(glb->pid, &glb->ret, 0);
		glb->ret = WEXITSTATUS(glb->ret);
	}
	//excve faut faire pour avoir le exit

	printf("number: %d\n", command);
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
		if (built_in_command(glb) != 0 && !(glb->buf[0] == '\n'))
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
	glb->env = envp;
	if (init_shell(glb))
		return (free_shell(glb));
	if (launch_shell(glb))
		return (free_shell(glb));
	return (0);
}