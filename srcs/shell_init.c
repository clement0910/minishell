/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:58:30 by csapt             #+#    #+#             */
/*   Updated: 2021/06/12 12:55:01 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	increment_shlvl(char **tab_env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab_env[i] != NULL)
	{
		if (ft_strncmp(tab_env[i], "SHLVL=", 6) == 0)
		{
			tmp = ft_itoa(1 + ft_atoi(tab_env[i] + 6));
			free(tab_env[i]);
			if (!tmp)
				return (1);
			tab_env[i] = argv_join("SHLVL=%s", tmp);
			if (!tab_env[i])
			{
				free(tmp);
				return (1);
			}
			break ;
		}
		i++;
	}
	return (0);
}

int	init_var(t_global *glb, char **envp)
{
	glb->p = ft_calloc(1, sizeof(t_parse));
	if (!glb->p)
		return (ret_errno_msg(NULL, 1));
	glb->tab_env = ft_strtabdup(envp);
	if (!glb->tab_env)
		return (ret_errno_msg(NULL, 1));
	if (increment_shlvl(glb->tab_env))
		return (ret_msg("Failed to get env", 1));
	glb->env = get_env(glb->tab_env);
	if (!glb->env)
		return (ret_msg("Failed to get env2", 1));
	return (0);
}
