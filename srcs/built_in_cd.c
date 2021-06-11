/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:48:53 by rolaforg          #+#    #+#             */
/*   Updated: 2021/06/11 11:49:31 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	update_pwd(t_env *env, char ***env_tab)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp("PWD", ((t_env_var *)tmp->content)->key) == 0)
		{
			free(((t_env_var *)tmp->content)->value);
			((t_env_var *)tmp->content)->value = current_path();
			if (((t_env_var *)tmp->content)->value == NULL)
				return (1);
		}
		tmp = tmp->next;
	}
	ft_free_tab(*env_tab);
	*env_tab = env_to_tab(env);
	if (!*env_tab)
		return (0);
	return (0);
}

int	built_in_cd(char *path, t_env *env, char ***env_tab)
{
	char	*home;

	home = get_var_value(env, "HOME");
	if (!path)
	{
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 1);
			return (1);
		}
		path = home;
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd(": ", 1);
		ft_putendl_fd(strerror(errno), 1);
	}
	else
		return (update_pwd(env, env_tab));
	return (1);
}
