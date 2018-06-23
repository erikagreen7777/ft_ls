#include "../ft_ls.h"

/*
** - Rrlta
*/
void	everything(const char *name, int flag, t_lists *lists)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_DIR) 
        {
                char path[1024];
                if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
                    continue;
                recursive_cat(path, name, entry);
                // ft_strcpy(path, name);
                // ft_strcat(path, "/");
                // ft_strcat(path, entry->d_name);
                // printf("\n%s: \n", path);
                /*
                ** 0 flag, no -a. 1 flag -a
                */
                if (flag == 0)
                {
                    everything_helper(path, 0, lists);
                    everything(path, 0, lists);
                }
                else
                {
                    everything_helper(path, 1, lists);
                    everything(path, 1, lists);
                }
        }    
    }
    closedir(dir);
}
