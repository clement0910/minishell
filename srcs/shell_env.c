/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:53:38 by csapt             #+#    #+#             */
/*   Updated: 2021/02/15 16:35:31 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env_var *get_env_data(char *envp)
{
	t_env_var *env_var;

	if (!(env_var = malloc(sizeof(t_env_var))))
		return (NULL);
	env_var->local = false;
	if (ft_chrcmp(envp, '='))
	{
		if (!(env_var->key = ft_strdup(envp)))
			return (NULL);
		env_var->value = NULL;
		return (env_var);
	}
	if (!(env_var->key = ft_strdupto(envp, '=')))
	{
		free(env_var);
		return (NULL);
	}
	if (!(env_var->value = ft_strdup(ft_strchr(envp, '=') + 1)))
	{
		free(env_var->key);
		free(env_var);
		return (NULL);
	}
	return (env_var);
}

int	env_to_lst(t_envlst **env, char *envp)
{
	t_env_var *env_data;
	t_envlst *tmp;

	if (*env == NULL)
	{
		if (!(env_data = get_env_data(envp)))
			return (1);
		if (!(*env = ft_lst_new(env_data)))
		{
			free(tmp);
			return (1);
		}
	}
	else
	{
		if (!(env_data = get_env_data(envp)))
			return (1);
		if (!(tmp = ft_lst_new(env_data)))
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