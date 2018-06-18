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
** ls -Rt helper
*/
int   Rt_helper(const char *str, int flag, t_lists *lists)
{
    DIR             *dip;
    struct dirent   *dit;
    struct stat     fileStat;
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
    lists->timearray = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
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
                lists->timearray[lists->i] = ft_strdup(ft_itoa(time_stat(lists->dest[lists->i])));
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
            lists->timearray[lists->i] = ft_strdup(ft_itoa(time_stat(lists->dest[lists->i])));
            lists->i++;        
        }
    }
    ft_switch_time(lists);
    lists->i = -1;
    while (++lists->i < lists->filecount)
        ft_printf("%s\n", lists->dest[lists->i]);
    if (closedir(dip) == -1)
        ft_error("closedir");
    return (0);
}


/*
** ls -R helper
*/
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
** ls -Rl helper
*/
int    Rl_helper(const char *str, int flag, t_lists *lists)
{
    DIR             *dip;
    struct dirent   *dit;
    struct stat     fileStat;
    char            arg[WORD_MAX];
    char            temp[WORD_MAX];
    char            **array;

    lists->i = 0;
    ft_strcpy(arg, str);
    if (ft_strcmp(arg, "/dev") == 0)
        lists->flag = 1;
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
        printf("%s\n", str);
        return (-1);
            /*
            ** end function here?
            */
    }
    lists->filecount = directory_count(dip, arg, 0);
    lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
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
    if (closedir(dip) == -1)
        ft_error("closedir");
    lists->i = 0;
    while (lists->i < lists->filecount)
    {
        lists->size += add_stat(lists->dest[lists->i]);
        lists->i++;
    }
    if (lists->size > 0)
        ft_printf("total %d\n", lists->size);
    else if (lists->flag == 1)
        ft_printf("total 0\n");
    /*
    ** print actual ls_stat()
    */
    lists->i = -1;
    while (++lists->i < lists->filecount)
        ls_stat(lists->dest[lists->i], lists);
    return (0);
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
