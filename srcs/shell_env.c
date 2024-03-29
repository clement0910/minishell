/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:10:30 by csapt             #+#    #+#             */
/*   Updated: 2021/06/16 20:02:38 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env_var	*get_env_var(char *str_env, bool exported)
{
	t_env_var	*env_var;

	env_var = malloc(1 * sizeof(t_env_var));
	if (!env_var)
		return (NULL);
	env_var->key = ft_strdupto(str_env, '=');
	if (!env_var->key)
	{
		free_env(env_var);
		return (NULL);
	}
	env_var->value = ft_strdup(ft_strchr(str_env, '=') + 1);
	if (!env_var->value)
	{
		free(env_var->key);
		free(env_var);
		return (NULL);
	}
	env_var->exported = exported;
	return (env_var);
}

t_env_var	*get_env_var_null(char *var)
{
	t_env_var	*env_var;

	env_var = malloc(1 * sizeof(t_env_var));
	if (!env_var)
		return (NULL);
	env_var->key = ft_strdup(var);
	if (!env_var->key)
	{
		free(env_var);
		return (NULL);
	}
	env_var->value = NULL;
	env_var->exported = true;
	return (env_var);
}

int	env_to_lst(t_env **env, char *envp)
{
	t_env_var	*env_var;

	if (*env == NULL)
	{
		*env = env_to_null_lst(envp);
		if (!*env)
			return (1);
	}
	else
	{
		env_var = get_env_var(envp, true);
		if (!env_var)
			return (1);
		if (addback_env(env_var, env))
			return (1);
	}
	return (0);
}

t_env	*env_to_null_lst(char *envp)
{
	t_env		*env;
	t_env_var	*env_var;

	env_var = get_env_var(envp, true);
	if (!env_var)
		return (NULL);
	env = ft_lst_new(env_var);
	if (!env)
	{
		free_env(env_var);
		return (NULL);
	}
	else
		return (env);
}

t_env	*get_env(char **envp)
{
	int		x;
	t_env	*env;

	x = 0;
	env = NULL;
	if (!envp)
		return (NULL);
	while (envp[x])
	{
		if (env_to_lst(&env, envp[x]))
		{
			ft_lst_clear(&env, free_env);
			return (NULL);
		}
		x++;
	}
	return (env);
}
