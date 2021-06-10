/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:03:06 by rolaforg          #+#    #+#             */
/*   Updated: 2021/06/10 18:02:54 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Check quotes closed
// Check something after && (non space)
// backslash avant quotes 
// backslash avant $ (env)
// If one cmd fail with && stop anb go to next ;
// echo exit pwd cd
int check_and(char *buff)
{
	int 	i;
	size_t 	len;

	i = ft_strlen(buff) - 1;
	while (buff[i] && ft_isws(buff[i]))
		i--;
	if (buff[i - 1] == '&' && buff[i] == '&')
		return (1);
	return (0);
}

int check_quotes(char *buff)
{
	int i;
	int singleCnt;
	int	doubleCnt;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\'' && (buff[i - 1] != '\\' || (buff[i - 1] == '\\' && buff[i - 2] == '\\')) && singleCnt < 2)
			singleCnt++;
		else if (buff[i] == '\'' && (buff[i - 1] != '\\' || (buff[i - 1] == '\\' && buff[i - 2] == '\\')) && singleCnt == 2)
			singleCnt = 1;
		else if (buff[i] == '"' && (buff[i - 1] != '\\' || (buff[i - 1] == '\\' && buff[i - 2] == '\\')) && doubleCnt < 2)
			doubleCnt++;
		else if (buff[i] == '"' && (buff[i - 1] != '\\' || (buff[i - 1] == '\\' && buff[i - 2] == '\\')) && doubleCnt == 2)
			doubleCnt = 1;
		i++;
	}
	if (singleCnt == 1 || doubleCnt == 1)
		return (1);
	return (0);
}

int	parse_command(t_global *glb, char *buf)
{
	char	**cmds;
	char	**cmdsBis;
	char	*cmd;
	char	**args;
	
	if (!buf)
		return (1);
	if (check_quotes(buf) || check_and(buf))
	{
		// printf("Quote not closed. Cannot execute.\n");
		return (1);
	}

	glb->p->cmds = ft_split(buf, ' ');
	cmds = ft_split(buf, ';');
	//cmds = replace_vars(cmds, glb->env);
	if (*cmds)
	{
		while (*cmds)
		{
			cmdsBis = ft_split(*cmds++, '&');
			while (*cmdsBis)
			{
				args = ft_split(*cmdsBis++, ' '); // TODO Create a modified version of ft_split for preventing split of ; inside quotes (for echo)
				cmd = args[0];
				if (built_in_command(cmd, args, glb) == 0)
					launch_command(glb);
				// printf("Command: \'%s\'\n", cmd);
				// if (args[1])
				// {
				// 	printf("Arguments:\n");
				// 	for (int i = 1; args[i]; i++)
				// 		printf("  %i: %s \n", i, args[i]);
				// }
			}
			// ft_free_tab(args);
		}
		// ft_free_tab(cmds);
		// ft_free_tab(cmdsBis);
	}
	return (0);
}