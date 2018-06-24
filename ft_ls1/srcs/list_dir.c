#include "../ft_ls.h"

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

/*
** ls -l
*/
void	list_dirl(int argc, char **argv, t_lists *lists)
{
	int				j;
	DIR				*dip;
	struct stat 	fileStat;
	char			arg[WORD_MAX];

/* ------------------------------------------> */
	lists->i = 0;
	j = 1;
	lists->flag = 0;
	if (argc == 2)
	{
		argv[j + 1] = ".";
		argc = 3;
	}
/* ------------------------------------------> */		
	while (++j < argc)
	{
		if(lstat(argv[j], &fileStat) < 0) 
        	ft_error("ls -l: No such file or directory");
		if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
			ls_stat(argv[j], lists);
		else if (S_ISDIR(fileStat.st_mode) == 1)
		{
			dip = opendir(argv[j]);
			ft_strcpy(arg, argv[j]);
			if (ft_strcmp(arg, "/dev") == 0)
				lists->flag = 1;
			if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
				ft_strcat(arg, "/");
			if (closedir(dip) == -1)
				ft_error("closedir");
			lists->filecount = directory_count(dip, argv[j], 0);
			dip = opendir(argv[j]);
			read_helper(lists, 0, arg, dip);
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
	}
	ls_stat_helper(lists);
}


/*
** ls -t
*/
void	list_dirt(int argc, char **argv, t_lists *lists)
{
	int				j;
	DIR				*dip;
	struct stat 	fileStat;
	char			arg[WORD_MAX];
/* --------------------------------------------> */
	lists->i = 0;
	j = 1;
	if (argc == 2)
	{
		argv[j + 1] = ".";
		argc = 3;
	}
/* --------------------------------------------> */
	while (++j < argc)
	{
		if(lstat(argv[j], &fileStat) < 0) 
        	ft_error("ls -t: No such file or directory");
		if ((fileStat.st_mode & S_IFMT) == S_IFREG)
			ls_stat(argv[j], lists);
		else if (S_ISDIR(fileStat.st_mode) == 1)
		{
			ft_strcpy(arg, argv[j]);
			if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
				ft_strcat(arg, "/");
			lists->filecount = directory_count(dip, argv[j], 0);
			dip = opendir(argv[j]);
			read_helper(lists, 1, arg, dip);
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
	}
	ft_switch_time(lists);
	print_lists(lists);
}
/*
** ls -r
*/
void	list_dirr(int argc, char **argv, t_lists *lists)
{
	DIR				*dip;
	char			arg[WORD_MAX];
	// int				lists->j;
/* ------------------------------------------> */
	// argc = argc_stuff(argc, argv, lists);
	lists->j = 1;
	if (argc >= 2)
	{
		argv[lists->j + 1] = ".";
		argc = 3;
	}
	/* ------------------------------------------> */
	while (++lists->j < argc)
	{
		if (lists->j > 2 && lists->j < argc)
			write(1, "\n", 1);
		dip = opendir(argv[lists->j]);
		if (dip == NULL)
			null_check(argv[lists->j]);
		if (closedir(dip) == -1)
			ft_error("closedir");
		lists->filecount = directory_count(dip, argv[lists->j], 0);
		dip = opendir(argv[lists->j]);
		read_helper(lists, 0, arg, dip);
		if (closedir(dip) == -1)
			ft_error("closedir");
		lex_sort(lists);
	}
}
