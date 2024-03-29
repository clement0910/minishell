/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_local_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:53:59 by csapt             #+#    #+#             */
/*   Updated: 2021/06/11 17:34:11 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	addback_value(char *str_env, t_env *env, char ***env_tab)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(str_env, ((t_env_var *)tmp->content)->key,
				 ft_strlento(((t_env_var *)tmp->content)->key, '=')) == 0)
		{
			((t_env_var *)tmp->content)->value = ft_strfreejoin(((t_env_var *)
						tmp->content)->value, ft_strchr(str_env, '=') + 1);
			if (((t_env_var *)tmp->content)->value == NULL)
				return (1);
			if (((t_env_var *)tmp->content)->exported)
			{
				ft_free_tab(*env_tab);
				*env_tab = env_to_tab(env);
				if (!*env_tab)
					return (1);
			}
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	addback_env_value(char *str_env, t_env **env, char ***env_tab,
						 bool exported)
{
	char	*tmp;

	if (check_exist_var(str_env, *env, exported) == 1)
	{
		if (addback_value(str_env, *env, env_tab))
			return (1);
		else
			return (0);
	}
	else
	{
		tmp = ft_strfreejoin(ft_strdupto(str_env, '+'),
				ft_strchr(str_env, '='));
		if (!tmp)
			return (1);
		if (export_env(tmp, env, env_tab, exported))
		{
			free(tmp);
			return (1);
		}
		free(tmp);
		return (0);
	}
}

int	addback_env(t_env_var *env_var, t_env **env)
{
	t_env	*lst;

	lst = ft_lst_new(env_var);
	if (!lst)
	{
		free(env_var);
		return (1);
	}
	ft_lst_addback(env, lst);
	return (0);
}

int	check_addback(const char *str_env)
{
	int	x;

	x = 0;
	while (str_env[x])
	{
		if (str_env[x] == '=')
			return (0);
		if (str_env[x] == '+' && str_env[x + 1] == '=')
			return (1);
		x++;
	}
	return (0);
}
