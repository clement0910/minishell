/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 18:31:39 by csapt             #+#    #+#             */
/*   Updated: 2021/06/15 16:20:56 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	check_block(char *openblock, char **input, int *iBlock, int *iBlockIndex)
{
	char	*block;

	block = NULL;
	block = ft_strchr(openblock, **input);
	if (**input == '\0')
		return (1);
	if (block != NULL)
	{
		*iBlock = 1;
		*iBlockIndex = block - openblock;
		(*input)++;
	}
	if (**input == '\0')
		return (1);
	return (0);
}

void	delimit_command(char **input, char *openblock, char *closeblock, char *delimit)
{
	int	iBlock;
	int	iBlockIndex;

	iBlock = 0;
	while (**input != '\0')
	{
		if (iBlock)
		{
			if (closeblock[iBlockIndex] == **input)
				iBlock = 0;
			(*input)++;
		}
		if (check_block(openblock, input, &iBlock, &iBlockIndex))
			break ;
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

char	**tab_command_add(char **tab, int *i)
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

char	**create_command_tab(char *lead, char **tab)
{
	int		i;
	char	**tmp;
	char	**ret;

	i = 0;
	if (lead && ft_strlen(lead)) //pourquoi verifier 2x ?
	{
		if (tab && tab[0] && ft_tablen(tab))
			ret = tab_command_add(tab, &i);
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


	tab = NULL;
	if (input != NULL)
		lead = input;
	while (lead)
	{
		lead = input;
		if (*input == '\0')
			lead = NULL;
		delimit_command(&input, openblock, closeblock, delimit);
		tab = create_command_tab(lead, tab);
	}
	return (tab);
}
