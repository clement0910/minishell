/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:42:35 by csapt             #+#    #+#             */
/*   Updated: 2021/04/27 17:47:49 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	built_in_export(t_parse *command, t_env **env, char ***env_tab)
{
	t_env *lst;
	t_env_var *env_var;

	if (!command->tab_command[1])
		return (0);
	if (ft_chrcmp(command->tab_command[1], '='))
		return (2); //TODO: check ce cas ou il y a "export <nom var>"
	else
	{
		env_var = get_env_var(command->tab_command[1], 1);
		if (!env_var)
			return (1);
	}
	lst = ft_lst_new(env_var);
	if (!lst)
	{
		free(env_var);
		return (0);
	}
	ft_lst_addback(env, lst);
	ft_free_tab(*env_tab);
	*env_tab = env_to_tab(*env);
	return (1);
}