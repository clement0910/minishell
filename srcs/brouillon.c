/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:00:02 by csapt             #+#    #+#             */
/*   Updated: 2021/02/05 10:07:00 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	excve_command(char *command, t_pid pid)
{
	int ret;
	struct stat file_stat;

	if (stat(command, &file_stat) == 0)
		return (1); //command msg
	if ((glb->pid = fork()) == -1)
		return(return_strerror());
	if (glb->pid == 0)
	{
		if ((ret = execve(command, NULL, NULL)) == -1)
			exit (ret);
	}
	else
	{
		waitpid(glb->pid, &ret, 0);
		ret = WEXITSTATUS(ret);
	}
	return (ret);
}

int	excve_command(t_global *glb)
{
	int x;
	char *path_command;

	x = 0;
	if (!(path_command = ft_strdup(glb->main_command)))
		return (1);
	while ((execve(path_command, glb->command, glb->env) == -1))
	{
		printf("%s\n", path_command);
		free(path_command);
		if (!(path_command = ft_strjoin(ft_strjoin(glb->path[x], "/"), glb->main_command)))
			return (1);
		x++;
	}
}

int	execute_command(t_global *glb)
{
	int x;
	int error;
	
	x = 0;
	if ((glb->pid = fork()) == -1)
		return(return_strerror());
	if (glb->pid == 0)
	{
		if (excve_command(glb))
			return (1);
	}
	else
		waitpid(glb->pid, &error, 0);
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
			if (execute_command(glb))
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