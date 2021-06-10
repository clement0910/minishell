#include <dirent.h>
#include "shell.h"

int built_in_ls(void)
{
    struct dirent *tmp;
    DIR *folder;

    folder = opendir(".");
    if(folder == NULL)
    {
        puts("Unable to read directory");
        return(1);
    }
    else
    {
        while ((tmp = readdir(folder))) {
            if (tmp->d_type == 4 && tmp->d_name[0] != '.') // folder
                ft_putstr_fd(C_YB, 1);
            else if (tmp->d_type == 4)
                ft_putstr_fd(C_RB, 1);
            else if (tmp->d_type == 8) // file
                ft_putstr_fd(C_BB, 1);
            ft_putstr_fd(tmp->d_name, 1);
            ft_putendl_fd(C_N, 1);
            //printf("type: %d\n", tmp->d_type);
            //printf("reclen: %hu\n", tmp->d_reclen);
        }
    }
    closedir(folder);
    return 0;
}