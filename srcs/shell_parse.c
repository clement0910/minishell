/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:01:33 by csapt             #+#    #+#             */
/*   Updated: 2021/02/09 15:37:22 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


int	get_path(char **env, char ***path)
{
	int x;
	char *str;

	x = 0;
	while (env[x] && ft_strnstr(env[x], "PATH=", 5) == NULL)
		x++;
	if (!env[x])
		return (return_message_int("Failed to find path in env", 1));
	if (!(str = ft_strtrim(env[x], "PATH=")))
		return (return_message_int("Impossible to get the Path", 1));
	if (!(*path = ft_split(str, ':')))
	{
		free(str);
		return (return_message_int("Failed to get all path", 1));
	}
	free(str);
	return (0);
}

t_env *get_env_value(char *envp)
{
	t_env *env;

	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	if (!(env->key = ft_substr(envp, 0, ft_strlento(envp, '='))))
	{
		free(env);
		return (NULL);
	}
	if (!(env->value = ft_strdup(ft_strchr(envp, '=') + 1)))
	{
		free(env->key);
		free(env);
		return (NULL);
	}
	return (env);
}

// int	env_to_lst(t_envlst **env, char *envp)
// {
// 	t_env *tmp;
// 	t_envlst *temp2;

// 	if (*env == NULL)
// 	{
// 		if (!(tmp = get_env_value(envp)))
// 			return (0);
// 		*env = ft_lst_new(tmp);
// 	}
// 	else
// 	{
// 		if (!(tmp = get_env_value(envp)))
// 			return (0);		
// 		if (!(temp2 = ft_lst_new(tmp)))
// 			return (0);
// 		ft_lst_addback(env, temp2);
// 	}
// }


int	get_env(t_envlst **env, char **envp)
{
	int x;
	t_env *tmp;
	t_envlst *lst_tmp;
	
	x = 0;
	if (!envp)
		return (1);
	while (envp[x])
	{
		if (*env == NULL)
		{
			if (!(tmp = get_env_value(envp[x])))
				return (1);
			*env = ft_lst_new(tmp);
		}
		else
		{
			if (!(tmp = get_env_value(envp[x])))
				return (1);
			if (!(lst_tmp = ft_lst_new(tmp)))
				return (1);
			ft_lst_addback(env, lst_tmp);			
		}
		x++;
	}
	return (0);
}

int	get_home(char **env, char **home)
{
	int x;

	x = 0;
	while (env[x] && ft_strnstr(env[x], "HOME=", 5) == NULL)
		x++;
	if (!env[x])
		return (return_message_int("Failed to find home in env", 1));
	if (!(*home = ft_strtrim(env[x], "HOME=")))
		return (return_message_int("Impossible to get the home", 1));
	return (0);
}

int	parse_command(t_global *glb)
{
	if (!glb->buf) //?
		return (1);
	if (!(glb->command = ft_split((const char*)glb->buf, ' ')))
		return (1);
	if (glb->command && !glb->command[0])
		glb->command[0] = ft_strdup("");
	if (!(glb->main_command = ft_strdup(glb->command[0]))) //?
		return (1);
	return (0);
}

int	built_in_command(t_global *glb)
{
	if (ft_strcmp(glb->main_command, "echo") == 0)
		return (ft_echo(glb->command)); // glb->command + 1 ?
	else if (ft_strcmp(glb->main_command, "pwd") == 0)
		return (ft_pwd(glb->cwd));
	else if (ft_strcmp(glb->main_command, "cd") == 0)
		return(built_in_cd(glb));
	else if (ft_strcmp(glb->main_command, "export") == 0)
		return (ft_export(glb));
	else if (ft_strcmp(glb->main_command, "unset") == 0)
		return (ft_unset(glb, &glb->env_list));
		return (2);
	return (2);
}

