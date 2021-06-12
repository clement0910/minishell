/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_location.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 18:00:20 by rolaforg          #+#    #+#             */
/*   Updated: 2021/06/12 12:58:01 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*current_path(void)
{
	char	*res;
	int		size;

	size = 64;
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	res[size] = '\0';
	while (!getcwd(res, size))
	{
		free(res);
		size += 8;
		res = malloc(sizeof(char) * (size + 1));
		if (!res)
			return (NULL);
		res[size] = '\0';
	}
	return (res);
}

char 	*get_latest_folder(char **folders)
{
	int		i;
	char	*current;

	i = 0;
	while (folders[i])
		i++;
	if (i > 0)
		i = i - 1;
	current = ft_strdup(folders[i]);
	ft_free_tab(folders);
	if (!current)
		return (NULL);
	return (current);
}

char	*current_folder(void)
{
	char	*path;
	char	**folders;
	char	*current;

	path = current_path();
	folders = ft_split(path, '/');
	free(path);
	if (folders && folders[0])
	{
		current = get_latest_folder(folders);
		if (!current)
			return (NULL);
		return (current);
	}
	ft_free_tab(folders);
	return (ft_strdup("root"));
}
