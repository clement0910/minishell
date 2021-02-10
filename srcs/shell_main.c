/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:08:42 by csapt             #+#    #+#             */
/*   Updated: 2021/02/10 18:27:32 by csapt            ###   ########lyon.fr   */
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

char *search_command_path(char *command, char **path) //null
{
	int x;
	char *tmp;
	char *path_command;
	struct stat file;

	x = 0;
	if (!(path_command = ft_strdup(command)))
		return (NULL);
	while (path[x])
	{
		if (stat(path_command, &file) == 0)
			return (path_command);
		free(path_command);
		if (!(tmp = ft_strjoin(path[x], "/")))
			return (NULL);
		if (!(path_command = ft_strfreejoin(tmp, command)))
		{
			free(tmp);
			return (NULL);
		}
		x++;
	}
	free(path_command);
	return (NULL);
}

int	launch_command(t_global *glb)
{
	char *path_command;

	if ((path_command = search_command_path(glb->command[0], glb->path)))
	{
		execve_command(path_command, glb->command, glb->env, &glb->ret);
		free(path_command);
	}
	else
	{
		glb->ret = 127;
		printf("error command\n");
	}
	return (0);
}

int	launch_shell(t_global *glb)
{
	while (1)
	{
		if (get_next_line(0, &glb->buf) == -1)
			return (1);
		if (parse_command(&glb->command, glb->buf))
			return (1);
		if (built_in_command(glb) != 0 && !(glb->buf[0] == '\0'))
		{
			if (launch_command(glb))
				return (1);
		}
		ft_free_tab(glb->command);
		ft_printf("Minishell> ");
	}
}

int main(int ac, char **av, char **envp)
{
	t_global *glb;
	
	if (!(glb = ft_calloc(1, sizeof(t_global))))
		return (1);
	if (!(glb->env = ft_strtabdup(envp)))
		return (free_shell(glb));
	if (init_shell(glb))
		return (free_shell(glb));
	if (launch_shell(glb))
		return (free_shell(glb));
	return (0);
}

