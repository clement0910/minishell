/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:45:12 by csapt             #+#    #+#             */
/*   Updated: 2021/06/12 22:36:36 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	execve_command(char *path_command, char **command, char **envp, int *ret)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ret_errno_msg(NULL, 1));
	if (pid == 0)
	{
		*ret = execve(path_command, command, envp);
		if (*ret == -1)
			exit(*ret);
	}
	else
	{
		waitpid(pid, ret, 0);
		*ret = WEXITSTATUS(*ret);
	}
	return (*ret);
}

char	**get_path(char *path)
{
	char	**path_tab;

	if (!path)
		return (NULL);
	path_tab = ft_split(path, ':');
	if (!path_tab || !path_tab[0])
	{
		ft_free_tab(path_tab);
		return (NULL);
	}
	return (path_tab);
}

int	check_another_path(char *path, char **path_command, char *command)
{
	char		*tmp;
	struct stat	file;

	if (stat(*path_command, &file) == 0)
		return (0);
	free(*path_command);
	*path_command = NULL;
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (1);
	*path_command = ft_strfreejoin(tmp, command);
	if (!(*path_command))
	{
		free(tmp);
		return (1);
	}
	return (2);
}

char	*search_path_command(t_env *env, char *command, char **path)
{
	int		x;
	int		ret;
	char	*path_command;

	path_command = ft_strdup(command);
	if (!path_command)
		return (NULL);
	x = 0;
	while (path[x])
	{
		ret = check_another_path(path[x], &path_command, command);
		if (ret == 1)
			break ;
		else if (ret == 0)
			return (path_command);
		x++;
	}
	free(path_command);
	return (NULL);
}

int	launch_command(t_global *glb, char **cmds)
{
	char	*command;
	char	*path_command;
	char	**path;

	command = cmds[0]; //bug here
	path = get_path(get_var_value(glb->env, "PATH"));
	if (!path)
		return (1);
	path_command = search_path_command(glb->env, command, path);
	if (!path_command)
	{
		glb->ret = 127;
		unknow_command_msg(command);
		free(path_command);
		ft_free_tab(path);
		return (0);
	}
	execve_command(path_command, cmds, glb->tab_env, &glb->ret);
	free(path_command);
	ft_free_tab(path);
	return (0);
}
