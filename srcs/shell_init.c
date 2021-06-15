/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:58:30 by csapt             #+#    #+#             */
/*   Updated: 2021/06/15 14:10:52 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	modify_shlvl(char **tab_env)
{
	char	*tmp;

	tmp = ft_itoa(1 + ft_atoi(*tab_env + 6));
	if (!tmp)
		return (1);
	free(*tab_env);
	*tab_env = argv_join("SHLVL=%s", tmp);
	if (!(*tab_env))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	increment_shlvl(char ***tab_env)
{
	int		i;
	char	**tmp;

	i = 0;
	while ((*tab_env)[i] != NULL)
	{
		if (ft_strncmp((*tab_env)[i], "SHLVL=", 6) == 0)
		{
			if (modify_shlvl(*tab_env + i))
				return (1);
			else
				return (0);
		}
		i++;
	}
	tmp = ft_tab_addback(*tab_env, "SHLVL=1");
	if (!tmp)
		return (1);
	free(*tab_env);
	*tab_env = tmp;
	return (0);
}

int	init_var(t_global *glb, char **envp)
{
	glb->tab_env = ft_strtabdup(envp);
	if (!glb->tab_env)
		return (ret_errno_msg(NULL, 1));
	if (increment_shlvl(&glb->tab_env))
		return (ret_msg("Failed to get env", 1));
	glb->env = get_env(glb->tab_env);
	if (!glb->env)
		return (ret_msg("Failed to get env2", 1));
	return (0);
}
