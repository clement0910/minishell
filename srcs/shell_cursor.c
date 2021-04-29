/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:54:34 by rolaforg          #+#    #+#             */
/*   Updated: 2021/04/28 18:53:54 by rolaforg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_cursor(int ret)
{
	char	*folder;

	folder = current_folder();
	if (ret)
	{
		ft_putstr_fd(folder, 1);
		ft_putstr_fd(" \e[31m>\e[39m ", 1);
	}
	else
	{
		ft_putstr_fd(folder, 1);
		ft_putstr_fd(" \e[32m>\e[39m ", 1);
	}
	free(folder);
}