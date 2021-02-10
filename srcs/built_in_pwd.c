/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:00:31 by csapt             #+#    #+#             */
/*   Updated: 2021/02/10 14:34:27 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	built_in_pwd(char **cwd) //opti - protect
{
	if (!(*cwd = malloc(BUFFER_SIZE * sizeof(char))))
		return (1);
	*cwd = getcwd(*cwd, BUFFER_SIZE);
	ft_putendl_fd(*cwd, 1);
	return (0);
}