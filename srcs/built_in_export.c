/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:31:44 by csapt             #+#    #+#             */
/*   Updated: 2021/02/16 11:59:37 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


t_envlst*	sort_ascii_lst(t_envlst **lst)
{
	char *str_tmp;;
	t_envlst *tmp;

	tmp = *lst;
	while (tmp->next)
	{
		if ((ft_strcmp(((t_env_var*)tmp->content)->key, ((t_env_var*)tmp->next->content)->key)) > 0)
		{
			if (!(str_tmp = ft_strdup(((t_env_var*)tmp->content)->key)))
				return (NULL);
			free(((t_env_var*)tmp->content)->key);
			if (!(((t_env_var*)tmp->content)->key = ft_strdup(((t_env_var*)tmp->next->content)->key)))
				return (NULL);
			free(((t_env_var*)tmp->next->content)->key);
			if (!(((t_env_var*)tmp->next->content)->key = ft_strdup(str_tmp)))
				return (NULL);
			tmp = *lst;
		}
		else
			tmp = tmp->next;
	}
	tmp = *lst;
	return (tmp);
}

int		print_declare(t_envlst **env_lst)
{
	t_envlst *tmp;

	tmp = sort_ascii_lst(env_lst); //why tmp?
	while (tmp)
	{
		if (((t_env_var*)tmp->content)->local == false)
		{
			ft_printf("declare -x %s", ((t_env_var*)tmp->content)->key);
			if (((t_env_var*)tmp->content)->value)
				ft_printf("=\"%s\"", ((t_env_var*)tmp->content)->value);
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int		built_in_export(char **command, t_env *env)
{
	t_envlst *lst;
	t_env_var *env_var;

	if (!command[1]) //Condition if no arguments
	{
		print_declare(&env->env_lst_ascii);
		return (0);
	}
	if (!(env_var = get_env_data(command[1])))
		return(1);
	if (!(lst = ft_lst_new(env_var)))
		return (1);
	ft_lst_addback(&env->env_lst, lst);
	ft_free_tab(env->env_tab);
	env->env_tab = ft_lst_to_tab(&env->env_lst);
	return (0);
}