/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 21:36:46 by csapt             #+#    #+#             */
/*   Updated: 2021/01/25 10:37:57 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int main(int ac, char **av)
{
	char *buf;
	int error;

	buf = malloc(BUFFER_SIZE);
	ft_printf("> ");
	while (read(0, buf, BUFFER_SIZE) != 0)
	{
		printf("COMMAND: [%s]\n", buf);
		ft_printf ("> ");
	}
	return (0);
}