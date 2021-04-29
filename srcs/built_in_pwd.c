/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:48:53 by rolaforg          #+#    #+#             */
/*   Updated: 2021/04/29 15:01:30 by rolaforg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	built_in_pwd(void)
{
	char *path = current_path();
	if (path)
	{
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
		free(path);
		return (0);
	}
	return (1);
}