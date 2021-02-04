/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:00:02 by csapt             #+#    #+#             */
/*   Updated: 2021/02/04 11:09:36 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	execute_command(t_global *glb)
{
	int x;
	int error;
	char *path_command;
	
	x = 0;
	if ((glb->pid = fork()) == -1)
		return_strerror();
	if (glb->pid == 0)
	{
		if (!(path_command = ft_strdup(glb->main_command)))
			return (1);
		while ((execve(path_command, glb->command, glb->env) == -1))
		{
			if (glb->pid != 0)
			{
				free(path_command);
				return (0);
			}
			free(path_command);
			if (!(path_command = ft_strjoin(ft_strjoin(glb->path[x], "/"), glb->main_command)))
				return (1);
			x++;
		}
	}
	else
		waitpid(glb->pid, &error, 0);
	return (0);
}

int	read_shell(t_global *glb)
{
	while (get_next_line(0, &glb->buf))
	{
		if (parse_command(glb))
			return (1);
			if (built_in_command(glb) != 0 && !(glb->buf[0] == '\n'))
			{
				if (execute_command(glb))
					return (1);
			}
		free(glb->command);
		free(glb->main_command);
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
	read_shell(glb);
	return (0);
}