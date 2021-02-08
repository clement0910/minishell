/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:48:53 by csapt             #+#    #+#             */
/*   Updated: 2021/02/08 16:15:18 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	built_in_cd(t_global *glb)
{
	if (!glb->command[1])
	{
		if (chdir(glb->home) == -1)
			return(return_strerror());
	}
	else 
	{
		if (chdir(glb->command[1]) == -1)
		{
			return_strerror();
			return(0);
		}
	}
	return (0);
}