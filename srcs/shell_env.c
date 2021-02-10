/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:53:38 by csapt             #+#    #+#             */
/*   Updated: 2021/02/10 14:36:05 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env *get_env_data(char *envp)
{
	t_env *env;

	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	//check env variables
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

int	env_to_lst(t_envlst **env, char *envp)
{
	t_env *env_data;
	t_envlst *tmp;

	if (*env == NULL)
	{
		if (!(env_data = get_env_data(envp)))
			return (1);
		if (!(*env = ft_lst_new(tmp)))
		{
			free(tmp);
			return (1);
		}
	}
	else
	{
		if (!(env_data = get_env_data(envp)))
			return (1);
		if (!(tmp = ft_lst_new(tmp)))
		{
			free(tmp);
			return (1);
		}
		ft_lst_addback(env, tmp);
	}
	return (0);
}

int	get_env(t_envlst **env, char **envp)
{
	int x;

	x = 0;
	if (!envp)
		return (1);
	while (envp[x])
	{
		if ((env_to_lst(env, envp[x])))
		{
			ft_lst_clear(env, free);
			return (return_message_int("Failed to get envv", 1));
		}
		x++;
	}
	return (0);
}