/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 21:36:46 by csapt             #+#    #+#             */
/*   Updated: 2021/02/04 15:59:29 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void example_function(void)
{
	return ;
}

int main(int ac, char **av)
{
	char *buf;

	(void)ac;
	(void)av;
	example_function();
	buf = ft_calloc(BUFFER_SIZE, sizeof(char));
	ft_printf("> ");
	while (read(0, buf, BUFFER_SIZE) != 0)
	{
		printf("COMMAND: [%s]\n", buf);
		ft_printf ("> ");
	}
	free(buf);
	return (0);
}