/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:48:53 by rolaforg          #+#    #+#             */
/*   Updated: 2021/06/11 16:58:29 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	built_in_pwd(void)
{
	char	*path;

	path = current_path();
	if (!path)
		return (1);
	ft_putendl_fd(path, 1);
	free(path);
	return (0);
}
