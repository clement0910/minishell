/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:16:36 by csapt             #+#    #+#             */
/*   Updated: 2021/02/10 12:16:46 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char **create_command(char *command)
{
	char **tab_command;
	if (!(tab_command = ft_split((const char *)command, ' ')))
		return (NULL);
	return(tab_command);
}
