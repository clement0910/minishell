/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:48:53 by rolaforg          #+#    #+#             */
/*   Updated: 2021/04/29 14:55:48 by rolaforg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	built_in_cd(char *path, char *home)
{
	if (!path)
	{
		if (!home)
		{
			printf("Home is NULL");
		}
		if (chdir(home) == -1)
			return(1);
	}
	else 
	{
		if (chdir(path) == -1)
		{
			return(1);
		}
	}
	return (0);
}