/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:32:26 by csapt             #+#    #+#             */
/*   Updated: 2021/06/11 16:40:49 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *get_var_value(t_env *env, char *var_name)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(var_name, ((t_env_var*)tmp->content)->key) == 0)
			return (((t_env_var*)tmp->content)->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int exported_env_len(t_env *env)
{
	int x;
	t_env *tmp;

	x = 0;
	tmp = env;
	while (tmp)
	{
		if (((t_env_var*)tmp->content)->exported == 1)
			x++;
		tmp = tmp->next;
	}
	return (x);
}

int check_exist_var(char *str_env, t_env *env, bool exported)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(str_env, ((t_env_var*)tmp->content)->key, ft_strlento(((t_env_var*)tmp->content)->key, '=')) == 0) //TODO: pas sur de ca recheck
		{
			if (exported)
				((t_env_var*)tmp->content)->exported = true;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char **env_to_tab(t_env *env)
{
	int x;
	char **tab;
	t_env *tmp;

	x = 0;
	tmp = env;
	tab = malloc((exported_env_len(env) + 1) * sizeof(char*));
	if (!tab)
		return (NULL);
	while (tmp)
	{
		if (((t_env_var*)tmp->content)->exported == 1 && ((t_env_var*)tmp->content)->value) //leaks car exported_env_len peut etre trop long
		{
			tab[x] = argv_join("%s=%s", ((t_env_var*)tmp->content)->key, ((t_env_var*)tmp->content)->value);
			if (!tab[x])
			{
				ft_free_tab(tab);
				return (NULL);
			}
			x++;
		}
		tmp = tmp->next;
	}
	tab[x] = NULL;
	return (tab);
}
