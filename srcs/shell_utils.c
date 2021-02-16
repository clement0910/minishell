/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:14:34 by csapt             #+#    #+#             */
/*   Updated: 2021/02/16 12:19:42 by csapt            ###   ########lyon.fr   */
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
		tab[x] = ft_strjoin(((t_env_var*)tmp->content)->key, ft_strjoin("=",((t_env_var*)tmp->content)->value));
		tmp = tmp->next;
		x++;
	}
	tab[x] = NULL;
	return (tab);
}

void	print_lst_tab(t_envlst **yolo)
{
	t_envlst *tmp;

	tmp = *yolo;
	while (tmp)
	{
		printf("[%s]=[%s]\n", ((t_env_var*)tmp->content)->key, ((t_env_var*)tmp->content)->value);
		tmp = tmp->next;
	}
}

int	ft_lstsize_value(t_envlst *lst) //made an universal func 
{
	int x;
	t_envlst *tmp;

	x = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		if (((t_env_var*)tmp->content)->local == false)
			x++;
	}
	return (x);
}

char **lstenv_to_tab(t_envlst *lst)
{
	int len;
	char **tab;
	t_envlst *tmp;

	tmp = *lst;
	len = ft_lstsize_value(tmp);
	if (!(tab = malloc((len + 1) * sizeof(char*))))
		return (NULL);
	while (tmp)
	{
		if (((t_env_var*)tmp->content)->local == false)
		{
			tab[x] = ft_strjoin(((t_env_var*)tmp->content)->key, ft_strjoin("=",((t_env_var*)tmp->content)->value));
			tmp = tmp->next;
			x++;
		}
	}
	tab[x] = NULL;
	return (tab);
}

char *envlst_to_str(char *key, char *value)
{
	int len;
	char *str;

	if (value == NULL)
		len = ft_strlen(key);
	else
		len = ft_strlen(key) + ft_strlen(value) + 3;
	if (!(str = malloc((len + 1) * sizeof(char))))
		return (NULL);
	str = ft_strcpy
}