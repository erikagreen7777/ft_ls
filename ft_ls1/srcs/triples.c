#include "../ft_ls.h"

/*
** -Rrl(a) helper
*/
int   	Rrl_helper(const char *str, int flag, t_lists *lists)
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
    lex_sortrl(lists);
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
** -Rrl(a)
*/
void	list_dirbigrrl(const char *name, int flag, t_lists *lists)
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
                    Rrl_helper(path, 0, lists);
                    list_dirbigrrl(path, 0, lists);
                }
                else
                {
                    Rrl_helper(path, 1, lists);
                    list_dirbigrrl(path, 1, lists);
                }
        }    
    }
    closedir(dir);
}

/*
** - rla
*/
void            ls_lra(int argc, char **argv, t_lists *lists)
{
    int             j;
    DIR             *dip;
    struct dirent   *dit;
    struct stat     fileStat;
    char            arg[WORD_MAX];
    char            temp[WORD_MAX];

    lists->size = 0;
    lists->i = 0;
    j = 2;
    if (argc == 2)
    {
        argv[j] = ".";
        argc = 3;
    }
    while (j < argc)
    {
        /*
        ** if the file/folder isn't valid
        */
        if(lstat(argv[j], &fileStat) < 0) 
            ft_error("ls -l: No such file or directory");
        /*
        ** if it's a regular file
        */
        if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
            ls_stat(argv[j], lists);        
        else if (S_ISDIR(fileStat.st_mode) == 1)
        {
            // dip = opendir(argv[j]);
            ft_strcpy(arg, argv[j]);
            /*
            ** if the last character of argv[j] isn't a "/", add one
            */
            if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
                ft_strcat(arg, "/");
            // if (closedir(dip) == -1)
            //  ft_error("closedir");

            lists->filecount = directory_count(dip, argv[j], 1);
            dip = opendir(argv[j]);
            /*
            ** malloc memory for the 2D array (include extra + 1 for null at end)
            */
            lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
            if (dip == NULL)
            {
                ft_error(": No file or directory");
            }
            /*
            ** TODO: end split function here?
            */
            ft_strcpy(temp, arg);
            while ((dit = readdir(dip)) != NULL)
            {   
                    if (lists->i > 0)
                        ft_strcpy(arg, temp);
                    ft_strcat(arg, dit->d_name);
                    lists->dest[lists->i] = ft_strdup(arg);
                    ft_bzero(arg, ft_strlen(arg));
                    lists->i++;
            }
            if (closedir(dip) == -1)
                ft_error("closedir");
            rlex_sortrl(lists);
        }
        j++;
    }
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
    lists->i = lists->filecount - 1;
    while (lists->i > -1)
    {
        ls_stat(lists->dest[lists->i], lists);
        lists->i--;
    }
}

/*
** - rlt
*/
void            ls_lrt(int argc, char **argv, t_lists *lists)
{
    int             j;
    DIR             *dip;
    struct dirent   *dit;
    char            **splitstr;
    struct stat     fileStat;
    char            arg[WORD_MAX];
    int             size;
    char            **array;
    char            temp[WORD_MAX];

    size = 0;
    lists->i = 0;
    j = 2;
    lists->flag = 0;
    splitstr = NULL;
    if (argc == 2)
    {
        argv[j] = ".";
        argc = 3;
    }
    while (j < argc)
    {
        /*
        ** if the file/folder isn't valid
        */
        if(lstat(argv[j], &fileStat) < 0) 
            ft_error("ls -l: No such file or directory");
        /*
        ** if it's a regular file
        */
        if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
            ls_stat(argv[j], lists);
        else if (S_ISDIR(fileStat.st_mode) == 1)
        {
            dip = opendir(argv[j]);
            ft_strcpy(arg, argv[j]);
            if (ft_strcmp(arg, "/dev") == 0)
                lists->flag = 1;
            /*
            ** if the last character of argv[j] isn't a "/", add one
            */
            if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
                ft_strcat(arg, "/");
            if (closedir(dip) == -1)
                ft_error("closedir");
            lists->filecount = directory_count(dip, argv[j], 0);
            dip = opendir(argv[j]);
            /*
            ** malloc memory for the 2D array (include extra + 1 for null at end)
            */
            lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
            array = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
            lists->timearray = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
            if (dip == NULL)
            {
                ft_error(": No file or directory");
            }
            ft_strcpy(temp, arg);
            while ((dit = readdir(dip)) != NULL)
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
            ft_switch_time(lists);
            /*
            ** close dir stream
            */
            if (closedir(dip) == -1)
                ft_error("closedir");
        }
        j++;
    }
    /*
    ** print total 512 block-byte size
    */
    lists->i = 0;
    while (lists->i < lists->filecount)
    {
        size += add_stat(lists->dest[lists->i]);
        lists->i++;
    }
    if (size > 0)
        ft_printf("total %d\n", size);
    else if (lists->flag == 1)
        ft_printf("total 0\n");
    /*
    ** print actual ls_stat()
    */
    lists->i = lists->filecount;
    while (--lists->i > -1)
        ls_stat(lists->dest[lists->i], lists);

    // lists->i = -1;
    // while (++lists->i < lists->filecount)
    //     ls_stat(lists->dest[lists->i], lists);
    /*
    ** TODO: free memory
    */
}

/*
** - Rrt
*/
void    rbigrt(const char *name, int flag, t_lists *lists)
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
                    rbigrt_helper(path, 0, lists);
                    rbigrt(path, 0, lists);
                }
                else
                {
                    rbigrt_helper(path, 1, lists);
                    rbigrt(path, 1, lists);
                }
        }    
    }
    closedir(dir);
}