/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:10:51 by csapt             #+#    #+#             */
/*   Updated: 2021/02/04 11:11:51 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_echo(char **command) //opti
{
	int x;
	bool n;

	x = 1;
	n = false;
	if ((command[1]) && (ft_strcmp(command[1],"-n") == 0))
	{
		x++;
		n = true;
	}
	while (command[x] != NULL)
	{
		ft_putstr_fd(command[x], 1);
		x++;
		if (command[x])
			write(1, " ", 1);
	}
	if (n == false)
		write(1, "\n", 1);
	return (0);
}
