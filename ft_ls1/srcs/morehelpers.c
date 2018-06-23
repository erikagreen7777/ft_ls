#include "../ft_ls.h"



/*
** checks that file/directory exists if dip == null
*/
void null_check(const char *str)
{
    struct stat     fileStat;

    if(lstat(str, &fileStat) < 0) 
    {
        ft_printf("./ft_ls: %s: No such file or directory\n", str);
        exit (-1);
    } 
    printf("%s\n", str);
    exit (-1);
}
/*
** - rt helpers helper
*/
void	rt_helper_helper(DIR *dip, t_lists *lists, char *arg, int flag)
{
	struct dirent   *dit;
	char            temp[WORD_MAX];

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
            read_helper_guts(lists, arg, dit, temp, 1);
        else if (flag == 1)
            read_helper_guts_a(lists, arg, dit, temp, 1);
    }

}

/*
** - Rrt helper
*/
int  rbigrt_helper(const char *str, int flag, t_lists *lists)
{
 	DIR             *dip;
    struct dirent   *dit;
    // struct stat     fileStat;
    char            arg[WORD_MAX];
    char            temp[WORD_MAX];

    lists->i = 0;
    ft_strcpy(arg, str);
    /* ----------------------------> new */
    if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
        ft_strcat(arg, "/");
    /* -----------------------------> end */
    dip = opendir(str);
    /* ---------------------------------> new */
    if (dip == NULL)
        null_check(str);
    if (flag == 0)
        lists->filecount = directory_count(dip, arg, 0);
    else if (flag == 1)
        lists->filecount = directory_count(dip, arg, 1);
    lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
    lists->timearray = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
    ft_strcpy(temp, arg);
    /* -------------------------------> end */
    while ((dit = readdir(dip)) != NULL)
    {
        if (flag == 0)
            read_helper_guts(lists, arg, dit, temp, 1);
        else if (flag == 1)
            read_helper_guts_a(lists, arg, dit, temp, 1);
    }
    if (closedir(dip) == -1)
        ft_error("closedir");
    ft_switch_time(lists);
    print_lists_back(lists);
    return (0);
}

/*
** - used for -Rrlta
*/
int  everything_helper(const char *str, int flag, t_lists *lists)
{
    DIR             *dip;
    struct dirent   *dit;
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
        null_check(str);
    if (flag == 0)
        lists->filecount = directory_count(dip, arg, 0);
    else if (flag == 1)
        lists->filecount = directory_count(dip, arg, 1);
    lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
    array = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
    lists->timearray = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
    ft_strcpy(temp, arg);
    while ((dit = readdir(dip)) != NULL)
    {
        if (flag == 0)
            read_helper_guts(lists, arg, dit, temp, 1);
        else if (flag == 1)
            read_helper_guts_a(lists, arg, dit, temp, 1);
    }
    ft_switch_time(lists);
    if (closedir(dip) == -1)
        ft_error("closedir");
    r_recursive_ls_stat_helper(lists);
    return (0);
}