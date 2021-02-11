/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:14:34 by csapt             #+#    #+#             */
/*   Updated: 2021/02/11 16:10:33 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char **ft_lst_to_tab(t_envlst **lst)
{
	int x;
	int len;
	char **tab;
	t_envlst *tmp;

	x = 0;
	tmp = *lst;
	len = ft_lst_size(*lst);
	if (!(tab = malloc((len + 1) * sizeof(char*))))
		return (NULL);
	while (tmp)
	{
		tab[x] = ft_strjoin(((t_env*)tmp->content)->key, ft_strjoin("=",((t_env*)tmp->content)->value));
		tmp = tmp->next;
		x++;
	}
	tab[x] = NULL;
	//print_tab(tab);
	return (tab);
}

void	print_lst_tab(t_envlst **yolo)
{
	t_envlst *tmp;

	tmp = *yolo;
	while (tmp)
	{
		printf("[%s]=[%s]\n", ((t_env*)tmp->content)->key, ((t_env*)tmp->content)->value);
		tmp = tmp->next;
	}
}