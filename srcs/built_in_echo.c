/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 14:42:10 by rolaforg          #+#    #+#             */
/*   Updated: 2021/04/29 14:42:13 by rolaforg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		quote_mode(char *str)
{
	if (str)
	{
		if (str[0] == 34 || str[0] == 39)
			return (str[0]);
	}
	return (0);
}

unsigned int begin_with(char *str, char *prefix) // TODO Move in another file
{
        unsigned int    i;
        unsigned int    size;

        i = 0;
        if (!(size = ft_strlen(prefix)) || !(ft_strlen(str)))
                return (0);
        while (str[i] && prefix[i])
        {
                if (str[i] == prefix[i])
                {
                        i++;
                        if (i == size)
						{
							while (ft_isws(str[i]))
								i++;
                            return (i);
						}
                }
                else
                        return (0);
        }
        return (0);
}

int	built_in_echo(char **args)
{
	int	x;
	int	i;
	int	jump;
	int	skip;

	x = 0;
	
	if (args[1])
		jump = begin_with(args[1], "-n");
	else
		jump = 0;

	//command = replace_vars(command, env);
	while (args[++x])
	{
		i = 0;
		skip = quote_mode(args[x]);
		if ((x > 1 && !jump) || (jump && x > 2))
			write(1, " ", 1);
		while (args[x][i] && (!jump || (jump && x != 1)))
		{
			if (!skip || (args[x][i] != skip || args[x][i - 1] == '\\') && (args[x][i] != '\\' || args[x][i - 1] == '\\'))
			{
				write(1, &args[x][i], 1);
				if (args[x][i - 1] == '\\')
					i++;
			}
			i++;
		}			
	}
	if (!jump)
		write(1, "\n", 1);
	return (0);
}
