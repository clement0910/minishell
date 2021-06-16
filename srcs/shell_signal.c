/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 19:53:13 by csapt             #+#    #+#             */
/*   Updated: 2021/06/16 20:08:24 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sigint_signal(int num)
{
	(void)num;
	write(1, "\n", 1);
	print_cursor(1);
}

void	read_line(char **buff)
{
	char	tmp[3];
	char	*tmp2;

	if (read(0, tmp, 1) == 0)
	{
		ft_putendl_fd("exit", 1);
		*buff = ft_strdup("exit");
	}
	else if (tmp[0] == '\n')
		*buff = ft_strdup("");
	else
	{
		tmp[1] = '\0';
		if (get_next_line(0, &tmp2) == -1)
			return ;
		*buff = ft_strjoin(tmp, tmp2);
		free(tmp2);
	}
}
