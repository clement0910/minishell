/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:48:53 by csapt             #+#    #+#             */
/*   Updated: 2021/02/10 13:52:42 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	built_in_cd(char **command, char *home)
{
	if (!command[1])
	{
		if (!home)
		{
			//error
		}
		if (chdir(home) == -1)
			return(return_strerror());
	}
	else 
	{
		if (chdir(command[1]) == -1)
		{
			return_strerror();
			return(0);
		}
	}
	return (0);
}