/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:03:06 by csapt             #+#    #+#             */
/*   Updated: 2021/04/26 16:47:26 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int parse_command(char **buf, t_parse *command)
{
	//Tu peux supprimer la fonction, ca serai bien de garder le même prototype, tu fait ce que tu veux avec la structure
	// La structure t_parse *command est dans shell_parse.h
	// Oublie pas de mettre des messages d'erreurs et securiser t'es mallocs
	//Oublie pas de free *buf;
	char **tmp;

	tmp = ft_split(*buf, ' ');
	if (!tmp)
	{
		free(*buf);
		return (0);
	}
	if (!tmp[0])
	{
		free(*buf);
		free(tmp);
		return (0);
	}
	command->tab_command = tmp;
	free(*buf);
	return (1);
}