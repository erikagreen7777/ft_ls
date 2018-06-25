#include "../ft_ls.h"

/*
** -Rrl(a) helper
*/
int   	Rrl_helper(const char *str, int flag, t_lists *lists)
{
    DIR             *dip;
    // struct dirent   *dit;
    // struct stat     fileStat;
    char            arg[WORD_MAX];
    // char            temp[WORD_MAX];
    
    lists->size = 0;
    lists->i = 0;
    ft_strcpy(arg, str);
    if (ft_strcmp(arg, "/dev") == 0)
        lists->flag = 1;
    if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
        ft_strcat(arg, "/");
    dip = opendir(str);
    if (dip == NULL)
        null_check(str);
    rl_helper_helper(dip, lists, arg, flag);
/* ----------------------------------------------------> */
    // if (flag == 0)
    //     lists->filecount = directory_count(dip, arg, 0);
    // else if (flag == 1)
    //     lists->filecount = directory_count(dip, arg, 1);
    // lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
    // ft_strcpy(temp, arg);
    // while ((dit = readdir(dip)) != NULL)
    // {
    //     if (flag == 0)
    //         read_helper_guts(lists, arg, dit, temp, 0);
    //     else if (flag == 1)
    //         read_helper_guts_a(lists, arg, dit, temp, 0);
    // }
/* ----------------------------------------------------> */
    if (closedir(dip) == -1)
        ft_error("closedir");
    lex_sortrl(lists);
    recursive_ls_stat_helper(lists);
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
                if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
                    continue;
/* ----------------------------------------------------> */
                recursive_cat(path, name, entry);
                // ft_strcpy(path, name);
                // ft_strcat(path, "/");
                // ft_strcat(path, entry->d_name);
                // ft_printf("\n%s: \n", path);
/* ----------------------------------------------------> */
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
    // DIR             *dip;
    struct stat     fileStat;
    // char            arg[WORD_MAX];

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
/* -------------------------------------------------------> */
        if(lstat(argv[j], &fileStat) < 0) 
            ft_error("ls -l: No such file or directory");
        if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
            ls_stat(argv[j], lists);        
        else if (S_ISDIR(fileStat.st_mode) == 1)
        {
                rla_helper_helper(lists, argv[j]);

        //     ft_strcpy(arg, argv[j]);
        //     if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
        //         ft_strcat(arg, "/");
        //     lists->filecount = directory_count(dip, argv[j], 1);
        //     dip = opendir(argv[j]);
        //     read_helper_a(lists, 0, arg, dip);
        //     if (closedir(dip) == -1)
        //         ft_error("closedir");
        //     rlex_sortrl(lists);
        }
/* -------------------------------------------------------> */

        j++;
    }
    back_helper(lists);
}

/*
** - rlt
*/
void            ls_lrt(/*int argc, */char **argv, t_lists *lists)
{
    int             j;
    struct stat     fileStat;
    // int             size;

    // size = 0;
    // j = 2;
    lists->flag = 0;
    // if (argc == 2)
    // {
    //     argv[j] = ".";
    //     argc = 3;
    // }
    j = lists->argcount;
    while (j < lists->newargc)
    {
        if (j > lists->argcount && j < lists->newargc)
            write(1, "\n", 1);
        lists->i = 0;
        if(lstat(argv[j], &fileStat) < 0) 
            ft_error("ls -l: No such file or directory");
        if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
            ls_stat(argv[j], lists);
        else if (S_ISDIR(fileStat.st_mode) == 1)
        {
            rlt_helper_helper(lists, argv[j]);
            // dip = opendir(argv[j]);
            // ft_strcpy(arg, argv[j]);
            // if (ft_strcmp(arg, "/dev") == 0)
            //     lists->flag = 1;
            // if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
            //     ft_strcat(arg, "/");
            // if (closedir(dip) == -1)
            //     ft_error("closedir");
            // lists->filecount = directory_count(dip, argv[j], 0);
            // dip = opendir(argv[j]);
            // read_helper(lists, 1, arg, dip);
            // ft_switch_time(lists);
            // if (closedir(dip) == -1)
            //     ft_error("closedir");
            back_helper(lists);
        }
        j++;
    }
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
                if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
                    continue;
/* -------------------------------------------------------> */
                recursive_cat(path, name, entry);
                // ft_strcpy(path, name);
                // ft_strcat(path, "/");
                // ft_strcat(path, entry->d_name);
                // ft_printf("\n%s: \n", path);
/* -------------------------------------------------------> */
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