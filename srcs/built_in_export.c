/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:42:35 by csapt             #+#    #+#             */
/*   Updated: 2021/06/11 11:33:43 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int export_var(char *var, t_env **env, char ***env_tab)
{
	t_env *lst;
	t_env_var *env_var;

	if (check_exist_var(var, *env, 1))
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

int replace_env_value(char *str_env, t_env *env, char ***env_tab, int exported)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(str_env, ((t_env_var*)tmp->content)->key,
					   ft_strlento(((t_env_var*)tmp->content)->key, '=')) == 0) //TODO: pas sur de ca recheck
		{
			free(((t_env_var*)tmp->content)->value);
			((t_env_var*)tmp->content)->value = ft_strdup(ft_strchr(str_env, '=') + 1);
			if (((t_env_var*)tmp->content)->value == NULL)
				return (0);
		}
		tmp = tmp->next;
	}
	if (exported)
	{
		ft_free_tab(*env_tab);
		*env_tab = env_to_tab(env);
		if (!*env_tab)
			return (0);
	}
	return (1);
}

int export_env(char *str_env, t_env **env, char ***env_tab, int exported)
{
	t_env *lst;
	t_env_var *env_var;

	env_var = get_env_var(str_env, exported);
	if (!env_var)
		return (0);
	if (addback_env(env_var, env) == 0)
		return (0);
	if (exported)
	{
		ft_free_tab(*env_tab);
		*env_tab = env_to_tab(*env);
		if (!*env_tab)
			return (0);
	}
	return (1);
}

int display_export(t_env *env)
{
	char **tab;

	tab = create_export_tab(env);
	if (!tab)
		return (0);
	sort_ascii_tab(tab);
	print_tab(tab);
	ft_free_tab(tab);
	return (1);
}

int built_in_export(int exported, char *str_env, t_env **env, char ***env_tab)
{
	if (exported && str_env == NULL)
		return (display_export(*env));
	if (exported && ft_chrcmp(str_env, '='))
		return (export_var(str_env, env, env_tab));
	if (check_addback(str_env))
		return (addback_env_value(str_env, env, env_tab, exported));
	else if (check_exist_var(str_env, *env, exported))
		return (replace_env_value(str_env, *env, env_tab, exported));
	else
		return (export_env(str_env, env, env_tab, exported));
}