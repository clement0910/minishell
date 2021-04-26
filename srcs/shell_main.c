/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:31:34 by csapt             #+#    #+#             */
/*   Updated: 2021/04/26 17:06:36 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int launch_shell(t_global *glb)
{
	char *buf;

	while (1)
	{
		ft_putstr_fd("Minishell > ", 1);
		if (get_next_line(0, &buf) == -1)
			return (ret_errno_msg("get_next_line error", 0));
		if (parse_command(&buf, glb->command) == 0)
			return (ret_msg("parsing error", 0)); //TODO: check error msg
		built_in_command(glb->command);
		if (ft_strcmp(glb->command->tab_command[0], "exit") == 0)
			return (0);
		ft_free_tab(glb->command->tab_command);
	}
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_global *glb;

	glb = ft_calloc(1, sizeof(t_global));
	if (!glb)
		return (ret_errno_msg(NULL, 1));
	if (init_var(glb, envp) == 0)
		return (free_shell(glb));
	if (launch_shell(glb) == 0)
		return (free_shell(glb));
	return (0);
}
