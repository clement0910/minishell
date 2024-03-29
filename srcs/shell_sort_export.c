/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_sort_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:25:11 by csapt             #+#    #+#             */
/*   Updated: 2021/06/12 13:05:18 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	exported_env_len(t_env *env)
{
	int		x;
	t_env	*tmp;

	x = 0;
	tmp = env;
	while (tmp)
	{
		if (((t_env_var *)tmp->content)->exported == 1)
			x++;
		tmp = tmp->next;
	}
	return (x);
}

int	sort_ascii_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (tab[i + 1] == NULL)
			return (0);
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			if (str_replace(&tab[i], &tab[i + 1]))
				return (1);
			i = 0;
		}
		else
			i++;
	}
	return (0);
}

char	*create_export_env(t_env_var *env)
{
	char	*ret;

	if (env->value == NULL)
		ret = argv_join("declare -x %s", env->key);
	else
		ret = argv_join("declare -x %s=\"%s\"", env->key, env->value);
	if (!ret)
		return (NULL);
	else
		return (ret);
}

char	**create_export_tab(t_env *env)
{
	int		i;
	char	**tab;
	t_env	*tmp;

	i = 0;
	tmp = env;
	tab = malloc((exported_env_len(env) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (tmp)
	{
		if (((t_env_var *)tmp->content)->exported == 1)
		{
			tab[i] = create_export_env((t_env_var *)tmp->content);
			if (!tab[i])
			{
				ft_free_tab(tab);
				return (NULL);
			}
			i++;
		}
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}
