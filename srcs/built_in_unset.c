/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:53:02 by csapt             #+#    #+#             */
/*   Updated: 2021/04/28 15:53:21 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int built_in_unset(t_parse *command, char ***env_tab, t_env **env)
{
	t_env *tmp;
	t_env *before_tmp;
	t_env *tmp_next;

	tmp = *env;
	before_tmp = NULL;
	if (!command->tab_command[1])
		return (1);
	while (tmp)
	{
		if (ft_strcmp(command->tab_command[1], ((t_env_var*)tmp->content)->key) == 0)
		{
			tmp_next = tmp->next;
			ft_lst_delone(tmp, free_env);
			before_tmp->next = NULL;
			if (before_tmp)
				ft_lst_addback(&(before_tmp), tmp_next);
			else
				*env = tmp->next;
			before_tmp = tmp;
			tmp = tmp_next;
		}
		else
		{
			before_tmp = tmp;
			tmp = tmp->next;
		}
	}
	ft_free_tab(*env_tab);
	*env_tab = env_to_tab(*env);
	display_export(*env);
	return (0);
}
