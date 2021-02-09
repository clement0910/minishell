/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:31:44 by csapt             #+#    #+#             */
/*   Updated: 2021/02/09 15:41:55 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char **ft_lst_to_tab(t_envlst **lst)
{
	int x;
	int len;
	char **tab;
	t_envlst *tmp;

	len = ft_lst_size(*lst);
	tmp = *lst;
	if (!(tab = malloc((len + 1) * sizeof(char*))))
		return (NULL);
	while (tmp)
	{
		tab[x] = ft_strjoin(((t_env*)tmp->content)->key, ft_strjoin("=",((t_env*)tmp->content)->value));
		tmp = tmp->next;
		x++;
	}
	tab[x] = NULL;
	return (tab);
}

char **ft_strtabdup(char **src)
{
	int x;
	int tablen;
	char **ret;

	x = 0;
	if ((tablen = ft_tablen(src)) == 0)
		return (NULL);
	if (!(ret = malloc((tablen + 1) * sizeof(char*))))
		return (NULL);
	while (x < tablen)
	{
		if (!(ret[x] = ft_strdup(src[x])))
		{
			ret[x] = NULL;
			ft_free_tab(ret);
			free(ret);
			return (NULL);
		}
		x++;
	}
	ret[x] = NULL;
	return (ret);
}

int ft_export(t_global *glb)
{
	t_envlst *lst;
	t_env *env;

	if (!(env = get_env_value(glb->command[1])))
		return(1);
	if (!(lst = ft_lst_new(env)))
		return (1);
	print_tab(glb->env);
	ft_printf("-----------------\n");
	ft_lst_addback(&glb->env_list, lst);
	//print_lst_tab(&glb->env_list);
	free(glb->env);
	glb->env = ft_lst_to_tab(&glb->env_list);
	print_tab(glb->env);
	return (0);
}