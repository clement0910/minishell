/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 18:31:39 by csapt             #+#    #+#             */
/*   Updated: 2021/06/13 18:36:28 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	func_2(char *openblock, char **input, int *iBlock, int *iBlockIndex)
{
	char	*block;

	block = NULL;
	block = ft_strchr(openblock, **input);
	if (block != NULL)
	{
		*iBlock = 1;
		*iBlockIndex = block - openblock;
		(*input)++;
	}
	return ;
}

void	func_1(char **input, char *openblock, char *closeblock, char *delimit)
{
	int	iBlock;
	int	iBlockIndex;

	iBlock = 0;
	iBlockIndex = 0;
	while (**input != '\0')
	{
		if (iBlock)
		{
			if (closeblock[iBlockIndex] == **input)
				iBlock = 0;
			(*input)++;
		}
		func_2(openblock, input, &iBlock, &iBlockIndex);
		if (ft_strchr(delimit, **input) != NULL)
		{
			if (ft_strchr(delimit, **input + 1) == NULL)
				**input = '\0';
			else
				(*input)++;
			(*input)++;
			break ;
		}
		(*input)++;
	}
}

char	**func_4(char *lead, char **tab, int *i)
{
	char	**tmp;
	char	**ret;

	tmp = ft_strtabdup(tab);
	ft_free_tab(tab);
	if (!tmp)
		return (NULL);
	ret = malloc(sizeof(char *) * (ft_tablen(tmp) + 2));
	if (!ret)
	{
		ft_free_tab(tmp);
		return (NULL);
	}
	while (tmp[*i] && tmp[*i][0])
	{
		ret[*i] = ft_strdup(tmp[*i]);
		(*i)++;
	}
	ft_free_tab(tmp);
	return (ret);
}

char	**func_3(char *lead, char **tab)
{
	int		i;
	char	**tmp;
	char	**ret;

	i = 0;
	if (lead && ft_strlen(lead)) //pourquoi verifier 2x ?
	{
		if (tab && tab[0] && ft_tablen(tab))
			ret = func_4(lead, tab, &i);
		else
			ret = malloc(sizeof(char *) * 2);
		ret[i] = ft_strdup(lead);
		i++;
		ret[i] = NULL;
	}
	else
		return (tab);
	return (ret);
}

char	**strmbtok(char *input, char *delimit, char *openblock, char *closeblock)
{
	char	**tab;
	char	*lead;
	char	*tmp;

	tab = NULL;
	if (input != NULL)
		lead = input;
	while (lead)
	{
		lead = input;
		if (*input == '\0')
			lead = NULL;
		func_1(&input, openblock, closeblock, delimit);
		tab = func_3(lead, tab);
	}
	return (tab);
}
