#include "../ft_ls.h"

/*
** ls -Rr helper
*/
int   Rr_helper(const char *str, int flag, t_lists *lists)
{
    DIR             *dip;
    struct dirent   *dit;
    struct stat     fileStat;
    char            **array;
    char            arg[WORD_MAX];
    char            temp[WORD_MAX];

    lists->i = 0;
    ft_strcpy(arg, str);
    if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
        ft_strcat(arg, "/");
    dip = opendir(str);
    if (dip == NULL)
    {
            /*
            ** TODO: create own function for this because it happens often?
            */
        if(lstat(str, &fileStat) < 0) 
        {
            ft_printf("./ft_ls: %s: No such file or directory\n", str);
            return (-1);
        } 
        ft_printf("%s\n", str);
        return (0);
            /*
            ** end function here?
            */
    }
    lists->filecount = directory_count(dip, arg, 0);
    lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
    array = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
    ft_strcpy(temp, arg);
    while ((dit = readdir(dip)) != NULL)
    {
        if (flag == 0)
        {
            if (dit->d_name[0] != '.')
            {
               if (lists->i > 0)
                    ft_strcpy(arg, temp);
                ft_strcat(arg, dit->d_name);
                lists->dest[lists->i] = ft_strdup(arg);
                ft_bzero(arg, ft_strlen(arg));
                lists->i++;
            }
        }
        else if (flag == 1)
        {
            if (lists->i > 0)
                ft_strcpy(arg, temp);
            ft_strcat(arg, dit->d_name);
            lists->dest[lists->i] = ft_strdup(arg);
            ft_bzero(arg, ft_strlen(arg));
            lists->i++;        
        }
    }
    // lists->i = -1;
    // while (++lists->i < lists->filecount)
    //     ft_printf("%s\n", lists->dest[lists->i]);
    if (closedir(dip) == -1)
        ft_error("closedir");
    lex_sort(lists);
    return (0);
}



/*
** ls -Rr
*/
void    list_dirbigrr(const char *name, int flag, t_lists *lists)
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
                    Rr_helper(path, 0, lists);
                    list_dirbigrr(path, 0, lists);
                }
                else
                {
                    Rr_helper(path, 1, lists);
                    list_dirbigrr(path, 1, lists);
                }
        }    
    }
    closedir(dir);
}
