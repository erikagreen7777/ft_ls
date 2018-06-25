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
** - la
*/
void 	ls_la(/*int argc, */char **argv, t_lists *lists)
{
	int				j;
	struct stat 	fileStat;
	// j = lists->argcount;
	j = lists->firstarg;
	lists->flag = 0;
	while (j < lists->newargc)
	{		
		if (j > lists->firstarg && j < lists->newargc)
		{
			init_struct(&lists);
			write(1, "\n", 1);
		}
		lists->i = 0;
		if(lstat(argv[j], &fileStat) < 0) 
        	ft_error("ls -l: No such file or directory");
		if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
			ls_stat(argv[j], lists);
		else if (S_ISDIR(fileStat.st_mode) == 1)
			la_helper(argv[j], lists);
		ls_stat_helper(lists);
		free_struct(lists);
		j++;
	}
	// ls_stat_helper(lists);
}

/*
** find out how many files are in a directory
*/
int		directory_count(DIR *dip, char *str, int flag)
{
	int		filecount;
	struct 	dirent *dit;
	filecount = 0;

	dip = opendir(str);

	while ((dit = readdir(dip)) != NULL)
	{
		if (flag == 0)
		{
			if (dit->d_name[0] != '.')
				filecount++;
		}
		else if (flag == 1)
			filecount++;
	}
	if (closedir(dip) == -1)
		ft_error("closedir");

	return (filecount);
}




