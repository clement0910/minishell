/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_location.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 18:00:20 by rolaforg          #+#    #+#             */
/*   Updated: 2021/02/25 16:25:19 by rolaforg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_f(char **folders)
{
	unsigned int	i;

	i = 0;
	while (folders[i])
		free(folders[i++]);
	free(folders);
}

char *current_path(void)
{
	char	*res;
	int		size;

	size = 64;
	if (!(res = malloc(sizeof(char) * (size + 1))))
		return (0);
	res[size] = '\0';
	while (!getcwd(res, size)) {
		free(res);
		size += 8;
		if (!(res = malloc(sizeof(char) * (size + 1))))
			return (0);
		res[size] = '\0';
	}
	return (res);
}

char	*current_folder(void)
{
	char	*path;
	char	**folders;
	char	*current;
	int		i;

	i = 0;
	path = current_path();
	folders = ft_split(path, '/');
	free(path);
	if (folders && folders[0])
	{
		while (folders[i])
			i++;
		current = ft_strdup(folders[i - 1]);
		free_f(folders);
		return(current);
	}
	free_f(folders);
	return (ft_strdup("root"));
}