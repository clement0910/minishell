/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:31:34 by csapt             #+#    #+#             */
/*   Updated: 2021/06/16 19:06:02 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	launch_commands(t_global *glb, char **args)
{
	if (args && args[0] && built_in_command(args[0], args, glb))
		launch_command(glb, args);
}

void	handle_commands1(t_global *glb, char **cmds)
{
	int		r;
	char	**redirs;
	int		stdoutCopy;
	int		stderrorCopy;
	int		fd;

	r = 0;
	redirs = extract_redirs(cmds);
	stdoutCopy = dup(1);
	stderrorCopy = dup(2);
	while (redirs[r])
	{
		fd = open(redirs[r], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
		dup2(fd, 1);
		dup2(fd, 2);
		close(fd);
		r++;
	}
	launch_commands(glb, extract_cmds(cmds));
	dup2(stdoutCopy, 1);
	close(stdoutCopy);
	dup2(stderrorCopy, 2);
	close(stderrorCopy);
}

void	handle_commands(t_global *glb, char ****cmds)
{
	int	i;
	int	y;

	i = 0;
	if (cmds == NULL)
		return ;
	while (cmds[i])
	{
		y = 0;
		while (cmds[i][y])
		{
			handle_commands1(glb, cmds[i][y]);
			ft_free_tab(cmds[i][y]);
			if (glb->ret)
				break ;
			y++;
		}
		free(cmds[i]);
		i++;
	}
}

int	launch_shell(t_global *glb)
{
	char	*buff;
	char	****cmds;

	buff = NULL;
	while (1)
	{
		if (get_next_line(0, &buff) == -1)
			return (ret_errno_msg("get_next_line error", 0));
		if (buff && buff[0])
		{
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

int	main(int ac, char **av, char **envp)
{
	t_global	*glb;

	(void)ac;
	(void)av;
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
