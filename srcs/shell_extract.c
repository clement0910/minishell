/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 19:06:56 by                   #+#    #+#             */
/*   Updated: 2021/06/16 19:54:43 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	extract_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], ">>") == 0 || ft_strcmp(tab[i], ">") == 0
			|| ft_strcmp(tab[i], "|") == 0)
			break ;
		i++;
	}
	return (i);
}

char	**extract_cmds(char **tab)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (extract_len(tab) + 1));
	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], ">>") == 0 || ft_strcmp(tab[i], ">") == 0
			|| ft_strcmp(tab[i], "|") == 0)
			break ;
		res[i] = ft_strdup(tab[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**extract_redirs(char **tab)
{
	char	**res;
	int		i;

	i = extract_len(tab);
	res = malloc(sizeof(char *) * 1);
	res[0] = NULL;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], ">") != 0 && ft_strcmp(tab[i], ">>") != 0)
			res = ft_tab_addback(res, tab[i]);
		i++;
	}
	return (res);
}
