/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:48:53 by rolaforg          #+#    #+#             */
/*   Updated: 2021/04/29 17:46:59 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	built_in_cd(char *path, char *home)
{
	if (!path)
	{
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 1);
			return (1);
		}
		path = home;
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd(": ", 1);
		ft_putendl_fd(strerror(errno), 1);
	}
	return (0);
}