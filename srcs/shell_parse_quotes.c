/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:27:31 by csapt             #+#    #+#             */
/*   Updated: 2021/06/15 18:42:08 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	check_backslash(const char *buff, int *i)
{
	if (buff[*i] == '\\')
	{
		(*i)++;
		if (buff[*i] == '\0')
			return (1);
		else
			(*i)++;
		return (2);
	}
	return (0);
}

int	check_quotes(const char *buff, int *i)
{
	if (buff[*i] == '\'')
	{
		(*i)++;
		while (buff[*i] != '\'')
		{
			if (buff[*i] == '\0')
				return (1);
			(*i)++;
		}
		(*i)++;
	}
	return (0);
}

int	check_double_quotes(const char *buff, int *i)
{
	if (buff[*i] == '\"')
	{
		(*i)++;
		while (buff[*i] != '\"')
		{
			if (check_backslash(buff, i) == 0)
				(*i)++;
			if (buff[*i] == '\0')
				return (1);
		}
		(*i)++;
	}
	return (0);
}

int	check_quotes_and_backslash(const char *buff)
{
	int	i;

	i = 0;
	while (buff[i])
	{
		if (check_backslash(buff, &i))
			return (1);
		if (check_quotes(buff, &i))
			return (1);
		if (check_double_quotes(buff, &i))
			return (1);
		if (buff[i] != '\0' && (buff[i] != '\'' && buff[i] != '\"'
				&& buff[i] != '\\'))
		{
			i++;
		}
	}
	return (0);
}
