/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:31:34 by csapt             #+#    #+#             */
/*   Updated: 2021/06/16 15:21:19 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


void sigint_signal(int num)
{
	write(1, "\n", 1);
	print_cursor(1);
}

int read_line(char **buff)
{
	char tmp[3];
	char *tmp2;

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
			return (ret_errno_msg("get_next_line error", 1));
		*buff = ft_strjoin(tmp, tmp2);
		free(tmp2);
	}
}

void handle_commands(t_global *glb, char ****cmds)
{
    int i;
    int y;

    i = 0;
    if (cmds == NULL)
    	return ;
    while (cmds[i])
    {
        y = 0;
        while (cmds[i][y])
        {
            if (cmds[i][y] && cmds[i][y][0] && built_in_command
                    (cmds[i][y][0],
                     cmds[i][y],
                     glb)) {
                launch_command(glb, cmds[i][y]);
            }

            ft_free_tab(cmds[i][y]);
            if (glb->ret)
                break;
            y++;
        }
        free(cmds[i]);
        i++;
    }
}

int launch_shell(t_global *glb)
{
	char *buff;
    char ****cmds;

	buff = NULL;
	while (1)
	{
		signal(2, sigint_signal);
		read_line(&buff);
		if (buff && buff[0]) {
            cmds = parse_command(glb, buff);
            if (!cmds)
            	return (1);
            handle_commands(glb, cmds);
            free(cmds);
            free(buff);
        }
		print_cursor(glb->ret);
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
	if (init_var(glb, envp))
		return (free_shell(glb));
	print_welcome();
	print_cursor(0);
	if (launch_shell(glb))
		return (free_shell(glb));
	return (0);
}
