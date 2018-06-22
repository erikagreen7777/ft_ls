#include "../ft_ls.h"

/*
** - -Rlt helper
*/
int  rlt_helper(const char *str, int flag, t_lists *lists)
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
    if (flag == 0)
        lists->filecount = directory_count(dip, arg, 0);
    else if (flag == 1)
        lists->filecount = directory_count(dip, arg, 1);
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
    if (closedir(dip) == -1)
        ft_error("closedir");
    lists->i = 0;
    while (lists->i < lists->filecount)
    {
        lists->size += add_stat(lists->dest[lists->i]);
        lists->i++;
    }
    ft_printf("total %d\n", lists->size);
    if (lists->flag == 1)
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
    if (flag == 0)
        lists->filecount = directory_count(dip, arg, 0);
    else if (flag == 1)
        lists->filecount = directory_count(dip, arg, 1);
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
int    R_helper(const char *str, int flag)
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

    lists->size = 0;
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
    if (flag == 0)
        lists->filecount = directory_count(dip, arg, 0);
    else if (flag == 1)
        lists->filecount = directory_count(dip, arg, 1);
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
    ft_printf("total %d\n", lists->size);
    if (lists->flag == 1)
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
** - Rrt helper
*/
int  rbigrt_helper(const char *str, int flag, t_lists *lists)
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
    if (flag == 0)
        lists->filecount = directory_count(dip, arg, 0);
    else if (flag == 1)
        lists->filecount = directory_count(dip, arg, 1);
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
    lists->i = lists->filecount;
    while (--lists->i > -1)
        ft_printf("%s\n", lists->dest[lists->i]);
    if (closedir(dip) == -1)
        ft_error("closedir");
    return (0);
}