/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:42:35 by csapt             #+#    #+#             */
/*   Updated: 2021/04/28 14:13:10 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int export_var(char *var, t_env **env, char ***env_tab)
{
	t_env *lst;
	t_env_var *env_var;

	if (check_exist_var(var, *env))
	{
		ft_free_tab(*env_tab);
		*env_tab = env_to_tab(*env);
		if (!*env_tab)
			return (0);
	}
	else
	{
		env_var = get_env_var_null(var);
		if (!env_var)
			return (0);
		if (addback_env(env_var, env) == 0)
			return (0);
	}
	return (1);
}

int replace_env_value(char *str_env, t_env *env, char ***env_tab)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(str_env, ((t_env_var*)tmp->content)->key, ft_strlento(((t_env_var*)tmp->content)->key, '=')) == 0) //TODO: pas sur de ca recheck
		{
			free(((t_env_var*)tmp->content)->value);
			((t_env_var*)tmp->content)->value = ft_strdup(ft_strchr(str_env, '=') + 1);
			if (((t_env_var*)tmp->content)->value == NULL)
				return (0);
		}
		tmp = tmp->next;
	}
	ft_free_tab(*env_tab);
	*env_tab = env_to_tab(env);
	if (!*env_tab)
		return (0);
	return (1);
}

int export_env(char *str_env, t_env **env, char ***env_tab)
{
	t_env *lst;
	t_env_var *env_var;

	env_var = get_env_var(str_env, 1);
	if (!env_var)
		return (0);
	if (addback_env(env_var, env) == 0)
		return (0);
	ft_free_tab(*env_tab);
	*env_tab = env_to_tab(*env);
	if (!*env_tab)
		return (0);
	return (1);
}

int display_export(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (((t_env_var*)tmp->content)->value)
			printf("declare -x %s=\"%s\"\n", ((t_env_var*)tmp->content)->key, ((t_env_var*)tmp->content)->value);
		else
			printf("declare -x %s\n", ((t_env_var*)tmp->content)->key);
		tmp = tmp->next;
	}
	return (1);
}

int	built_in_export(t_parse *command, t_env **env, char ***env_tab)
{
	if (!command->tab_command[1])
		return (display_export(*env));
	if (ft_chrcmp(command->tab_command[1], '='))
		return (export_var(command->tab_command[1], env, env_tab));
	else if (check_exist_var(command->tab_command[1], *env))
		return (replace_env_value(command->tab_command[1], *env, env_tab));
	else
		return (export_env(command->tab_command[1], env, env_tab));
}