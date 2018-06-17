#include "../ft_ls.h"

static int    R_helper(const char *str, int flag)
{
    DIR             *dip;
    struct dirent   *dit;
    struct stat     fileStat;

    dip = opendir(str);
    if (dip == NULL)
    {
            /*
            ** TODO: create own function for this because it happens often?
            */
        if(stat(str, &fileStat) < 0) 
        {
            ft_printf("./ft_ls: %s: No such file or directory\n", str);
            return (-1);
        } 
        printf("%s\n", str);
        return (-1);
            /*
            ** end function here?
            */
    }
    while ((dit = readdir(dip)) != NULL)
    {
        if (flag == 0)
        {
            if (dit->d_name[0] != '.')
                ft_printf("%s\n", dit->d_name);
        }
        else if (flag == 1)
            ft_printf("%s\n", dit->d_name);
    }
    if (closedir(dip) == -1)
        ft_error("closedir");
    return (0);
}



void list_dirbigr(const char *name, int flag)
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
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                    continue;
                ft_strcpy(path, name);
                ft_strcat(path, "/");
                ft_strcat(path, entry->d_name);
                printf("\n%s: \n", path);
                /*
                ** 0 flag, no -a. 1 flag -a
                */
                if (flag == 0)
                {
                    R_helper(path, 0);
                    list_dirbigr(path, 0);
                }
                else
                {
                    R_helper(path, 1);
                    list_dirbigr(path, 1);
                }
        }    
    }
    closedir(dir);
}
