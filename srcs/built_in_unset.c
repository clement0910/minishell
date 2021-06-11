/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:53:02 by csapt             #+#    #+#             */
/*   Updated: 2021/06/10 18:52:32 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void delete_from_env(t_env **tmp, t_env **tmp_next, t_env **before_tmp, t_env **env)
{
	*tmp_next = (*tmp)->next;
	ft_lst_delone(*tmp, free_env);
	(*before_tmp)->next = NULL;
	if (*before_tmp)
		ft_lst_addback(before_tmp, *tmp_next);
	else
		*env = (*tmp)->next;
	*before_tmp = *tmp;
	*tmp = *tmp_next;
}

int built_in_unset(char *var_name, char ***env_tab, t_env **env)
{
	t_env *tmp;
	t_env *before_tmp;
	t_env *tmp_next;

	tmp = *env;
	before_tmp = NULL;
	if (!var_name)
		return (1);
	while (tmp)
	{
		if (ft_strcmp(var_name, ((t_env_var*)tmp->content)->key) == 0)
			delete_from_env(&tmp, &tmp_next, &before_tmp, env);
		else
		{
			before_tmp = tmp;
			tmp = tmp->next;
		}
	}
	ft_free_tab(*env_tab);
	*env_tab = env_to_tab(*env);
	if (!*env_tab)
		return (1);
	return (0);
}
