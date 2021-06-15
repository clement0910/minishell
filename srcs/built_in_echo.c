/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_built_in_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 15:54:33 by csapt             #+#    #+#             */
/*   Updated: 2021/06/15 16:43:35 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_str_echo(char *str)
{
	int i;
	char sign;

	i = 0;
	if (!str)
		return ;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
			{
				ft_putchar_fd(str[i], 1);
				i++;
			}
			i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"' && str[i])
			{
				if (str[i] == '\\')
				{
					if (str[i + 1] != '\"')
					{
						ft_putchar_fd(str[i], 1);
						i++;
					}
					else
						i++;
					while (str[i] == '\\')
					{
						i++;
						if (str[i] == '\\') {
							ft_putchar_fd(str[i], 1);
							i++;
						}
						else
							break ;
					}
				}
				ft_putchar_fd(str[i], 1);
				i++;
			}
		}
		while ((str[i] != '\'' && str[i] != '\"') && str[i])
		{
			if (str[i] == '\\')
			{
				while (str[i] == '\\')
				{
					i++;
					if (str[i] == '\\') {
						ft_putchar_fd(str[i], 1);
						i++;
					}
					else
						break ;
				}
			}
			ft_putchar_fd(str[i], 1);
			i++;
		}
	}
}

int built_in_echo(char **argv)
{
	int i;
	bool newline;

	i = 0;
	newline = true;
	if (!argv || !argv[0])
		return (0);
	if (ft_strcmp(argv[0], "-n") == 0)
	{
		newline = false;
		i++;
	}
	while (argv[i])
	{
		print_str_echo(argv[i]);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}