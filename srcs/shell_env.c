/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:10:30 by csapt             #+#    #+#             */
/*   Updated: 2021/04/27 18:04:17 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char **env_to_tab(t_env *env)
{
	//TODO: check le cas ou exported est a 0 et proteger argv_join
	int x;
	int len;
	char **tab;
	t_env *tmp;

	x = 0;
	tmp = env;
	len = ft_lst_size(env);
	tab = malloc((len + 1) * sizeof(char*));
	if (!tab)
		return (NULL);
	while (tmp)
	{
		tab[x] = argv_join("%s=%s", ((t_env_var*)tmp->content)->key, ((t_env_var*)tmp->content)->value);
		tmp = tmp->next;
		x++;
	}
	tab[x] = NULL;
	return (tab);
}

t_env *env_to_null_lst(char *envp)
{
	t_env *env;
	t_env_var *env_var;

	env_var = get_env_var(envp, 1);
	if (!env_var)
		return (NULL);
	env = ft_lst_new(env_var);
	if (!env)
	{
		free(env_var);
		return (NULL);
	}
	else
		return (env);
}

int	env_to_lst(t_env **env, char *envp)
{
	t_env 		*tmp;
	t_env_var 	*env_var;

	if (*env == NULL)
	{
		*env = env_to_null_lst(envp);
		if (!*env)
			return (0);
	}
	else
	{
		env_var = get_env_var(envp, 1);
		if (!env_var)
			return (0);
		tmp = ft_lst_new(env_var);
		if (!tmp)
		{
			free(env_var);
			return (0);
		}
		ft_lst_addback(env, tmp);
	}
	return (1);
}

t_env *get_env(char **envp)
{
	int x;
	t_env *env;

	x = 0;
	env = NULL;
	if (!envp)
		return (NULL);
	while (envp[x])
	{
		if (env_to_lst(&env, envp[x]) == 0)
		{
			ft_lst_clear(&env, free);
			return (NULL);
		}
		x++;
	}
	return (env);
}

t_env_var *get_env_var(char *str_env, int exported)
{
	t_env_var *env_var;

	env_var = malloc(1 * sizeof(t_env_var));
	if (!env_var)
		return (NULL);
	env_var->key = ft_strdupto(str_env, '=');
	if (!env_var->key)
	{
		free(env_var);
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

