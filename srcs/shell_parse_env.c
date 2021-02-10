/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:35:31 by csapt             #+#    #+#             */
/*   Updated: 2021/02/10 14:36:37 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	get_path(char **env, char ***path)
{
	int x;
	char *str;

	x = 0;
	while (env[x] && ft_strnstr(env[x], "PATH=", 5) == NULL)
		x++;
	if (!env[x])
		return (return_message_int("Failed to find path in env", 1));
	if (!(str = ft_strtrim(env[x], "PATH=")))
		return (return_message_int("Impossible to get the Path", 1));
	if (!(*path = ft_split(str, ':')))
	{
		free(str);
		return (return_message_int("Failed to get all path", 1));
	}
	free(str);
	return (0);
}

int	get_var_from_env(char **env, char **var, char *str)
{
	int x;
	int len;

	x = 0;
	len = ft_strlen(str);
	while (env[x] && ft_strnstr(env[x], str, len) == NULL)
		x++;
	if (!env[x])
		return (1); //msg
	if (!(*var = ft_strtrim(env[x], str)))
		return (1); //msg
	return (0);
}
