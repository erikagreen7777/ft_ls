#include "../ft_ls.h"

/*
** -aother backwards helper
*/
void	back_helper(t_lists *lists)
{
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
	lists->i = lists->filecount;
	while (--lists->i > -1)
	{
		ls_stat(lists->dest[lists->i], lists);
	}
}
/*
** -recursive lstat() helpers
*/
void 	recursive_ls_stat_helper(t_lists *lists)
{
    lists->i = 0;
    while (lists->i < lists->filecount)
    {
        lists->size += add_stat(lists->dest[lists->i]);
        lists->i++;
    }
    ft_printf("total %d\n", lists->size);
    if (lists->flag == 1)
        ft_printf("total 0\n");
    lists->i = -1;
    while (++lists->i < lists->filecount)
        ls_stat(lists->dest[lists->i], lists);
}

/*
** - recurstive lstat() helper for -r
*/
void 	r_recursive_ls_stat_helper(t_lists *lists)
{
	lists->i = -1;
    while (++lists->i < lists->filecount)
        lists->size += add_stat(lists->dest[lists->i]);
    ft_printf("total %d\n", lists->size);
    if (lists->flag == 1)
        ft_printf("total 0\n");
    lists->i = lists->filecount;
    while (--lists->i > -1)
        ls_stat(lists->dest[lists->i], lists);
}

/*
** -lstat()_helper
*/
void	ls_stat_helper(t_lists *lists)
{
	int 			size;

	size = 0;
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
	lists->i = -1;
	while (++lists->i < lists->filecount)
		ls_stat(lists->dest[lists->i], lists);
}

/*
** - a
*/
void 	ls_la(int argc, char **argv, t_lists *lists)
{
	int				j;
	// DIR				*dip;
	struct stat 	fileStat;
	// char			arg[WORD_MAX];

	// lists->i = 0;
	j = lists->argcount;
	lists->flag = 0;
	// if (argc == 2)
	// {
	// 	argv[j] = ".";
	// 	argc = 3;
	// }
	while (j < argc)
	{
		lists->i = 0;
		/* ------------------------------------------------------>> funtion start here */
		if(lstat(argv[j], &fileStat) < 0) 
        	ft_error("ls -l: No such file or directory");
		if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
			ls_stat(argv[j], lists);
		else if (S_ISDIR(fileStat.st_mode) == 1)
		{
				la_helper(argv[j], lists);

		// 	dip = opendir(argv[j]);
		// 	ft_strcpy(arg, argv[j]);
		// 	if (ft_strcmp(arg, "/dev") == 0)
		// 		lists->flag = 1;
		// 	if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
		// 		ft_strcat(arg, "/");
		// 	if (closedir(dip) == -1)
		// 		ft_error("closedir");
		// 	lists->filecount = directory_count(dip, argv[j], 1);
		// 	dip = opendir(argv[j]);
		// 	read_helper_a(lists, 0, arg, dip);
		// 	if (closedir(dip) == -1)
		// 		ft_error("closedir");
		}

			/* ------------------------------------------------------------->> function end here */
		j++;
	}
	ls_stat_helper(lists);
}




