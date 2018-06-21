#include "../ft_ls.h"
/*
** ls -R pre-helper
*/
void    R_first(int argc, char **argv, int flag)
{
    DIR             *dip;
    struct dirent   *dit;
    struct stat     fileStat;
    int             j;
    j = 2;
    if (argc == 2)
    {
        argv[j] = ".";
        argc = 3;
    }
    while (j < argc)
    {
        if (j > 2 && j < argc)
            write(1, "\n", 1);
        dip = opendir(argv[j]);
        if (dip == NULL)
        {
            /*
            ** TODO: create own function for this because it happens often?
            */
                if(stat(argv[j],&fileStat) < 0) 
                {
                    ft_printf("./ft_ls: %s: No such file or directory\n", argv[j]);
                    exit (-1);
                } 
                printf("%s\n", argv[j]);
                exit(0);
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
            else
                ft_printf("%s\n", dit->d_name);
        }
        if (closedir(dip) == -1)
            ft_error("closedir");
        j++;
    }
}


/*
** -R
*/

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

/*
** -Rt R part
*/
void    list_dirbigrt(const char *name, int flag, t_lists *lists)
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
                    Rt_helper(path, 0, lists);
                    list_dirbigrt(path, 0, lists);
                }
                else
                {
                    Rt_helper(path, 1, lists);
                    list_dirbigrt(path, 1, lists);
                }
        }    
    }
    closedir(dir);
}

/*
** ls -Rl
*/
void    list_dirbigrl(const char *name, int flag, t_lists *lists)
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
                    Rl_helper(path, 0, lists);
                    list_dirbigrl(path, 0, lists);
                }
                else
                {
                    Rl_helper(path, 1, lists);
                    list_dirbigrl(path, 1, lists);
                }
        }    
    }
    closedir(dir);
}
