/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:31:34 by csapt             #+#    #+#             */
/*   Updated: 2021/06/15 16:43:35 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void launch_pipes(t_global *glb, char **args1, char **args2)
{
    pid_t pid;
    int fd[2];

    pipe(fd);
    pid = fork();

    if(pid==0)
    {
        dup2(fd[0], STDOUT_FILENO);
        close(fd[1]);
        close(fd[0]);
        launch_command(glb, args1);
        exit(1);
    }
    else
    {
        pid=fork();

        if(pid==0)
        {
            dup2(fd[1], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            launch_command(glb, args2);
            exit(1);
        }
        else
        {
            int status;
            close(fd[1]);
            close(fd[0]);
            waitpid(pid, &status, 0);
        }
    }
}

char** tab_extract(int start, int end, char **tab)
{
    char **res;
    int i;
    int len;

    len = end - start;
    res = malloc(sizeof(char*) * (len + 1));
    while (i < len)
        res[i] = ft_strdup(tab[start + i]);
    res[i] = NULL;
    return (res);
}

int     extract_len(char **tab)
{
    int i;

    i = 0;
    while (tab[i]) {
        if (ft_strcmp(tab[i], ">>") == 0 || ft_strcmp(tab[i], ">") == 0 ||
            ft_strcmp(tab[i], "|") == 0)
            break;
        i++;
    }
    return i;
}

char**  extract_cmds(char **tab)
{
    char    **res;
    int     i;

    res = malloc(sizeof(char*) * (extract_len(tab) + 1));
    i = 0;
    while (tab[i])
    {
        if (ft_strcmp(tab[i], ">>") == 0 || ft_strcmp(tab[i], ">") == 0 ||
            ft_strcmp(tab[i], "|") == 0)
            break;
        res[i] = ft_strdup(tab[i]);
        i++;
    }
    res[i] = NULL;
    return res;
}

char** extract_redirs(char **tab)
{
    char **res;
    int i;

    i = extract_len(tab);
    res = malloc(sizeof(char*) * 1);
    res[0] = NULL;
    while (tab[i])
    {
        if (ft_strcmp(tab[i], ">") != 0 && ft_strcmp(tab[i], ">>") != 0) {
            res = ft_tab_addback(res, tab[i]);
        }
        i++;
    }
    return res;
}

void launch_commands(t_global *glb,char **args)
{
    if (args && args[0] && built_in_command
            (args[0],
             args,
             glb)) {
        launch_command(glb, args);
    }
}

void handle_commands(t_global *glb, char ****cmds)
{
    int i;
    int y;
    int stdoutCopy;
    int stderrorCopy;

    i = 0;
    if (cmds == NULL)
    	return ;
    while (cmds[i])
    {
        y = 0;
        while (cmds[i][y])
        {
            int r = 0;
            char** redirs = extract_redirs(cmds[i][y]);
            stdoutCopy = dup(1);
            stderrorCopy = dup(2);
            while (redirs[r])
            {
                int fd = open(redirs[r], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
                dup2(fd, 1);
                dup2(fd, 2);
                close(fd);
                r++;
            }
            launch_commands(glb, extract_cmds(cmds[i][y]));
            dup2(stdoutCopy,1);
            close(stdoutCopy);
            dup2(stderrorCopy, 2);
            close(stderrorCopy);
            ft_free_tab(cmds[i][y]);
            if (glb->ret)
                break;
            y++;
        }
        free(cmds[i]);
        i++;
    }
}

int launch_shell(t_global *glb)
{
	char *buff;
    char ****cmds;

	buff = NULL;
	while (1)
	{
		if (get_next_line(0, &buff) == -1)
			return (ret_errno_msg("get_next_line error", 0));
		if (buff && buff[0]) {
            cmds = parse_command(glb, buff);
            if (!cmds)
            	return (1);
            handle_commands(glb, cmds);
            free(cmds);
            free(buff);
        }
        print_cursor(glb->ret);
	}
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_global *glb;

	glb = ft_calloc(1, sizeof(t_global));
	if (!glb)
		return (ret_errno_msg(NULL, 1));
	if (init_var(glb, envp))
		return (free_shell(glb));
	print_welcome();
	print_cursor(0);
	if (launch_shell(glb))
		return (free_shell(glb));
	return (0);
}
