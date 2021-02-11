/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:31:44 by csapt             #+#    #+#             */
/*   Updated: 2021/02/11 16:09:34 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int built_in_export(char **command, char ***env_tab, t_envlst **env_list)
{
	t_envlst *lst;
	t_env *env;

	if (!(env = get_env_data(command[1])))
		return(1);
	if (!(lst = ft_lst_new(env)))
		return (1);
	ft_lst_addback(env_list, lst);
	//print_lst_tab(env_list);
	ft_free_tab(*env_tab);
	*env_tab = ft_lst_to_tab(env_list);
	return (0);
}