/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:59:25 by csapt             #+#    #+#             */
/*   Updated: 2021/02/15 15:36:48 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	built_in_unset(char **command, t_env *env)
{
	// int x;
	// int i;
	// t_envlst *tmp;
	// t_envlst *tmpn;
	// t_envlst *lasttmp;
	
	// lasttmp = NULL;
	// tmp = *lst;
	// x = ft_lst_size(tmp);
	// i = 0;
	// if (!(command[1]))
	// 	return (1);
	// printf("LIST TAILLE: %d\n", x);
	// while (tmp)
	// {
	// 	printf("%p\n", tmp);
	// 	if (i >= x)
	// 	{
	// 		printf("%p\n", tmp);
	// 		printf("%p\n", tmp->next);
	// 		exit(1);		
	// 	}
		
	// 	if (ft_strcmp(command[1], ((t_env*)tmp->content)->key) == 0)
	// 	{
	// 		printf("1\n");
	// 		tmpn = tmp->next;
	// 		ft_lst_delone(tmp, free);
	// 		lasttmp->next = NULL;
	// 		if (lasttmp)
	// 			ft_lst_addback(&(lasttmp), tmpn);
	// 		else
	// 			*lst = tmpn;
	// 		lasttmp = tmp;
	// 		tmp = tmpn;
	// 	}
	// 	else
	// 	{
	// 		printf("2\n");
	// 		lasttmp = tmp;
	// 		tmp = tmp->next;
	// 	}
	// 	i++;
	// }
	// print_tab(*env_tab);
	// ft_free_tab(*env_tab);
	// *env_tab = ft_lst_to_tab(lst);
	// print_tab(*env_tab);
	// return (0);
	return (0);
}