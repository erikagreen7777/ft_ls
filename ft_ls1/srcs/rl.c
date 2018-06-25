#include "../ft_ls.h"
		
/*
** - -Rlt helper
*/
int  rlt_helper(const char *str, int flag, t_lists *lists)
{
    DIR             *dip;
    char            arg[WORD_MAX];

    lists->i = 0;
    ft_strcpy(arg, str);
    if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
        ft_strcat(arg, "/");
    dip = opendir(str);
    if (dip == NULL)
    	null_check(str);
    rt_helper_helper(dip, lists, arg, flag);
    ft_switch_time(lists);
    if (closedir(dip) == -1)
        ft_error("closedir");
    recursive_ls_stat_helper(lists);
    return (0);
}
/*
** - at
*/
void			list_dirta(/*int argc, */char **argv, t_lists *lists)
{
	int				j;
	DIR				*dip;
	struct stat 	fileStat;
	char			arg[WORD_MAX];

	j = lists->argcount - 1;
	while (++j < lists->newargc)
	{
		if (j > lists->argcount && j < lists->newargc)
		{
			init_struct(&lists);
			write(1, "\n", 1);
		}
		lists->i = 0;
		if(stat(argv[j], &fileStat) < 0) 
        	ft_error("ls -t: No such file or directory");
		if ((fileStat.st_mode & S_IFMT) == S_IFREG)
			ls_stat(argv[j], lists);
		else if (S_ISDIR(fileStat.st_mode) == 1)
		{
			ft_strcpy(arg, argv[j]);
			if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
				ft_strcat(arg, "/");
			lists->filecount = directory_count(dip, argv[j], 1);
			dip = opendir(argv[j]);
			read_helper_a(lists, 1, arg, dip);
			ft_switch_time(lists);
			if (closedir(dip) == -1)
				ft_error("closedir");
			print_lists(lists);
			free_struct(lists);
		}
	}
}
/*
** -lta
*/
void 				ls_lta(char **argv, t_lists *lists)
{
	int				j;
	struct stat 	fileStat;


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
			lta_helper(lists, argv[j]);
		}
		ls_stat_helper(lists);
		j++;
	}
}
/*
** -lt / -tl
*/
void 					ls_lt(/*int argc, */char **argv, t_lists *lists)
{
	int				j;
	struct stat 	fileStat;

	j = lists->argcount;
	lists->flag = 0;
	while (j < lists->newargc)
	{		
		if (j > lists->argcount && j < lists->newargc)
		{
			write(1, "\n", 1);
			// init_struct(&lists);
		}
		lists->i = 0;
		if(lstat(argv[j], &fileStat) < 0) 
        	ft_error("ls -l: No such file or directory");
		if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
			ls_stat(argv[j], lists);
		else if (S_ISDIR(fileStat.st_mode) == 1)
			lt_helper(lists, argv[j]);
		ft_switch_time(lists);
		ls_stat_helper(lists);
		// free_struct(lists);
		j++;
	}
}
/*
** - rl helper
*/
static void rl_helper(char *str, t_lists *lists, struct dirent *dit)
{
    DIR             *dip;
    char            arg[WORD_MAX];
    char            temp[WORD_MAX];

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
    lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
    if (dip == NULL)
        ft_error(": No file or directory");
    ft_strcpy(temp, arg);
    while ((dit = readdir(dip)) != NULL)
    	read_helper_guts(lists, arg, dit, temp, 0);
    if (closedir(dip) == -1)
        ft_error("closedir");
}
/*
** -rl
*/
void    list_dirlr(/*int argc, */char **argv, t_lists *lists)
{
    int             j;
    struct dirent   *dit;
    struct stat     fileStat;

    dit = NULL;
	j = lists->argcount - 1;
    lists->flag = 0;
	while (++j < lists->newargc)
    {	
    	if (j > lists->argcount && j < lists->newargc)
		{
			write(1, "\n", 1);
			init_struct(&lists);
		}
	    lists->i = 0;
        if(lstat(argv[j], &fileStat) < 0) 
            ft_error("ls -l: No such file or directory");
        if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
            ls_stat(argv[j], lists);
        else if (S_ISDIR(fileStat.st_mode) == 1)
        {
        	rl_helper(argv[j], lists, dit);
		    lex_sortrl(lists);
		    ls_stat_helper(lists);
    		free_struct(lists);
        }
        // j++;
    }
}
