/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_built_in_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 15:54:33 by csapt             #+#    #+#             */
/*   Updated: 2021/06/15 18:51:38 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_backslash(const char *str, int *i, int quote)
{
	if (quote)
	{
		if (str[*i] == '\\' && str[*i + 1] == '\'')
		{
			write(1, &str[*i], 2);
			(*i) += 2;
		}
		return ;
	}
	if (str[*i] == '\\')
	{
		(*i)++;
		write(1, &str[*i], 1);
		if (str[*i] != '\0')
			(*i)++;
	}
}

void	print_quotes(const char *str, int *i)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
		{
			write(1, &str[*i], 1);
			(*i)++;
		}
		if (str[*i] != '\0')
			(*i)++;
	}
}

void	print_double_quotes(const char *str, int *i)
{
	if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\"')
		{
			if (str[*i] == '\\' && str[*i + 1] == '\'')
				print_backslash(str, i, 1);
			else
				print_backslash(str, i, 0);
			if (str[*i] == '\"')
				break ;
			if (str[*i] == '\0')
				return ;
			if (str[*i] != '\\')
			{
				write(1, &str[*i], 1);
				(*i)++;
			}
		}
		if (str[*i] != '\0')
			(*i)++;
	}
}

void	print_echo_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		print_backslash(str, &i, 0);
		print_quotes(str, &i);
		print_double_quotes(str, &i);
		if (str[i] != '\0' && (str[i] != '\'' && str[i] != '\"' && str[i] != '\\'))
		{
			write(1, &str[i], 1);
			i++;
		}
	}
}

int	built_in_echo(char **argv)
{
	int		i;
	bool	newline;
	bool	space;

	i = 0;
	newline = true;
	space = false;
	if (!argv || !argv[0])
		return (0);
	if (ft_strcmp(argv[0], "-n") == 0)
	{
		newline = false;
		i++;
	}
	while (argv[i])
	{
		if (space)
			write(1, " ", 1);
		space = true;
		print_echo_str(argv[i]);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
