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
** - rl helpers helper
*/
void 	rl_helper_helper(DIR *dip, t_lists *lists, char *arg, int flag)
{
	struct dirent   *dit;
	char            temp[WORD_MAX];
	
	if (flag == 0)
        lists->filecount = directory_count(dip, arg, 0);
    else if (flag == 1)
        lists->filecount = directory_count(dip, arg, 1);
    lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
    ft_strcpy(temp, arg);
    while ((dit = readdir(dip)) != NULL)
    {
        if (flag == 0)
            read_helper_guts(lists, arg, dit, temp, 0);
        else if (flag == 1)
            read_helper_guts_a(lists, arg, dit, temp, 0);
    }
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
** -rl
*/
void    list_dirlr(int argc, char **argv, t_lists *lists)
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
    lists->flag = 0;
    if (argc == 2)
    {
        argv[j] = ".";
        argc = 3;
    }
    while (j < argc)
    {
        if(lstat(argv[j], &fileStat) < 0) 
            ft_error("ls -l: No such file or directory");
        if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
            ls_stat(argv[j], lists);
        else if (S_ISDIR(fileStat.st_mode) == 1)
        {
        	/* -----------------------------------> */
            dip = opendir(argv[j]);
            ft_strcpy(arg, argv[j]);
            if (ft_strcmp(arg, "/dev") == 0)
                lists->flag = 1;
            if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
                ft_strcat(arg, "/");
            if (closedir(dip) == -1)
                ft_error("closedir");
            lists->filecount = directory_count(dip, argv[j], 0);
            /* -----------------------------------> */
            dip = opendir(argv[j]);
            lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
            if (dip == NULL)
                ft_error(": No file or directory");
            ft_strcpy(temp, arg);
            while ((dit = readdir(dip)) != NULL)
            	read_helper_guts(lists, arg, dit, temp, 0);
            if (closedir(dip) == -1)
                ft_error("closedir");
        }
        j++;
    }
    lex_sortrl(lists);
    ls_stat_helper(lists);
}

/*
** -lt helper
*/
void		lt_helper(t_lists *lists, char *str)
{
	DIR				*dip;
	char			arg[WORD_MAX];


	dip = opendir(str);
	ft_strcpy(arg, str);
	if (ft_strcmp(arg, "/dev") == 0)
		lists->flag = 1;
	if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
		ft_strcat(arg, "/");
	if (closedir(dip) == -1)
		ft_error("closedir");
	lists->filecount = directory_count(dip, str, 0);
	dip = opendir(str);
	read_helper(lists, 1, arg, dip);
	if (closedir(dip) == -1)
		ft_error("closedir");
}
/*
** -lta helper
*/
void	lta_helper(t_lists *lists, char *str)
{
	DIR				*dip;
	char			arg[WORD_MAX];


	dip = opendir(str);
	ft_strcpy(arg, str);
	if (ft_strcmp(arg, "/dev") == 0)
		lists->flag = 1;
	if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
		ft_strcat(arg, "/");
	if (closedir(dip) == -1)
		ft_error("closedir");
	lists->filecount = directory_count(dip, str, 1);
	dip = opendir(str);
	read_helper_a(lists, 1, arg, dip);
	ft_switch_time(lists);
	if (closedir(dip) == -1)
		ft_error("closedir");

}

