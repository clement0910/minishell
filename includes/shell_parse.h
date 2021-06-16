/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:04:11 by csapt             #+#    #+#             */
/*   Updated: 2021/06/16 15:19:50 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_H
# define SHELL_PARSE_H

int		check_block(char *openblock, char **input,
				 	int *iBlock, int *iBlockIndex);
void	delimit_command(char **input, char *openblock,
					 char *closeblock, char *delimit);
char	**tab_command_add(char **tab, int *i);
char	**create_command_tab(char *lead, char **tab);
char	**strmbtok(char *input, char *delimit,
					char *openblock, char *closeblock);

int		check_backslash(const char *buff, int *i);
int		check_quotes(const char *buff, int *i);
int		check_double_quotes(const char *buff, int *i);
int		check_quotes_and_backslash(const char *buff);

#endif