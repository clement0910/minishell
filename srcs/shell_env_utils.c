/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:32:26 by csapt             #+#    #+#             */
/*   Updated: 2021/06/12 12:53:36 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_var_value(t_env *env, char *var_name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(var_name, ((t_env_var *)tmp->content)->key) == 0)
			return (((t_env_var *)tmp->content)->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	exported_tab_env_len(t_env *env)
{
	int		x;
	t_env	*tmp;

	x = 0;
	tmp = env;
	while (tmp)
	{
		if (((t_env_var *)tmp->content)->exported == true
			&& ((t_env_var *)tmp->content)->value)
			x++;
		tmp = tmp->next;
	}
	return (x);
}

int	check_exist_var(char *str_env, t_env *env, bool exported)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(str_env, ((t_env_var *)tmp->content)->key,
				ft_strlento(((t_env_var *)tmp->content)->key, '=')) == 0)
		{
			if (exported)
				((t_env_var *)tmp->content)->exported = true;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	**env_to_tab(t_env *env)
{
	char	**tab;

	tab = malloc((exported_tab_env_len(env) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	if (create_tab_env(env, tab))
		return (NULL);
	else
		return (tab);
}

int	create_tab_env(t_env *env, char **tab)
{
	int		x;
	t_env	*tmp;

	tmp = env;
	x = 0;
	while (tmp)
	{
		if (((t_env_var *)tmp->content)->exported == true
			&& ((t_env_var *)tmp->content)->value)
		{
			tab[x] = argv_join("%s=%s", ((t_env_var *)tmp->content)->key,
					((t_env_var *)tmp->content)->value);
			if (!tab[x])
			{
				ft_free_tab(tab);
				return (1);
			}
			x++;
		}
		tmp = tmp->next;
	}
	tab[x] = NULL;
	return (0);
}
