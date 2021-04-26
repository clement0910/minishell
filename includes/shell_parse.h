/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:04:11 by csapt             #+#    #+#             */
/*   Updated: 2021/04/26 16:12:23 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_H
# define SHELL_PARSE_H

typedef struct s_parse
{
	//Libre à toi de faire ce que tu veux avec la structure
	char **tab_command;
}				t_parse;

int 	parse_command(char **buf, t_parse *command);
#endif