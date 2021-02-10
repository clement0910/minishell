/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:13:56 by csapt             #+#    #+#             */
/*   Updated: 2021/02/10 14:29:44 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_COMMAND_H
# define SHELL_COMMAND_H

char 		*search_command_path(char *command, char **path);
int			execve_command(char *path_command, char **command, char **envp, int *ret);
char 		**create_command(char *command);

#endif